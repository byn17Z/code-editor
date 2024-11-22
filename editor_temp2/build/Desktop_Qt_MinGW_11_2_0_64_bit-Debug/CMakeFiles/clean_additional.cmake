# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Editor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Editor_autogen.dir\\ParseCache.txt"
  "Debugger\\CMakeFiles\\debugger_lib_autogen.dir\\AutogenUsed.txt"
  "Debugger\\CMakeFiles\\debugger_lib_autogen.dir\\ParseCache.txt"
  "Debugger\\debugger_lib_autogen"
  "Editor_autogen"
  )
endif()
