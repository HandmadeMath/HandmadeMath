ifeq ($(OS),Windows_NT)
RM = del /Q /F
RMDIR = rmdir /Q /S
CP = copy /Y
PYTHON = python
PIP = pip
else
RM = rm -rf
RMDIR = rm -rf
CP = cp -f
PYTHON = python3
PIP = pip3
endif

BUILD_DIR=build

all: example

example: lib/flextgl/flextgl.h
	$(RMDIR) $(BUILD_DIR)
	mkdir $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CC) -std=c99 -c -lm \
			-I../lib/glfw/include \
			-I../lib/flextgl \
			-I../lib/EGL-Registry/api \
			../src/main.c ../lib/flextgl/flextGL.c \
		&& $(CC) -ohmm_example.exe main.o -lm

flextgl-deps:
	$(PIP) install --user wheezy.template

lib/flextgl/flextgl.h lib/flextgl/flextgl.c: flextgl-deps
	$(PYTHON) lib/flextgl-gen/flextGLgen.py -D lib/flextgl -T glfw3 flextgl-profile.txt
