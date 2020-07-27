set(PROGS
  hello
  global
  local
  generate_random
)

foreach(PROG ${PROGS})
  set(PROG_TARGET ${PROG}_mpi)
  add_executable(${PROG_TARGET} ${PROG}.cpp)
  target_compile_features(${PROG_TARGET} PRIVATE cxx_std_14)
  target_link_libraries(${PROG_TARGET} MPI::MPI_CXX dash-mpi dart-mpi )
  install(TARGETS ${PROG_TARGET} RUNTIME DESTINATION bin COMPONENT ${PROG_TARGET})
endforeach()
