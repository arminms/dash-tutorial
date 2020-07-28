# dash-tutorial
A project for experimenting with DASH C++ library (http://www.dash-project.org/).

## Building from Source

`dash-tutorial` is built using [CMake](https://cmake.org/).

### Prerequisites

* CMake version 3.9 or higher
* C compiler supporting the `C99` standard
* C++ compiler supporting the `C++14` standard

Third-party libraries:

* [Open MPI](https://www.open-mpi.org/) with API 3.0 or higher. You can check it
with the following command:

```
$ ompi_info | grep API:
                 MPI API: 3.1.0
```

Optional third-party libraries
* [DASH](https://github.com/dash-project/dash)
* [Google Benchmark](https://github.com/google/benchmark)

The `CMake` script configured in a way that if it cannot find the optional third-party libraries it tries to download and build them automatically. So, there is no need to do anything if they are missing.

### Building using CMake
On [Compute Canada](https://www.computecanada.ca/) national platforms (e.g. [graham](https://docs.computecanada.ca/wiki/Graham), [cedar](https://docs.computecanada.ca/wiki/Cedar), [béluga](https://docs.computecanada.ca/wiki/Beluga), etc.), you can download and build the tutorial using the following commands:

```
$ cd ~/scratch
$ git clone git@github.com:arminms/dash-tutorial.git
$ cd dash-tutorial
$ module load cmake gcc/7.3.0 intel/2018.3 openmpi
$ mkdir build && cd build && cmake ..
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

## Submitting as a job

Here is an example script to submit the `sort_mpi` benchmark using `sbatch`
command: 

```
#!/bin/bash
#SBATCH --account=cc-debug
#SBATCH --ntasks=16        # number of MPI processes
#SBATCH --mem-per-cpu=1G   # memory; default unit is megabytes
#SBATCH --time=0-00:05     # time (DD-HH:MM)
srun ./perf_sort_mpi
```
