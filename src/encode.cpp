#include <fstream>

using namespace std;

unordered_map<unsigned char, uint64_t> frequencyTable(string filename) {
    unordered_map<unsigned char, uint64_t> frequencies;
    ifstream file(filename, ios::binary);
    if (file) {
        char byte;
        while (file.get(byte)) {
            frequencies[static_cast<unsigned char>(byte)]++;
        }
        file.close();
    }
    return frequencies;
}
