const _tf = require('./nan/addons');

let tf = {
  // version: _tf.TF_VERSION_STRING,
  Graph: require('./core/graph')
}

// Object.assign(tf, require('./core/types'));

module.exports = tf;
