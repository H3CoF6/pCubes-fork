# pCubes-fork

Fork of **pCubes**, a twisty-puzzle simulator by Boris Mouradov.

- Upstream: https://github.com/BMouradov/pCubes
- This fork: https://github.com/H3CoF6/pCubes-fork

## Credits

All original source code is by Boris Mouradov and contributors.
This fork is a personal copy and is **not** intended as an upstream
contribution; it only adds housekeeping on top of the original tree.

## Original project notes

pCubes is a twisty-puzzle (Rubik's cube and friends) simulator, open source
since the 0.4 beta (May 02 2023). It is written in Free Pascal / Lazarus
(v2.2.2).

To build the sources you must install the **BGRABitmap** package:

    Package \ Online package manager \ BGRABitmap \ Install

Sources live in `Lazarus_sources/`; puzzle definitions are XML files under
`Puzzles/` and `Figures/`, loaded at runtime from `Puzzles.zip`.

## What this fork adds

* The complete puzzle library from the official release
  (http://pmetro.su/pCubes.zip, v0.3 build 169) — 5819 puzzles, up from the
  four samples that ship with the open sources.
* A cross-platform (Linux) build: the sources now compile with the LCL on
  non-Windows targets. See `Lazarus_sources/uWinCompat.pas`; the Windows-only
  OpenGL backend (WGL into a bitmap) falls back to the BSP engine elsewhere.

## Building

Requirements: FPC 3.2.x, Lazarus 2.2+, and the BGRABitmap package registered
with the IDE.

    # register BGRABitmap once (adjust the path to your checkout)
    lazbuild --add-package-link /path/to/bgrabitmap/bgrabitmap/bgrabitmappack.lpk

    # build (choose a widgetset: gtk2 on Linux, win32 on Windows)
    lazbuild --widgetset=gtk2 Lazarus_sources/pCubes.lpi

The binary is written to `Lazarus_sources/pCubes` (`pCubes.exe` on Windows).
It reads its puzzle library and `Puzzles.zip` from the working directory, so
use `tools/package-release.sh` to assemble a runnable folder:

    tools/package-release.sh Lazarus_sources/pCubes linux-x86_64 dist

## Releases

Pushing a `v*` tag triggers `.github/workflows/release.yml`, which builds and
publishes archives for Linux/Windows on x86_64 and arm64. Pushes to `main`
do not create a release.

Prebuilt archives are also available on the Actions page: run the workflow
manually (Actions -> Release -> Run workflow) and download the *Artifacts*.

The Linux builds use the **GTK2** widgetset, so the `gtk2` runtime must be
installed to run them, e.g. on Arch:

    sudo pacman -S gtk2        # or: yay -S gtk2
    tar xzf pCubes-linux-x86_64.tar.gz
    cd linux-x86_64 && ./pCubes

Keep the whole folder together: the executable reads `Puzzles.zip`, `Menu.xml`
and the `Puzzles/ Figures/ Extra/` data from its own directory.
