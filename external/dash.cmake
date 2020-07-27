if((NOT DASH-MPI_DIR) OR (NOT DART-MPI_DIR))
  message("-- Try cloning DASH/DART...")
  execute_process(COMMAND git submodule update --init -- external/dash
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

  # set(DART_IMPLEMENTATIONS "mpi" CACHE STRING "Comma-separated list of DASH runtime implementations to build.")
  set(BUILD_EXAMPLES OFF CACHE BOOL "Specify whether to build examples")
  set(BUILD_TESTS OFF CACHE BOOL "Whether tests should be built")
  set(ENABLE_SCALAPACK OFF CACHE BOOL "Specify whether ScaLAPACK features are enabled")

  # patching the files
  message("-- Patching DASH/DART CMake scripts7...")
  file(GLOB_RECURSE PATCH_FILES 
    "${PROJECT_SOURCE_DIR}/external/dash/*.cmake"
    "${PROJECT_SOURCE_DIR}/external/dash/CMakeLists.*")
#   message("${PATCH_FILES}")
  foreach(FILE ${PATCH_FILES})
    file(READ ${FILE} CONTENT)
    string(REPLACE "CMAKE_SOURCE_DIR" "PROJECT_SOURCE_DIR"
      PATCHED
      "${CONTENT}"
    )
    file(WRITE ${FILE} ${PATCHED})
  endforeach()

  file(READ "${PROJECT_SOURCE_DIR}/external/dash/dart-impl/mpi/CMakeLists.txt" CONTENT)
  string(REPLACE "\${PROJECT_SOURCE_DIR}/CMakeExt/MPI.cmake"
    "\${CMAKE_SOURCE_DIR}/external/dash/CMakeExt/MPI.cmake" PATCHED "${CONTENT}")
  file(WRITE "${PROJECT_SOURCE_DIR}/external/dash/dart-impl/mpi/CMakeLists.txt" ${PATCHED})

  file(READ "${PROJECT_SOURCE_DIR}/external/dash/dash/CMakeLists.txt" CONTENT)
  string(REPLACE "\${PROJECT_SOURCE_DIR}/dash/include/dash/util/StaticConfig.h"
    "\${CMAKE_CURRENT_SOURCE_DIR}/include/dash/util/StaticConfig.h" PATCHED "${CONTENT}")
  file(WRITE "${PROJECT_SOURCE_DIR}/external/dash/dash/CMakeLists.txt" "${PATCHED}")

  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/dash EXCLUDE_FROM_ALL)
  include_directories(
    "${PROJECT_SOURCE_DIR}/external/dash/dash/include"
    "${PROJECT_SOURCE_DIR}/external/dash/dart-if/include"
  )

  # removing .git in external/dash to not bugged by git about modified files
  file(REMOVE_RECURSE "${PROJECT_SOURCE_DIR}/external/dash/.git")
endif()
