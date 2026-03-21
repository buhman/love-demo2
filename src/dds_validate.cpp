#include <assert.h>
#include <stdint.h>

#include "dds_validate.h"

static inline unsigned int max(unsigned int a, unsigned int b)
{
  return (a > b) ? a : b;
}

struct dds_size_levels {
  unsigned int const size;
  unsigned int const levels;
};

static inline unsigned int dim(unsigned int d)
{
  return max(1, (d / 4));
}

static inline dds_size_levels dds_mip_total_size(uintptr_t data,
                                                 unsigned int height,
                                                 unsigned int width,
                                                 unsigned int max_mip_levels)
{
  unsigned int mip_total_size = 0;
  unsigned int mip_levels = 0;
  while (true) {
    unsigned int mip_size = dim(height) * dim(width) * 8;
    mip_total_size += mip_size;
    //subresourceData[mip_levels].pSysMem = (const void *)data;
    //subresourceData[mip_levels].SysMemPitch = dim(width) * 8;
    mip_levels += 1;
    assert(mip_levels <= max_mip_levels);
    data += mip_size;

    if (max_mip_levels == 1 || (width == 1 && height == 1))
      break;

    height /= 2;
    width /= 2;
  }

  return (dds_size_levels){mip_total_size, mip_levels};
}

DDS_FILE const * dds_validate(void const * data, unsigned int size, void ** out_data, int * out_size)
{
  DDS_FILE const * const dds = (DDS_FILE const *)data;
  assert(dds->dwMagic == DDS_MAGIC);
  assert(dds->header.dwSize == 124);
  assert(dds->header.ddspf.dwSize == 32);
  assert(dds->header.ddspf.dwFlags == DDS_FOURCC);
  assert(dds->header.ddspf.dwFourCC == MAKEFOURCC('D','X','T','1'));

  assert(dds->header.dwDepth == 0);

  uintptr_t image_data = ((uintptr_t)dds) + (sizeof (DDS_FILE));
  dds_size_levels ret = dds_mip_total_size(image_data,
                                           dds->header.dwHeight,
                                           dds->header.dwWidth,
                                           dds->header.dwMipMapCount);
  assert(ret.size + (sizeof (DDS_FILE)) == size);
  assert(ret.levels == dds->header.dwMipMapCount);

  *out_data = (void *)image_data;
  *out_size = ret.size;
  return dds;
}
