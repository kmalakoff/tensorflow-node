
Setup xcode (https://www.youtube.com/watch?v=DND2H2-XfAc):

$ node-gyp configure -- -f xcode
$ open build/binding.xcodeproj

xcode$ Edit Scheme -> Info -> Executable -> shift + command + G -> copy value from $ which node
xcode$ Edit Scheme -> Info -> Arguments -> set path from $ $PWD/test/index.js

Note libtensorflow.dylib was renamed to libtensorflow.so for xcode to work.
