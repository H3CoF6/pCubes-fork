#!/usr/bin/env bash
#
# Assemble a macOS application bundle for pCubes.
#
# Usage: package-macos.sh <path-to-binary> <target-name> <output-dir>
#   e.g. package-macos.sh Lazarus_sources/pCubes macos-x86_64 dist
#
# The result is <output-dir>/<target-name>/pCubes.app, a double-clickable
# bundle. pCubes resolves its data files relative to the executable, so the
# puzzle library sits in Contents/MacOS right next to the binary.
#
# The binary is stripped and ad-hoc code signed. Signing is not optional on
# Apple Silicon: the kernel refuses to run an unsigned arm64 executable.
set -euo pipefail

if [ "$#" -ne 3 ]; then
  echo "usage: $0 <binary> <target-name> <output-dir>" >&2
  exit 2
fi

BIN="$1"
TARGET="$2"
OUTDIR="$3"

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
DEST="$OUTDIR/$TARGET"
APP="$DEST/pCubes.app"

if [ ! -f "$BIN" ]; then
  echo "error: binary not found: $BIN" >&2
  exit 1
fi

rm -rf "$DEST"
mkdir -p "$APP/Contents/MacOS" "$APP/Contents/Resources"

# --------------------------------------------------------------- executable
cp "$BIN" "$APP/Contents/MacOS/pCubes"
if command -v strip >/dev/null 2>&1; then
  strip "$APP/Contents/MacOS/pCubes" 2>/dev/null || true
fi
# Ad-hoc sign so Gatekeeper and Apple Silicon let the binary run.
codesign --force --sign - --timestamp=none "$APP/Contents/MacOS/pCubes" >/dev/null 2>&1 || \
  echo "warning: ad-hoc codesign failed; arm64 builds may not launch" >&2

# ------------------------------------------------------------ runtime data
# Puzzles.zip holds Menu.xml + the Library.xml index; the actual puzzle,
# figure and extra files are read from disk. All of it lives beside the
# executable because that is where pCubes looks (ExtractFilePath(ParamStr(0))).
cp "$ROOT/Menu.xml" "$APP/Contents/MacOS/"
cp "$ROOT/Puzzles.zip" "$APP/Contents/MacOS/"
cp -r "$ROOT/Puzzles" "$APP/Contents/MacOS/"
cp -r "$ROOT/Figures" "$APP/Contents/MacOS/"
[ -d "$ROOT/Extra" ] && cp -r "$ROOT/Extra" "$APP/Contents/MacOS/"

# --------------------------------------------------------------- icon
ICON_NAME=""
if [ -f "$ROOT/Lazarus_sources/pCubes.png" ] && command -v iconutil >/dev/null 2>&1; then
  ICONSET="$(mktemp -d)/pCubes.iconset"
  mkdir -p "$ICONSET"
  SRC="$ROOT/Lazarus_sources/pCubes.png"
  for s in 16 32 128 256 512; do
    sips -z $s $s "$SRC" --out "$ICONSET/icon_${s}x${s}.png" >/dev/null 2>&1 || true
  done
  sips -z 32 32   "$SRC" --out "$ICONSET/icon_16x16@2x.png"   >/dev/null 2>&1 || true
  sips -z 64 64   "$SRC" --out "$ICONSET/icon_32x32@2x.png"   >/dev/null 2>&1 || true
  sips -z 256 256 "$SRC" --out "$ICONSET/icon_128x128@2x.png" >/dev/null 2>&1 || true
  sips -z 512 512 "$SRC" --out "$ICONSET/icon_256x256@2x.png" >/dev/null 2>&1 || true
  if iconutil -c icns "$ICONSET" -o "$APP/Contents/Resources/pCubes.icns" >/dev/null 2>&1; then
    ICON_NAME="pCubes.icns"
  fi
fi

# --------------------------------------------------------------- Info.plist
cat > "$APP/Contents/Info.plist" <<PLIST
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>CFBundleDevelopmentRegion</key>
  <string>English</string>
  <key>CFBundleExecutable</key>
  <string>pCubes</string>
  <key>CFBundleName</key>
  <string>pCubes</string>
  <key>CFBundleDisplayName</key>
  <string>pCubes</string>
  <key>CFBundleIdentifier</key>
  <string>su.pmetro.pCubes</string>
  <key>CFBundleInfoDictionaryVersion</key>
  <string>6.0</string>
  <key>CFBundlePackageType</key>
  <string>APPL</string>
  <key>CFBundleShortVersionString</key>
  <string>${PCUBES_VERSION:-0.4}</string>
  <key>CFBundleVersion</key>
  <string>${PCUBES_BUILD:-4}</string>
  <key>NSHighResolutionCapable</key>
  <true/>
  <key>LSMinimumSystemVersion</key>
  <string>10.13</string>
$([ -n "$ICON_NAME" ] && echo "  <key>CFBundleIconFile</key>
  <string>$ICON_NAME</string>")
</dict>
</plist>
PLIST

printf 'APPL????' > "$APP/Contents/PkgInfo"

# Sign the finished bundle (covers the plist and resources too).
codesign --force --deep --sign - --timestamp=none "$APP" >/dev/null 2>&1 || \
  echo "warning: ad-hoc codesign of the bundle failed" >&2

# Bundle documentation.
[ -f "$ROOT/Lazarus_sources/ReadMe.txt" ] && cp "$ROOT/Lazarus_sources/ReadMe.txt" "$DEST/"
[ -f "$ROOT/Lazarus_sources/history.txt" ] && cp "$ROOT/Lazarus_sources/history.txt" "$DEST/"
[ -f "$ROOT/README.md" ] && cp "$ROOT/README.md" "$DEST/"

echo "packaged $TARGET -> $APP"
