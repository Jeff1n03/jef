#include "../include/Encode.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <unordered_map>

using namespace std;

void testOne() {
    Encode encode = Encode{"e.txt"};
    unordered_map<unsigned char, uint64_t> expected = {
        {'d', 0}, {'c', 2}, {'a', 6}, {'b', 7}};
    assert(encode.getCodes() == expected);
}

int main() {
    cout << "\nencodeTests: Begin..." << endl;
    testOne();
    cout << "encodeTests: Passed Test 1" << endl;
    return 0;
}
