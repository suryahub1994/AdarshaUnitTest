CXX = g++

.PHONY: all clean

all: build/test_runner

build/test_runner: Test/test.cpp | build
	$(CXX) Test/test.cpp -o $@

build:
	mkdir -p build

clean:
	rm -rf build
