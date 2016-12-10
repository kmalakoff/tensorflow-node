const _tf = require('./addons');

module.exports = class Session {
  constructor(graph) {
    this._ = new _tf.Session(graph._);
  }

  run(ops, input_pairs) { return this._.run(ops, input_pairs); }
  runNoOut(ops, input_pairs) { return this._.runNoOut(ops, input_pairs); }
};
