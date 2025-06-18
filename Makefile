CXX := clang++
CXXFLAGS := -std=c++17 -Wall

TESTS := huffmanTreeTests encodeTests

all:

huffmanTreeTests: build/huffmanTreeTests.o build/HuffmanTree.o
	$(CXX) $(CXXFLAGS) build/huffmanTreeTests.o build/HuffmanTree.o -o bin/huffmanTreeTests

encodeTests: build/encodeTests.o build/Encode.o build/HuffmanTree.o
	$(CXX) $(CXXFLAGS) build/encodeTests.o build/Encode.o build/HuffmanTree.o -o bin/encodeTests

build/huffmanTreeTests.o: tests/huffmanTreeTests.cpp
	$(CXX) $(CXXFLAGS) -c tests/huffmanTreeTests.cpp -o build/huffmanTreeTests.o

build/encodeTests.o: tests/encodeTests.cpp
	$(CXX) $(CXXFLAGS) -c tests/encodeTests.cpp -o build/encodeTests.o

build/HuffmanTree.o: src/HuffmanTree.cpp include/HuffmanTree.h
	$(CXX) $(CXXFLAGS) -c src/HuffmanTree.cpp -o build/HuffmanTree.o

build/Encode.o: src/Encode.cpp include/Encode.h include/HuffmanTree.h
	$(CXX) $(CXXFLAGS) -c src/Encode.cpp -o build/Encode.o

test: $(TESTS)
	@for test in $(TESTS); do \
		./bin/$$test; \
	done

clean:
	rm build/* bin/*
