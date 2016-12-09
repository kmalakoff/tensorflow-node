const _tf = require('./nan_bridge');

let tf = {
  // version: _tf.TF_VERSION_STRING,
  Graph: require('./core/graph')
}

Object.assign(tf, _tf.CONSTANTS);
Object.assign(tf, _tf.TYPES);

module.exports = tf;
 