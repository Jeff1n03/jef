CXX := clang++
CXXFLAGS := -std=c++17 -Wall

TESTS := huffmanTreeTest

all:

huffmanTreeTest: build/huffmanTreeTests.o build/HuffmanTree.o
	$(CXX) $(CXXFLAGS) build/huffmanTreeTests.o build/HuffmanTree.o -o bin/huffmanTreeTest

build/huffmanTreeTests.o: tests/huffmanTreeTests.cpp
	$(CXX) $(CXXFLAGS) -c tests/huffmanTreeTests.cpp -o build/huffmanTreeTests.o

build/HuffmanTree.o: src/HuffmanTree.cpp include/HuffmanTree.h
	$(CXX) $(CXXFLAGS) -c src/HuffmanTree.cpp -o build/HuffmanTree.o

test: $(TESTS)
	./bin/$(TESTS)

clean:
	rm build/*.o bin/*
