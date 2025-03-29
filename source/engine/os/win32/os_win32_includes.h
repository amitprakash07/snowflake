/*
        Any project that uses Windows should #include this file
        to ensure consistency
*/

#ifndef ENGINE_OS_WIN32_OS_WIN32_INCLUDES_H_
#define ENGINE_OS_WIN32_OS_WIN32_INCLUDES_H_

// Exclude extraneous Windows stuff
#define WIN32_LEAN_AND_MEAN
// Prevent Windows from creating min/max macros
#define NOMINMAX

// Initialize Windows
#include <Windows.h>
#include <windowsx.h>

#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN

#endif
