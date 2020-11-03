file(GLOB_RECURSE LIB_SRC "*.cpp" "*.h" "*.nsmap")
add_library(libmagicserver ${LIB_SRC})
