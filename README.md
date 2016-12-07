# tensorflow.js
Tensorflow for node.js

Installation and building
===========================================================
Until tensorflow binaries are distributed, this module requires a one-time configuration process. In the meantime, you will need to install the full tensorflow pipeline including bazel and python: https://www.tensorflow.org/versions/r0.12/get_started/os_setup.html

```
npm install
npm run configure   # for changes to the tensorflow library
npm run build       # for changes to tensorflow.js C++ bindings
```

Test
===========================================================

```
npm run test
```

Test
===========================================================

```
node examples/simple.js
```
