#include <cstddef>
#include <cstdint>
#include <fstream>

using namespace std;

int main() {
    ofstream file("tests/data/output-1.txt", ios::binary);
    if (!file) {
        return 1;
    }
    uint8_t arr[256] = {};
    arr[static_cast<unsigned char>('a')] = 4;
    arr[static_cast<unsigned char>('b')] = 3;
    arr[static_cast<unsigned char>('c')] = 2;
    arr[static_cast<unsigned char>('d')] = 1;
    arr[static_cast<unsigned char>('\n')] = 4;
    file.write(reinterpret_cast<char *>(arr), sizeof(arr));
    uint8_t offset = 2;
    file.write(reinterpret_cast<char *>(&offset), sizeof(uint8_t));
    array<uint8_t, 4> code = {0x3f, 0x6a, 0xa0, 0x0e};
    size_t i = 0;
    for (size_t j = 1; i < code.size() - 1; i++, j += j) {
        file.write(reinterpret_cast<char *>(&code[i]), sizeof(uint8_t));
    }
    file.write(reinterpret_cast<char *>(&code[i]), sizeof(uint8_t));
    file.close();
    return 0;
}
