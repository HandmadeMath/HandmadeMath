BUILD_DIR=./build

CXXFLAGS+=-g -Wall -Wextra -pthread -Wno-missing-braces -Wno-missing-field-initializers -Wfloat-equal

all: c c_no_sse cpp cpp_no_sse build_c_without_coverage build_cpp_without_coverage

build_all: build_c build_c_no_sse build_cpp build_cpp_no_sse

clean:
	rm -rf $(BUILD_DIR)

c: build_c
	$(BUILD_DIR)/hmm_test_c

build_c: HandmadeMath.c test_impl
	@echo "\nCompiling in C mode"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR)\
		&& $(CC) $(CPPFLAGS) $(CXXFLAGS) -std=c99 \
			-c ../HandmadeMath.c ../hmm_test.c \
			-lm \
		&& $(CC) -ohmm_test_c HandmadeMath.o hmm_test.o -lm

c_no_sse: build_c_no_sse
	$(BUILD_DIR)/hmm_test_c_no_sse

build_c_no_sse: HandmadeMath.c test_impl
	@echo "\nCompiling in C mode (no SSE)"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CC) $(CPPFLAGS) $(CXXFLAGS) -std=c99 \
			-DHANDMADE_MATH_NO_SSE \
			-c ../HandmadeMath.c ../hmm_test.c \
			-lm \
		&& $(CC) -ohmm_test_c_no_sse HandmadeMath.o hmm_test.o -lm

cpp: build_cpp
	$(BUILD_DIR)/hmm_test_cpp

build_cpp: HandmadeMath.cpp test_impl
	@echo "\nCompiling in C++ mode"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CXX) $(CPPFLAGS) $(CXXFLAGS) -ohmm_test_cpp \
			-DHANDMADE_MATH_CPP_MODE \
			../HandmadeMath.cpp ../hmm_test.cpp

cpp_no_sse: build_cpp_no_sse
	$(BUILD_DIR)/hmm_test_cpp_no_sse

build_cpp_no_sse: HandmadeMath.cpp test_impl
	@echo "\nCompiling in C++ mode (no SSE)"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CXX) $(CPPFLAGS) $(CXXFLAGS) -ohmm_test_cpp_no_sse \
			-DHANDMADE_MATH_CPP_MODE -DHANDMADE_MATH_NO_SSE \
			../HandmadeMath.cpp ../hmm_test.cpp

test_impl: hmm_test.cpp hmm_test.c

build_c_without_coverage: HandmadeMath.c
	@echo "\nCompiling in C mode"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR)\
		&& $(CC) $(CPPFLAGS) $(CXXFLAGS) -std=c99 \
			-DWITHOUT_COVERAGE \
			-c ../HandmadeMath.c ../hmm_test.c \
			-lm \
		&& $(CC) -ohmm_test_c HandmadeMath.o hmm_test.o -lm

build_cpp_without_coverage: HandmadeMath.cpp test_impl
	@echo "\nCompiling in C++ mode (no SSE)"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CXX) $(CPPFLAGS) $(CXXFLAGS) -ohmm_test_cpp_no_sse \
			-DHANDMADE_MATH_CPP_MODE -DWITHOUT_COVERAGE \
			../HandmadeMath.cpp ../hmm_test.cpp
