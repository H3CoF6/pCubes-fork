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
