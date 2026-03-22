#pragma once

#include <stdlib.h>

#ifdef aligned_alloc
#undef aligned_alloc
#endif

#ifdef _WIN32
#define aligned_alloc(alignment, size) _aligned_malloc(size, alignment)
#endif

template <typename T>
T * New(int elements)
{
  return (T *)aligned_alloc(16, (sizeof (T)) * elements);
}
