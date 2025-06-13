CXX := clang++
CXXFLAGS := -std=c++17 -Wall

all:

huffmanTreeTest: tests/huffmanTreeTests.o src/HuffmanTree.o
	$(CXX) $(CXXFLAGS) tests/huffmanTreeTests.o src/HuffmanTree.o -o huffmanTreeTest

tests/huffmanTreeTests.o: tests/huffmanTreeTests.cpp
	$(CXX) $(CXXFLAGS) -c tests/huffmanTreeTests.cpp -o tests/huffmanTreeTests.o

src/HuffmanTree.o: src/HuffmanTree.cpp src/HuffmanTree.h
	$(CXX) $(CXXFLAGS) -c src/HuffmanTree.cpp -o src/HuffmanTree.o

test: huffmanTreeTest
	./huffmanTreeTest

clean:
	rm tests/*.o src/*.o huffmanTreeTest
