const _tf = require('../nan_addons');

module.exports = class Graph {
  constructor() { this._ = new _tf.Graph(); }

  input() { return this._.input(); }
  constant(v) { return this._.constant(v); }
  add(l, r) { return this._.add(l, r); }
  matmul(l, r) { return this._.matmul(l, r); }
  run(ops, input_pairs) { return this._.run(ops, input_pairs); }
};
