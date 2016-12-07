const path = require('path');
const execa = require('execa');
let removeSync = require('fs-extra').removeSync;

const sectionLog = require('./lib/section_log');
const tensorflowDirectory = require('./lib/tensorflow_directory');

const BAZEL_LINKS = require('./lib/bazel_links');
const VENDOR_DIRECTORY = require('./lib/vendor_directory');

tensorflowDirectory((err, tensorflow_directory) => {
  if (err) throw err;

  try {
    removeSync(VENDOR_DIRECTORY);
    BAZEL_LINKS.forEach(link => removeSync(path.resolve(path.join(__dirname, '..', link))));
    BAZEL_LINKS.forEach(link => removeSync(path.resolve(tensorflow_directory, link)));
    console.log(''); sectionLog('Tensorflow clean successful');
  }
  catch (err) {
    console.log(''); sectionLog('Tensorflow clean failed. Error:' + err.message);
  }
});
