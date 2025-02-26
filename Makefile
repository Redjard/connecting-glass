# get the mod name from info.json5
MOD_NAME := "$(shell grep -Po 'name\s*:\s*"[^"]*' info.json5 | grep -Po '(?<=")[^"]*')"

# configure mingw as the compiler
CC=x86_64-w64-mingw32-g++

# 4dm.h will spam your compiler output otherwise
HIDE_SOME_WARNINGS=-Wno-return-type -Wno-conversion-null -Wno-return-local-addr
CFLAGS=-std=c++20 -mwindows $(HIDE_SOME_WARNINGS) -s -O3 -flto=auto


INCLUDE=-I 4dm.h/ -I 4dm.h/networking/include/

# ./4dm.h/networking/lib/*;./4dm.h/soil/SOIL.lib;opengl32.lib;glew32.lib;glfw3.lib
NETLIBS=$(shell find 4dm.h/networking/lib/*.lib -not -name steamwebrtc.lib -not -name webrtc-lite.lib)
CLIBS=-L. $(patsubst %.lib,-l %,$(NETLIBS)) -L. -l opengl32   -Wl,-Bdynamic  -l glew32 -l glfw3  -Wl,-Bstatic
# CLIBS=-L. $(patsubst %.lib,-l %,$(wildcard 4dm.h/networking/lib/*.lib)) -L 4dm.h/soil -l SOIL -L. -l opengl32   -Wl,-Bdynamic  -l glew32 -l glfw3  -Wl,-Bstatic


default: compile
compile:
	$(CC) $(CFLAGS) $(INCLUDE)   main.cpp   -shared -static $(CLIBS)   -o $(MOD_NAME).dll

DEST = ~/"steam/4D Miner/_currMod/mods/"

install:
	cd $(DEST) && mkdir -p $(MOD_NAME)
	cp $(MOD_NAME).dll info.json5 icon.png $(DEST)$(MOD_NAME)/ ;true
	[ -d assets/ ] && [ "$(shell ls -A assets)" ] && cp assets/* $(DEST)$(MOD_NAME)/ ;true

clean:
	rm $(MOD_NAME).dll
