cmake_minimum_required(VERSION 3.21.7)

if(WIN32)
    option(USE_MSVC, "Use MSVC compiler")
elseif(UNIX)
    option(USE_GCC, "Use gcc compiler")
endif()