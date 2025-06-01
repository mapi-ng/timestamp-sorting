# timestamp-sorting

## Prerequisites
- Internet connection (for CMake FetchContent module)
- CMake version at least 3.26.2
- Compiler with support for C++20

## Build instructions
From command line, execute the commands below (replace Debug by Release if relevant):

```
mkdir build
cmake -S. -B./build
cmake --build ./build --config Debug
```

## Running tests

From the build directory, run:
```
ctest -C Debug --output-on-failure
```

## Running the application
From the build directory, run:
```
timestamp-sorting-app
```

## Comments

Program works correctly on computers with little-endian architecture. To account for different endianness, file reading and writing should be performed by single bytes, taking into account the order.

Time complexity of implemented solution is O(m n log n), where *m* is the number of frames and *n* is the number of events in a frame (on average). With each new frame, a series of events from time span up to 1024 ns needs to be sorted.

Space complexity is constant, because input data is read as stream, processed on the fly and written to file as output stream. Total file size does not have impact on memory use. Only data from up to two frames is processed, unless their time spans are much smaller than 1024 ns.

## Possibilities of improvement

As events can only be delayed by up to 100 ns, it is not necessary to sort full frames.

An idea worth exploring would be a window of 200 ns used to limit sorted range and moved by 100 ns until the end of each frame. This allows sorting smaller ranges of data, but with more frequency than once per frame.