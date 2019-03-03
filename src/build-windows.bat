::the old command
::g++ -o ../bin/airport-renderer-windows.exe earthAirportPrototype.cpp -I./deps -L./deps -static-libgcc -static-libstdc++ -static -DGLEW_STATIC -lglu32 -lglfw3 -lgdi32 -lopengl32 -std=c++11


::The new one with nfd
g++ -o ../bin/airport-renderer-windows.exe earthAirportPrototype.cpp ./deps/NativeFileDialog/src/nfd_common.c ./deps/NativeFileDialog/src/nfd_win.cpp -I./deps -L./deps -static-libgcc -static-libstdc++ -static -DGLEW_STATIC -lglu32 -lglfw3 -lgdi32 -lopengl32 -L./deps/NativeFileDialog/build/lib/Release/x64/nfd.lib -lole32 -luuid -I./deps/NativeFileDialog/include -std=c++11
