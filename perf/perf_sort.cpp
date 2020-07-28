#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

#include <mpi.h>
#include <benchmark/benchmark.h>
#include <libdash.h>

namespace
{
    void Sort_MPI_float(benchmark::State &state)
    {
        dash::Array<float> arr(state.range(0));

        std::mt19937 rd(static_cast<uint>(dash::myid()));
        std::uniform_real_distribution<float> dist(0, 1);

        double max_elapsed_second;
        while (state.KeepRunning())
        {
            dash::generate(arr.begin(), arr.end(), [&] () { return dist(rd); });
            // arr.barrier();

            // Do the work and time it on each proc
            auto start = std::chrono::high_resolution_clock::now();

            // The unit of code we want to benchmark
            dash::sort(arr.begin(), arr.end());
            arr.barrier();

            auto end = std::chrono::high_resolution_clock::now();
            // Now get the max time across all procs:
            // for better or for worse, the slowest processor is the one that is
            // holding back the others in the benchmark.
            auto const duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
            auto elapsed_seconds = duration.count();
            MPI_Allreduce(&elapsed_seconds, &max_elapsed_second, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
            state.SetIterationTime(max_elapsed_second);
        }
    }
}

BENCHMARK(Sort_MPI_float)
// ->  Arg(30000000000)
->  RangeMultiplier(2)
->  Range(1<<20, 1<<24)
->  Unit(benchmark::kMillisecond)
->  UseManualTime();

// This reporter does nothing.
// We can use it to disable output from all but the root process
class NullReporter
:   public ::benchmark::BenchmarkReporter
{
public:
    NullReporter() {}
    virtual bool ReportContext(const Context &) {return true;}
    virtual void ReportRuns(const std::vector<Run> &) {}
    virtual void Finalize() {}
};

int main(int argc, char* argv[])
{
    dash::init(&argc, &argv);

    if (dash::myid() == 0)
    {
        std::cout << "Number of Units = " << dash::size() << std::endl;
        ::benchmark::RunSpecifiedBenchmarks();
    }
    else
    {
        NullReporter null;
        ::benchmark::RunSpecifiedBenchmarks(&null);
    }

    dash::finalize();
}
