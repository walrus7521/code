
md build
cd build
cmake ..
msbuild solution.sln /t:solution
msbuild solution.sln /t:jsontest
msbuild INSTALL.vcxproj
