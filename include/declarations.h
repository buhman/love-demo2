#pragma once

#ifdef _WIN32
#ifdef _MSC_VER
#define EXPORT __declspec(dllexport)
#define DECL __cdecl
#else
#define EXPORT __attribute__((dllexport))
#define DECL __attribute__((__cdecl__))
#endif
#else
#define EXPORT
#define DECL
#endif
