set(BENCHMARKS
  generate_random
)

foreach(BENCHMARK ${BENCHMARKS})
  set(PERF_TARGET perf_${BENCHMARK}_mpi)
  add_executable(${PERF_TARGET} perf_${BENCHMARK}.cpp)
  target_compile_features(${PERF_TARGET} PRIVATE cxx_std_14)
  target_link_libraries(${PERF_TARGET} ${MPI_LIBRARIES} MPI::MPI_CXX dash-mpi dart-mpi ${BENCHMARK_TARGET})
  install(TARGETS ${PERF_TARGET} RUNTIME DESTINATION bin COMPONENT ${PERF_TARGET})
endforeach()
