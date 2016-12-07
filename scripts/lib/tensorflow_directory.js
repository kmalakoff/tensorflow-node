const path = require('path');
const execa = require('execa');

let tensorflow_directory = null;

module.exports = function(callback) {
  if (tensorflow_directory) return callback(tensorflow_directory);

  execa('bazel', ['info', 'output_base'], {stderr: 'inherit'})
  .then(result => {
    if (result.code != 0) throw new Error('Failed to find tensorflow');

    // cache the reference to tensorflow_directory
    tensorflow_directory = path.join(result.stdout, 'external', 'org_tensorflow');
    callback(null, tensorflow_directory)
  })
  .catch(err => callback(err))
}
