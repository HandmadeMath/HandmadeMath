ROOT_DIR = ..

CXXFLAGS += -g -Wall -Wextra -pthread -Wno-missing-braces -Wno-missing-field-initializers

all: c c_no_sse cpp cpp_no_sse

clean:
	rm -f hmm_test_c hmm_test_cpp hmm_test_c_no_sse hmm_test_cpp_no_sse *.o

c: $(ROOT_DIR)/test/HandmadeMath.c test_impl
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -std=c99 -c $(ROOT_DIR)/test/HandmadeMath.c $(ROOT_DIR)/test/hmm_test.c -lm
	$(CC) -ohmm_test_c HandmadeMath.o hmm_test.o -lm

c_no_sse: $(ROOT_DIR)/test/HandmadeMath_NoSSE.c test_impl
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -std=c99 -c $(ROOT_DIR)/test/HandmadeMath_NoSSE.c $(ROOT_DIR)/test/hmm_test.c -lm
	$(CC) -ohmm_test_c_no_sse HandmadeMath_NoSSE.o hmm_test.o -lm

cpp: $(ROOT_DIR)/test/HandmadeMath.cpp test_impl
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -ohmm_test_cpp $(ROOT_DIR)/test/HandmadeMath.cpp $(ROOT_DIR)/test/hmm_test.cpp

cpp_no_sse: $(ROOT_DIR)/test/HandmadeMath_NoSSE.cpp test_impl
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -ohmm_test_cpp_no_sse $(ROOT_DIR)/test/HandmadeMath_NoSSE.cpp $(ROOT_DIR)/test/hmm_test.cpp

test_impl: $(ROOT_DIR)/test/hmm_test.cpp $(ROOT_DIR)/test/hmm_test.c
