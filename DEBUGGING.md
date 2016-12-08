
Setup xcode (https://www.youtube.com/watch?v=DND2H2-XfAc):

$ node-gyp configure -- -f xcode
$ open build/binding.xcodeproj

xcode$ Edit Scheme -> Info -> Executable -> shift + command + G -> copy value from $ which node
xcode$ Edit Scheme -> Info -> Arguments -> set path from $ $PWD/mocha.js

Rename libtensorflow.so to libtensorflow.dylib and update the location of the library:

$ sudo install_name_tool -id "$PWD/vendor/libtensorflow.dylib" vendor/libtensorflow.dylib
$ otool -L vendor/libtensorflow.dylib

##$ sudo install_name_tool -id "$PWD/vendor/libtensorflow.so" vendor/libtensorflow.so
##$ otool -L vendor/libtensorflow.so
