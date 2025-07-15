#include "../include/Decode.h"
#include "../include/Encode.h"
#include <exception>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    string invalid = "Error: invalid no. of args";
    if (argc < 2 || argc > 3) {
        cerr << invalid << endl;
        return 1;
    }
    string filename;
    bool replace = false;
    if (argc == 3) {
        if (strcmp(argv[1], "-r") == 0) {
            replace = true;
        } else {
            cerr << invalid << endl;
            return 1;
        }
        filename = argv[2];
    } else {
        filename = argv[1];
    }
    try {
        if (filename.size() <= strlen(FILE_EXTENSION) ||
            filename.substr(filename.size() - strlen(FILE_EXTENSION)) !=
                FILE_EXTENSION) {
            Encode encode(filename);
            encode.toFile();
        } else {
            Decode decode(filename);
            decode.toFile();
        }
    } catch (exception &error) {
        cerr << "Error: " << error.what() << endl;
        return 1;
    }
    if (replace) {
        if (remove(filename.c_str()) != 0) {
            cerr << "Error: failed to replace" << endl;
            return 1;
        }
    }
    return 0;
}
