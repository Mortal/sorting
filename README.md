Modify the `Makefile` so that `TPIEMEMORY`, `TPIEFILESTREAM`, `STXXL` point to
your [TPIE/memory](https://github.com/thomasmoelhave/tpie/tree/memory),
[TPIE/filestream](https://github.com/thomasmoelhave/tpie/tree/filestream) and
[STXXL](http://stxxl.sourceforge.net/) source trees. In the TPIE source trees,
create subfolders `Release` and use `cmake` to build release builds in them.
Build STXXL in parallel mode using `make library_g++_pmode`.

Now run the `Makefile` in this project, and `sorting.sh` is ready for use.
