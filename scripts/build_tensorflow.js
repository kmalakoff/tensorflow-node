const fs = require('fs');
const path = require('path');
const execa = require('execa');

const sectionLog = require('./lib/section_log');
const tensorflowDirectory = require('./lib/tensorflow_directory');
const VENDOR_LINKS = require('./lib/vendor_links');
const VENDOR_DIRECTORY = require('./lib/vendor_directory'); require('fs-extra').mkdirsSync(VENDOR_DIRECTORY);

tensorflowDirectory((err, tensorflow_directory) => {
  if (err) throw err;

  // Build tensorflow
  sectionLog('Building tensorflow'); console.log('');
  let cmd = 'bazel build -c opt //tensorflow:libtensorflow.so'.split(' ')
  execa(cmd.shift(), cmd, {cwd: tensorflow_directory, stdio: 'inherit', stderr: 'inherit'})

  // Link tensorflow into vendor
  .then(result => {
    if(result.code != 0) throw new Error('Failed to build tensorflow');

    sectionLog('Linking tensorflow'); console.log('');
    VENDOR_LINKS.forEach(link => {
      try { fs.linkSync(path.join(tensorflow_directory, link), path.join(VENDOR_DIRECTORY, link)); }
      catch (err) { if (err.code != 'EEXIST') console.log(err); }
    });
    console.log('Linked vendor: ' + VENDOR_LINKS.join(' '));
  })

  // Link tensorflow shared library
  .then(() => {
    try { fs.linkSync(path.join(VENDOR_DIRECTORY, 'bazel-out', 'local-opt'), path.resolve(path.join(__dirname, '..', 'bazel-out', 'local-opt'))); }
    catch (err) { if (err.code != 'EEXIST') console.log(err); }

    let lib_dir = path.resolve(path.join(__dirname, '..', 'bazel-out', 'local-opt', 'bin', 'tensorflow'))
    try { fs.linkSync(path.join(lib_dir, 'libtensorflow.so'), path.join(lib_dir, 'libtensorflow.dylib')) }
    catch (err) { if (err.code != 'EEXIST') console.log(err); }

    console.log('Linked shared library: ' + path.join('bazel-out', 'local-opt'));
  })

  // done
  .then(() => {
    console.log(''); sectionLog('Tensorflow build successful');
  })
  .catch(err => {
    console.log(''); sectionLog('Tensorflow build failed. Error:' + err.message);
  });
});
