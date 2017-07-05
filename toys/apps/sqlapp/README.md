md build
cd build
cmake ..
msbuild solution.sln /t:solution
msbuild INSTALL.vcxproj

install gmake: git clone googletest, cmake, make install

notes:
build: gcc -l sqlite3 orm.c 
http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
https://github.com/paulftw/hiberlite
http://www.qxorm.com/qxorm_en/home.html

