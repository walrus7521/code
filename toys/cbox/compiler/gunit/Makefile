# Where to find user code.
USER_DIR = .

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -std=c++11

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = unit_test

# House-keeping build targets.
all : $(TESTS)

clean :
	rm -f $(TESTS) *.o

unit_test.o : $(USER_DIR)/unit_test.cpp \
                     $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/unit_test.cpp

unit_test : unit_test.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lgtest -lgtest_main $^ -o $@
