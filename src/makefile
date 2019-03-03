DEPS_DIR = ./deps

NFD_DIR = $(DEPS_DIR)/NativeFileDialog


GTK_LIB = `pkg-config --cflags --libs gtk+-3.0`
LIBSLINUX = -static-libstdc++ -lGLEW -lglfw3 -lGL -lX11 -lXxf86vm -lpthread -ldl -lXrandr -lXinerama -lXcursor -lm -L$(NFD_DIR)/build/lib/Release/x64/libnfd.a $(GTK_LIB) 
LIBSWIN =-static-libgcc -static-libstdc++ -static -DGLEW_STATIC -lglu32 -lglfw3 -lgdi32 -lopengl32 -L$(NFD_DIR)/build/lib/Release/x64/nfd.lib -lole32 -luuid

INCLUDES = -I$(NFD_DIR)/include

TARGET_RENDERER = airport-renderer
TARGET_TESTER = testing-airport-renderer

TARGETLINUX = ../bin/$(TARGET_RENDERER)-linux.elf
TARGETWIN = ../bin/$(TARGET_RENDERER)-windows.exe
TARGETWINBACKSLASH = ..\bin\\$(TARGET_RENDERER)-windows.exe

TARGETLINUX_TESTER = ../bin/$(TARGET_TESTER)-linux.elf
TARGETWIN_TESTER = ../bin/$(TARGET_TESTER)-windows.exe
TARGETWINBACKSLASH_TESTER = ..\bin\\$(TARGET_TESTER)-windows.exe


REFERENCES = $(NFD_DIR)/src/nfd_common.c
REFERENCESLINUX = $(REFERENCES) $(NFD_DIR)/src/nfd_gtk.c
REFERENCESWIN = $(REFERENCES) $(NFD_DIR)/src/nfd_win.cpp


objects = earthAirportPrototype.cpp
objects_tester = testing/testingmain.cpp

ifeq ($(OS),Windows_NT)
COMPILER_CMD_WIN = $(CXX)
DELETE_CMD = DEL
else
COMPILER_CMD_WIN = x86_64-w64-mingw32-g++
DELETE_CMD = rm -f
endif

ifeq ($(OS),Windows_NT)
all: windows
else
all: linux
endif

linux: $(TARGETLINUX)
windows: $(TARGETWIN)

ifeq ($(OS),Windows_NT)
test: $(TARGETWIN_TESTER)
else
test: $(TARGETLINUX_TESTER)
endif


ifeq ($(OS),Windows_NT)
clean: clean-windows
else
clean: clean-linux
clean-all: clean-linux clean-windows
endif

$(TARGETLINUX): $(objects)
	$(CXX) -o $@ $^ $(REFERENCESLINUX) $(LIBSLINUX) $(INCLUDES) -std=c++11

$(TARGETLINUX_TESTER): $(objects_tester)
	$(CXX) -o $@ $^ $(REFERENCESLINUX) $(LIBSLINUX) $(INCLUDES) -std=c++11

clean-linux:
	$(DELETE_CMD) $(TARGETLINUX)
	$(DELETE_CMD) $(TARGETLINUX_TESTER)

$(TARGETWIN): $(objects)
	$(COMPILER_CMD_WIN) -o $@ $^ $(REFERENCESWIN) -I./deps -L./deps $(LIBSWIN) $(INCLUDES) -std=c++11

$(TARGETWIN_TESTER): $(objects_tester)
	$(COMPILER_CMD_WIN) -o $@ $^ $(REFERENCESWIN) -I./deps -L./deps $(LIBSWIN) $(INCLUDES) -std=c++11

clean-windows:
ifeq ($(OS),Windows_NT)
	$(DELETE_CMD) $(TARGETWINBACKSLASH)
	$(DELETE_CMD) $(TARGETWINBACKSLASH_TESTER)
else
	$(DELETE_CMD) $(TARGETWIN)
	$(DELETE_CMD) $(TARGETWIN_TESTER)
endif

