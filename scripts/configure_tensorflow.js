const fs = require('fs');
const path = require('path');
const execa = require('execa');

const sectionLog = require('./lib/section_log');
const tensorflowDirectory = require('./lib/tensorflow_directory');

tensorflowDirectory((err, tensorflow_directory) => {
  if (err) throw err;

  // needs to be configured
  try {
    let needs_configure = !fs.statSync(tensorflow_directory);
    if (!needs_configure) { sectionLog('Tensorflow already configured. Skipping'); return; }
  } catch (err) {}

  // Bootstrap tensorflow
  sectionLog('Installing tensorflow');
  let cmd = 'bazel build @org_tensorflow//tensorflow:all_files'.split(' ')
  execa(cmd.shift(), cmd, {stdio: 'inherit', stderr: 'inherit'})

  // Configure tensorflow
  .then(result => {
    if (result.code != 0) throw new Error('Failed to install tensorflow');

    console.log(''); sectionLog('Configuring tensorflow'); console.log('');
    return execa(path.join(tensorflow_directory, 'configure'), {cwd: tensorflow_directory, stdio: 'inherit', stderr: 'inherit'})
  })

  // done
  .then(result => {
    if(result.code != 0) throw new Error('Failed to configure');
    console.log(''); sectionLog('Tensorflow install successful');
  })
  .catch(err => {
    console.log(''); sectionLog('Tensorflow install failed. Error:' + err.message);
  });
});
