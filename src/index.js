const _tf = require('./addons');

let tf = {
  // version: _tf.TF_VERSION_STRING,
  Graph: require('./tensorflow/graph'),
  Session: require('./tensorflow/session')
}

Object.assign(tf, _tf.CONSTANTS);
Object.assign(tf, _tf.TYPES);

module.exports = tf;
 