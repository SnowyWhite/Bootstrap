# bootstrap

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`bootstrap` in your `build2`-based project, then instead see the accompanying
package [`README.md`](<PACKAGE>/README.md) file.

The development setup for `bootstrap` uses the standard `bdep`-based workflow.
For example:

```
git clone .../bootstrap.git
cd bootstrap

bdep init -C @gcc cc config.cxx=g++
bdep update
bdep test
```

Build 32 bit version:

```
bdep init -C -@mingw cc config.cxx=x86_64-w64-mingw32-g++
bdep update -@mingw
```

