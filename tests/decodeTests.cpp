#include "../include/Decode.h"
#include <cassert>
#include <iostream>

using namespace std;

void testOne() {
    Decode decode("tests/data/output-1.txt");
    decode.toFile("tests/data/monkey.txt");
    remove("tests/data/monkey.txt");
}

int main() {
    cout << "decodeTests: Begin..." << endl;
    testOne();
    cout << "decodeTests: Passed Test 1" << endl;
    cout << "decodeTests: ...Done" << endl;
    return 0;
}
