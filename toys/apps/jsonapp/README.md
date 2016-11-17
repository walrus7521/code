
md build
cd build
cmake ..
msbuild solution.sln /t:solution
msbuild INSTALL.vcxproj
