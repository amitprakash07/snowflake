cmake_minimum_required(VERSION 3.25.0)

if(WIN32)
    option(USE_MSVC, "Use MSVC compiler")
elseif(UNIX)
    option(USE_GCC, "Use gcc compiler")
endif()