# dash-tutorial
A project for experimenting with DASH C++ library (http://www.dash-project.org/).

## Building from Source

`dash-tutorial` is built using [CMake](https://cmake.org/).

### Prerequisites

* CMake version 3.9 or higher
* C compiler supporting the `C99` standard
* C++ compiler supporting the `C++14` standard

Third-party libraries:

* [Open MPI](https://www.open-mpi.org/) with API 3.0 or higher

Optional third-party libraries
* [DASH](https://github.com/dash-project/dash)
* [Google Benchmark](https://github.com/google/benchmark)

The `CMake` script configured in a way that if it cannot find the optional third-party libraries it tries to download and build them automatically. So, there is no need to do anything if they are missing.

### Getting the sources

`dash-tutorial` makes use of `git` submodules to include optional third-party software. The build environment will take care of cloning the submodules upon first invocation if it cannot find them installed.

### Building using CMake
On [Compute Canada](https://www.computecanada.ca/) national platforms (e.g. [graham](https://docs.computecanada.ca/wiki/Graham), [cedar](https://docs.computecanada.ca/wiki/Cedar), etc.), you can download and build `dash-tutorial` using the following commands:

```
$ cd ~/scratch
$ git clone git@github.com:arminms/dash-tutorial.git
$ cd dash-tutorial
$ module load cmake gcc/6.4.0 intel/2017.5 openmpi
$ mkdir build && cd build
$ cmake -DCMAKE_INSTALL_PREFIX=~ ..
```

Then you can see all the available options by:

```
$ make help
```

To build using 8 concurrent threads use:

```
$ make -j 8
```

## Running examples

```
$ mpirun -n 8 example/sort_mpi
```

## Running benchmarks

Benchmarks are in `perf` folder:

```
$ mpirun -n 8 perf/perf_sort_mpi
```

