const _tf = require('../native_bindings');

module.exports = class Graph {
  constructor() {
    this.graph_ = _tf.createGraph();
  }

  placeholder() { return _tf.Placeholder(this.graph_); }
  scalar(value) { return _tf.ScalarConst(this.graph_, value); }
  add(l, r) { return _tf.Add(this.graph_, l, r); }
  run(op1, op2) { return _tf.run(this.graph_, op1, op2); }
}
