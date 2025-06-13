output: tests/huffmanTreeTests.o src/HuffmanTree.o
	clang++ -std=c++17 -Wall tests/huffmanTreeTests.o src/HuffmanTree.o -o output

tests/huffmanTreeTests.o: tests/huffmanTreeTests.cpp
	clang++ -c -std=c++17 -Wall tests/huffmanTreeTests.cpp -o tests/huffmanTreeTests.o

src/HuffmanTree.o: src/HuffmanTree.cpp src/HuffmanTree.h
	clang++ -c -std=c++17 -Wall src/HuffmanTree.cpp -o src/HuffmanTree.o

clean:
	rm tests/*.o src/*.o output
