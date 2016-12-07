const execa = require('execa');

const sectionLog = require('./lib/section_log');

// Build tensorflow
sectionLog('Building tensorflow'); console.log('');
let cmd = 'node-gyp configure build --directory=scripts'.split(' ')
execa(cmd.shift(), cmd, {stdio: 'inherit', stderr: 'inherit'})

// done
.then(result => {
  if(result.code != 0) throw new Error('Failed to build');
  console.log(''); sectionLog('Tensorflow build successful');
})
.catch(err => {
  console.log(''); sectionLog('Tensorflow build failed. Error:' + err.message);
});
