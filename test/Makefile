ROOT_DIR=..

CXXFLAGS+=-g -Wall -Wextra -pthread -Wno-missing-braces -Wno-missing-field-initializers

all: c c_no_sse cpp cpp_no_sse

clean:
	rm -rf build

c: $(ROOT_DIR)/test/HandmadeMath.c test_impl
	@echo "\nCompiling in C mode"
	mkdir -p build
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -std=c99 \
		-c $(ROOT_DIR)/test/HandmadeMath.c $(ROOT_DIR)/test/hmm_test.c \
		-lm
	$(CC) -obuild/hmm_test_c HandmadeMath.o hmm_test.o -lm

c_no_sse: $(ROOT_DIR)/test/HandmadeMath.c test_impl
	@echo "\nCompiling in C mode (no SSE)"
	mkdir -p build
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -std=c99 \
	    -DHANDMADE_MATH_NO_SSE \
	    -c $(ROOT_DIR)/test/HandmadeMath.c $(ROOT_DIR)/test/hmm_test.c \
	    -lm
	$(CC) -obuild/hmm_test_c_no_sse HandmadeMath.o hmm_test.o -lm

cpp: $(ROOT_DIR)/test/HandmadeMath.cpp test_impl
	@echo "\nCompiling in C++ mode"
	mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -obuild/hmm_test_cpp \
		-DHANDMADE_MATH_CPP_MODE \
		$(ROOT_DIR)/test/HandmadeMath.cpp $(ROOT_DIR)/test/hmm_test.cpp

cpp_no_sse: $(ROOT_DIR)/test/HandmadeMath.cpp test_impl
	@echo "\nCompiling in C++ mode (no SSE)"
	mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -obuild/hmm_test_cpp_no_sse \
		-DHANDMADE_MATH_CPP_MODE -DHANDMADE_MATH_NO_SSE \
		$(ROOT_DIR)/test/HandmadeMath.cpp $(ROOT_DIR)/test/hmm_test.cpp

test_impl: $(ROOT_DIR)/test/hmm_test.cpp $(ROOT_DIR)/test/hmm_test.c
