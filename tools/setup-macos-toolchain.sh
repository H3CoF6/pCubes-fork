#!/usr/bin/env bash
#
# Install FPC + Lazarus on macOS the same way the CI release workflow does.
#
# Usage: tools/setup-macos-toolchain.sh [prefix]
#
# FPC comes from the official Free Pascal disk image (its installer writes the
# compiler under /usr/local and generates /etc/fpc.cfg, so sudo is required
# for that one step). Lazarus comes from the portable upstream zip and is
# unpacked into <prefix> (default "$HOME/pctools/Lazarus"), so no sudo and no
# /Applications entry is needed.
#
# Both architectures are supported: on Apple Silicon the script picks the
# aarch64 Lazarus zip, on Intel the x86_64 one. The FPC disk image is a
# universal installer that covers both.
set -euo pipefail

PREFIX="${1:-$HOME/pctools}"
LAZ_VER="3.8"

# SF_DIR is the upstream folder name; note the hyphen in "x86-64".
case "$(uname -m)" in
  arm64)  LAZ_ARCH="aarch64"; SF_DIR="aarch64" ;;
  x86_64) LAZ_ARCH="x86_64";  SF_DIR="x86-64"  ;;
  *) echo "unsupported macOS architecture: $(uname -m)" >&2; exit 1 ;;
esac

SF="https://downloads.sourceforge.net/lazarus"
FPC_DMG_URL="$SF/Lazarus%20macOS%20x86-64/Lazarus%20$LAZ_VER/fpc-3.2.2.intelarm64-macosx.dmg"
LAZ_ZIP_URL="$SF/Lazarus%20macOS%20$SF_DIR/Lazarus%20$LAZ_VER/lazarus-darwin-$LAZ_ARCH-$LAZ_VER.zip"

LAZ_DIR="$PREFIX/Lazarus"
CACHE="$PREFIX/cache"
mkdir -p "$CACHE"

fetch() { # fetch <url> <dest-file>
  local url="$1" dest="$2"
  if [ -s "$dest" ]; then
    echo "==> cached: $dest"
    return
  fi
  echo "==> downloading $url"
  curl -fL --retry 3 --retry-delay 5 -o "$dest.part" "$url"
  mv "$dest.part" "$dest"
}

# -------------------------------------------------------------------- FPC
# The installer drops the compiler into /usr/local/bin, which is on the
# default PATH on both GitHub runners and a stock macOS shell.
find_fpc() {
  if command -v fpc >/dev/null 2>&1; then command -v fpc; return; fi
  if [ -x /usr/local/bin/fpc ]; then echo /usr/local/bin/fpc; fi
}

if [ -z "$(find_fpc)" ]; then
  dmg="$CACHE/fpc-3.2.2.dmg"
  fetch "$FPC_DMG_URL" "$dmg"

  mnt="$(mktemp -d)"
  echo "==> mounting $dmg"
  hdiutil attach "$dmg" -nobrowse -quiet -mountpoint "$mnt"
  trap 'hdiutil detach "$mnt" -quiet || true' EXIT

  mpkg="$(find "$mnt" -maxdepth 2 -name '*.mpkg' -print -quit)"
  [ -n "$mpkg" ] || { echo "no .mpkg inside $dmg" >&2; exit 1; }

  echo "==> installing FPC (sudo required)"
  sudo installer -pkg "$mpkg" -target /

  hdiutil detach "$mnt" -quiet || true
  trap - EXIT
fi

FPC_BIN="$(find_fpc)"
[ -n "$FPC_BIN" ] || { echo "fpc not found after install" >&2; exit 1; }
# Make sure later steps find it even if /usr/local/bin is not on this PATH.
export PATH="$(dirname "$FPC_BIN"):$PATH"
echo "==> fpc $("$FPC_BIN" -iV) at $FPC_BIN"

# ----------------------------------------------------------------- Lazarus
if [ ! -x "$LAZ_DIR/lazbuild" ]; then
  zip="$CACHE/lazarus-$LAZ_ARCH-$LAZ_VER.zip"
  fetch "$LAZ_ZIP_URL" "$zip"

  echo "==> extracting Lazarus into $LAZ_DIR"
  tmp="$(mktemp -d)"
  unzip -q "$zip" -d "$tmp"
  src="$tmp/lazarus"
  [ -d "$src" ] || { echo "unexpected Lazarus zip layout" >&2; exit 1; }
  mkdir -p "$LAZ_DIR"
  cp -R "$src/." "$LAZ_DIR/"
  rm -rf "$tmp"
fi

[ -x "$LAZ_DIR/lazbuild" ] || { echo "lazbuild not found at $LAZ_DIR/lazbuild" >&2; exit 1; }
echo "==> lazbuild $("$LAZ_DIR/lazbuild" --version) at $LAZ_DIR/lazbuild"

cat <<EOF

Toolchain ready. Build pCubes with:

  "$LAZ_DIR/lazbuild" --lazarusdir="$LAZ_DIR" --widgetset=cocoa \\
      Lazarus_sources/pCubes.lpi

Register BGRABitmap once first, if you have not already:

  "$LAZ_DIR/lazbuild" --lazarusdir="$LAZ_DIR" \\
      --add-package-link /path/to/bgrabitmap/bgrabitmap/bgrabitmappack.lpk

EOF
