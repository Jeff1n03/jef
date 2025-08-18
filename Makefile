CXX := clang++
CXXFLAGS := -std=c++17 -Wall -O2

TESTS := bin/huffmanTreeTests bin/encodeTests bin/decodeTests

all: bin/jef

install: bin/jef
	install -d /usr/local/bin/
	install -m 755 $< /usr/local/bin/

bin/jef: build/main.o build/Decode.o build/Encode.o build/HuffmanTree.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/huffmanTreeTests: build/huffmanTreeTests.o build/HuffmanTree.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/encodeTests: build/encodeTests.o build/Encode.o build/HuffmanTree.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/decodeTests: build/decodeTests.o build/Decode.o build/Encode.o build/HuffmanTree.o
	$(CXX) $(CXXFLAGS) $^ -o $@

build/huffmanTreeTests.o: tests/huffmanTreeTests.cpp include/HuffmanTree.h include/config.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/encodeTests.o: tests/encodeTests.cpp include/Encode.h tests/testUtils.h include/config.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/decodeTests.o: tests/decodeTests.cpp include/Decode.h tests/testUtils.h include/config.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/HuffmanTree.o: src/HuffmanTree.cpp include/HuffmanTree.h include/config.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Encode.o: src/Encode.cpp include/Encode.h include/HuffmanTree.h include/config.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Decode.o: src/Decode.cpp include/Decode.h include/Encode.h include/config.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/main.o: src/main.cpp include/Decode.h include/Encode.h include/config.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TESTS)
	@printf "\n"
	@for test in $(TESTS); do \
		./$$test; \
		printf "\n"; \
	done

clean:
	rm build/* bin/*

.PHONY: all test clean
