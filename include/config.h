#ifndef CONFIG_H
#define CONFIG_H

#include <cstddef>

inline constexpr size_t CHAR_COUNT = 256, BYTE_SIZE = 8, MAX_BITS = 64;
inline constexpr const char *FILE_EXTENSION = ".fin",
                            *CODE_OVERFLOW = "code exceeds 64 bits",
                            *FAIL_READ_FILE = "failed to read file",
                            *FAIL_WRITE_FILE = "failed to write file";

#endif
