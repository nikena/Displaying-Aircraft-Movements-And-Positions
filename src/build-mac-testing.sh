#! /usr/bin/env bash
 g++ -o ../bin/testing-airport-renderer-mac.o testing/testingmain.cpp ./deps/NativeFileDialog/src/nfd_common.c ./deps/NativeFileDialog/src/nfd_cocoa.m -lglfw -framework Cocoa -framework OpenGL -framework IOkit -framework CoreVideo -framework Appkit -I./deps/NativeFileDialog/include -L./deps/NativeFileDialog/build/lib/Release/x64/ -Wno-c++11-extensions -Wno-c++11-extra-semi
