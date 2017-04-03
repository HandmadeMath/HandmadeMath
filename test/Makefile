ROOT_DIR = ..

CXXFLAGS += -g -Wall -Wextra -pthread -Wno-missing-braces -Wno-missing-field-initializers

all: c cpp

clean:
	rm -f hmm_test_c hmm_test_cpp *.o

c: $(ROOT_DIR)/test/HandmadeMath.c test_impl
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -std=c99 -lm -c $(ROOT_DIR)/test/HandmadeMath.c $(ROOT_DIR)/test/hmm_test.c
	$(CC) -ohmm_test_c -lm HandmadeMath.o hmm_test.o

cpp: $(ROOT_DIR)/test/HandmadeMath.cpp test_impl
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -ohmm_test_cpp $(ROOT_DIR)/test/HandmadeMath.cpp $(ROOT_DIR)/test/hmm_test.cpp

test_impl: $(ROOT_DIR)/test/hmm_test.cpp $(ROOT_DIR)/test/hmm_test.c
