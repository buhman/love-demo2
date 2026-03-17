#pragma once

#include <stdlib.h>

template <typename T>
T * New(int elements)
{
  return (T *)aligned_alloc(16, (sizeof (T)) * elements);
}
