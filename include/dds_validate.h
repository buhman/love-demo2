#pragma once

#include "dds.h"

struct DDS_FILE {
  unsigned int dwMagic;
  DDS_HEADER header;
};

DDS_FILE const * dds_validate(void const * data, unsigned int size, void ** out_data, int * out_size);
