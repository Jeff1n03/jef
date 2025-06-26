CXX := g++
CXXFLAGS := -std=c++17 -Wall -g # REMOVE DEBUG FLAG

TESTS := huffmanTreeTests encodeTests

all:

huffmanTreeTests: build/huffmanTreeTests.o build/HuffmanTree.o
	$(CXX) $(CXXFLAGS) $^ -o bin/$@

encodeTests: build/encodeTests.o build/Encode.o build/HuffmanTree.o
	$(CXX) $(CXXFLAGS) $^ -o bin/$@

build/huffmanTreeTests.o: tests/huffmanTreeTests.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/encodeTests.o: tests/encodeTests.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/HuffmanTree.o: src/HuffmanTree.cpp include/HuffmanTree.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Encode.o: src/Encode.cpp include/Encode.h include/HuffmanTree.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TESTS)
	@for test in $(TESTS); do \
		./bin/$$test; \
	done

clean:
	rm build/* bin/*

.PHONY: all test clean
