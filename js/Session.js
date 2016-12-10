const _tf = require('./addons');

module.exports = class Session {
  constructor(graph) {
    this._ = new _tf.Session(graph._);
  }

  run(ops, input_pairs) { return this._.run(ops, input_pairs); }
};
