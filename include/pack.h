#include <stdint.h>

namespace pack {
  struct file_entry {
    char filename[128];
    uint32_t offset;
    uint32_t size;
  };

  struct header {
    uint32_t magic;
    uint32_t header_size;
    uint32_t entry_count;
    file_entry entry[0];
  };
  static_assert((sizeof (header)) == 12);

  const uint32_t magic_value = 0x037c2dc0;
}
