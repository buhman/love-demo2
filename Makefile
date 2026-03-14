#PREFIX = x86_64-w64-mingw32-
CC=$(PREFIX)gcc
CXX=$(PREFIX)g++

OPT = -O2 -march=x86-64-v3

CSTD = -std=gnu23
CXXSTD = -std=gnu++23
CFLAGS += -g
CFLAGS += -fpic
CFLAGS += -I./include
CFLAGS += -Wall -Werror -Wfatal-errors -Wno-error=unused-variable -Wno-error=unused-but-set-variable
CFLAGS += -Wno-error=unknown-pragmas -Wno-unknown-pragmas
CFLAGS += $(shell pkg-config --cflags glfw3)
CFLAGS += -fno-strict-aliasing

LDFLAGS += -lm
LDFLAGS += $(shell pkg-config --libs glfw3)

OBJS = \
	src/gl.o \
	src/opengl.o \
	src/test.o \
	src/font.o \
	src/window.o \
	src/bresenham.o \
	src/file.o \
	src/world.o \
	src/inthash.o \
	src/non_block.o \
	src/view.o \
	src/minecraft.o \
	src/hud.o \
	src/lighting.o \
	src/collision_scene.o

all: test.so

%.o: %.c
	$(CC) $(ARCH) $(CSTD) $(CFLAGS) $(OPT) -c $< -o $@

%.o: %.cpp
	$(CXX) $(ARCH) $(CXXSTD) $(CFLAGS) $(OPT) -c $< -o $@

test.so: $(OBJS)
	$(CC) $(ARCH) $(OPT) -shared -g $^ -o $@ -lSDL3

main: $(OBJS) src/main.o
	$(CC) $(ARCH) $(LDFLAGS) $(OPT) -g $^ -o $@

clean:
	find . -type f ! -name "*.*" -delete

.SUFFIXES:
.INTERMEDIATE:
.SECONDARY:
.PHONY: all clean phony

%: RCS/%,v
%: RCS/%
%: %,v
%: s.%
%: SCCS/s.%
