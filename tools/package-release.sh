#!/usr/bin/env bash
#
# Assemble a runnable pCubes distribution directory.
#
# Usage: package-release.sh <path-to-binary> <target-name> <output-dir>
#   e.g. package-release.sh Lazarus_sources/pCubes linux-x86_64 dist
#
# The result is <output-dir>/<target-name>/ containing the executable and
# every runtime data file the simulator reads next to it.
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

if [ ! -f "$BIN" ]; then
  echo "error: binary not found: $BIN" >&2
  exit 1
fi

rm -rf "$DEST"
mkdir -p "$DEST"

# Executable
cp "$BIN" "$DEST/"

# Strip debug info when a matching strip is available (release binaries
# drop from ~50 MB to ~13 MB).
if command -v strip >/dev/null 2>&1; then
  strip "$DEST/$(basename "$BIN")" 2>/dev/null || true
fi

# Runtime data. Puzzles.zip holds Menu.xml + the Library.xml index; the
# actual puzzle/figure/extra files are read from disk.
cp "$ROOT/Menu.xml" "$DEST/"
cp "$ROOT/Puzzles.zip" "$DEST/"
cp -r "$ROOT/Puzzles" "$DEST/"
cp -r "$ROOT/Figures" "$DEST/"

if [ -d "$ROOT/Extra" ]; then
  cp -r "$ROOT/Extra" "$DEST/"
fi

# Documentation and history, if present.
[ -f "$ROOT/Lazarus_sources/ReadMe.txt" ] && cp "$ROOT/Lazarus_sources/ReadMe.txt" "$DEST/"
[ -f "$ROOT/Lazarus_sources/history.txt" ] && cp "$ROOT/Lazarus_sources/history.txt" "$DEST/"
[ -f "$ROOT/README.md" ] && cp "$ROOT/README.md" "$DEST/"

echo "packaged $TARGET -> $DEST"
