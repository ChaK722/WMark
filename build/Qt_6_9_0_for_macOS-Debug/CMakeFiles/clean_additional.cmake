# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/WMark_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/WMark_autogen.dir/ParseCache.txt"
  "WMark_autogen"
  )
endif()
