const execa = require('execa');

const sectionLog = require('./lib/section_log');

// Build tensorflow
sectionLog('Building tensorflow'); console.log('');
let cmd = 'swig -javascript -node -c++ -o src/tensorflow_wrap.cxx -DV8_VERSION=0x054500 src/tensorflow.i'.split(' ')
execa(cmd.shift(), cmd, {stdio: 'inherit', stderr: 'inherit'})

// Build library
.then(result => {
  if (result.code != 0) throw new Error('Failed to link tensorflow');

  let cmd = 'node-gyp configure build --directory=scripts'.split(' ')
  return execa(cmd.shift(), cmd, {stdio: 'inherit', stderr: 'inherit'})
})

// done
.then(result => {
  if(result.code != 0) throw new Error('Failed to build');
  console.log(''); sectionLog('Tensorflow build successful');
})
.catch(err => {
  console.log(''); sectionLog('Tensorflow build failed. Error:' + err.message);
});
