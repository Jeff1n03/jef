CXX ?= g++
CXXFLAGS := -std=c++17 -Wall -O2

all: bin/jef

install: bin/jef
	install -d /usr/local/bin/
	install -m 755 $< /usr/local/bin/

bin/jef: build/main.o build/Decode.o build/Encode.o build/HuffmanTree.o | bin
	$(CXX) $(CXXFLAGS) $^ -o $@

build/HuffmanTree.o: src/HuffmanTree.cpp include/HuffmanTree.h include/config.h | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Encode.o: src/Encode.cpp include/Encode.h include/HuffmanTree.h include/config.h | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Decode.o: src/Decode.cpp include/Decode.h include/Encode.h include/config.h | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/main.o: src/main.cpp include/Decode.h include/Encode.h include/config.h | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin build:
	mkdir -p $@

clean:
	rm build/* bin/*

.PHONY: all install clean
