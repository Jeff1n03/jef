#ifndef CONFIG_H
#define CONFIG_H

#include <cstddef>

inline constexpr size_t CHAR_COUNT = 256, BYTE_SIZE = 8;
inline constexpr const char *FILE_EXTENSION = ".fin",
                            *FAIL_READ_FILE = "failed to read file",
                            *FAIL_WRITE_FILE = "failed to write file",
                            *FAIL_INIT_TREE = "failed to initialize "
                                              "huffman tree";

#endif
