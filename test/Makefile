BUILD_DIR=./build

CXXFLAGS+=-g -Wall -Wextra -pthread -Wno-missing-braces -Wno-missing-field-initializers -Wfloat-equal

.PHONY: all all_c all_cpp
all: all_c all_cpp
all_c: c99 c99_no_simd c11 c17
all_cpp: cpp98 cpp98_no_simd cpp03 cpp11 cpp14 cpp17 cpp20

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: c99
c99:
	@echo "\nCompiling as C99"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR)\
		&& $(CC) $(CPPFLAGS) $(CXXFLAGS) -std=c99 \
			../HandmadeMath.c ../hmm_test.c \
			-lm -o hmm_test_c99 \
		&& ./hmm_test_c99

.PHONY: c99_no_simd
c99_no_simd:
	@echo "\nCompiling as C99 (no SIMD)"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CC) $(CPPFLAGS) $(CXXFLAGS) -std=c99 \
			-DHANDMADE_MATH_NO_SIMD \
			../HandmadeMath.c ../hmm_test.c \
			-lm -o hmm_test_c99_no_simd \
		&& ./hmm_test_c99_no_simd

.PHONY: c11
c11:
	@echo "\nCompiling as C11"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR)\
		&& $(CC) $(CPPFLAGS) $(CXXFLAGS) -std=c11 \
			../HandmadeMath.c ../hmm_test.c \
			-lm -o hmm_test_c11 \
		&& ./hmm_test_c11

.PHONY: c17
c17:
	@echo "\nCompiling as C17"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR)\
		&& $(CC) $(CPPFLAGS) $(CXXFLAGS) -std=c17 \
			../HandmadeMath.c ../hmm_test.c \
			-lm -o hmm_test_c17 \
		&& ./hmm_test_c17

.PHONY: cpp98
cpp98:
	@echo "\nCompiling as C++98"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CXX) $(CPPFLAGS) $(CXXFLAGS) -std=c++98 \
			../HandmadeMath.cpp ../hmm_test.cpp \
			-lm -o hmm_test_cpp98 \
		&& ./hmm_test_cpp98

.PHONY: cpp98_no_simd
cpp98_no_simd:
	@echo "\nCompiling as C++98 (no SIMD)"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CXX) $(CPPFLAGS) $(CXXFLAGS) -std=c++98 \
			-DHANDMADE_MATH_NO_SIMD \
			../HandmadeMath.cpp ../hmm_test.cpp \
			-lm -o hmm_test_cpp98 \
		&& ./hmm_test_cpp98

.PHONY: cpp03
cpp03:
	@echo "\nCompiling as C++03"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CXX) $(CPPFLAGS) $(CXXFLAGS) -std=c++03 \
			../HandmadeMath.cpp ../hmm_test.cpp \
			-lm -o hmm_test_cpp03 \
		&& ./hmm_test_cpp03

.PHONY: cpp11
cpp11:
	@echo "\nCompiling as C++11"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CXX) $(CPPFLAGS) $(CXXFLAGS) -std=c++11 \
			../HandmadeMath.cpp ../hmm_test.cpp \
			-lm -o hmm_test_cpp11 \
		&& ./hmm_test_cpp11

.PHONY: cpp14
cpp14:
	@echo "\nCompiling as C++14"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CXX) $(CPPFLAGS) $(CXXFLAGS) -std=c++14 \
			../HandmadeMath.cpp ../hmm_test.cpp \
			-lm -o hmm_test_cpp14 \
		&& ./hmm_test_cpp14

.PHONY: cpp17
cpp17:
	@echo "\nCompiling as C++17"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CXX) $(CPPFLAGS) $(CXXFLAGS) -std=c++17 \
			../HandmadeMath.cpp ../hmm_test.cpp \
			-lm -o hmm_test_cpp17 \
		&& ./hmm_test_cpp17

.PHONY: cpp20
cpp20:
	@echo "\nCompiling as C++20"
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& $(CXX) $(CPPFLAGS) $(CXXFLAGS) -std=c++20 \
			../HandmadeMath.cpp ../hmm_test.cpp \
			-lm -o hmm_test_cpp20 \
		&& ./hmm_test_cpp20
