const _tf = require('./addons');

let tf = {
  // version: _tf.TF_VERSION_STRING,
  Graph: require('./graph'),
  Session: require('./session')
}

Object.assign(tf, _tf.Constants);
Object.assign(tf, _tf.Types);

module.exports = tf;
 