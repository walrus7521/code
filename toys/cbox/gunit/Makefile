# Where to find user code.
USER_DIR = .

CXX = /usr/local/opt/llvm/bin/clang++
# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -std=c++11 -fprofile-instr-generate -fcoverage-mapping

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = unit_test
RUN_TESTS = run_unit_tests

# House-keeping build targets.
all : $(TESTS) $(RUN_TESTS)
unit: $(TESTS)
test: $(RUN_TESTS)

clean :
	rm -f $(TESTS) *.o foo.profdata foo.profraw foo.report

unit_test.o : $(USER_DIR)/unit_test.cpp \
                     $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/unit_test.cpp

unit_test : unit_test.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lgtest -lgtest_main $^ -o $@

run_unit_tests:
	LLVM_PROFILE_FILE="foo.profraw" ./unit_test
	/usr/local/opt/llvm/bin/llvm-profdata merge -sparse foo.profraw -o foo.profdata
	/usr/local/opt/llvm/bin/llvm-cov show ./unit_test -instr-profile=foo.profdata > foo.show
	/usr/local/opt/llvm/bin/llvm-cov report ./unit_test -instr-profile=foo.profdata > foo.report
	vi foo.report

