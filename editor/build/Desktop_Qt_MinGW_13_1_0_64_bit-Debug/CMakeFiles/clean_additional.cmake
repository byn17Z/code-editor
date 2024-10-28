# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\editor1_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\editor1_autogen.dir\\ParseCache.txt"
  "editor1_autogen"
  )
endif()
