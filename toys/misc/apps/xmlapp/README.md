http://www.grinninglizard.com/tinyxmldocs/tutorial0.html

md build
cd build
cmake ..
msbuild solution.sln /t:solution
msbuild INSTALL.vcxproj

note: install gtest by: git clone, and cmake, and make install
