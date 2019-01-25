
rem g++ -Ic:\gtest-1.6.0\include -Lc:\gtest-1.6.0\msvc\gtest\Debug -lc:\gtest-1.6.0\msvc\gtest\Debug\gtest_main-md.lib -lc:\gtest-1.6.0\msvc\gtest\Debug\gtest-md.lib unit_test.cpp
rem g++ -S -I"c:\gtest-1.6.0\include" unit_test.cpp
rem g++ -I"c:\gtest-1.6.0\include" -Lc:\gtest-1.6.0\msvc\gtest\Debug unit_test.cpp
rem g++ -I"c:\gtest-1.6.0\include" -L"c:\gtest-1.6.0\msvc\gtest\Debug" -l"c:\gtest-1.6.0\msvc\gtest\Debug\gtest_main-md.lib" -l"c:\gtest-1.6.0\msvc\gtest\Debug\gtest-md.lib" unit_test.cpp
g++ -I"c:\gtest-1.6.0\include" unit_test.cpp -L"c:\gtest-1.6.0\msvc\gtest\Debug" -L"gtest_main-md.lib" -L"gtest-md.lib"


