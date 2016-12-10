const _tf = require('../nan_bridge');

class NeuralNetwork {
  constructor(graph) { this.graph = graph; }

  softmax() {}
}

class GradientDescentOptimizer {
  constructor(graph) { this.graph = graph; }

  minimize() { return this.graph.add(this.graph.constant(1), this.graph.constant(2)); }
}

class Train {
  constructor(graph) { this.graph = graph; }

  GradientDescentOptimizer() { return new GradientDescentOptimizer(this.graph); }
}

module.exports = class Graph {
  constructor() {
    this._ = new _tf.Graph();
    this.nn = new NeuralNetwork(this);
    this.train = new Train(this);
  }

  input(arg1, arg2) { return this._.placeholder(arg1, arg2); }
  variable(v) { return this._.variable(v); }
  constant(v) { return this._.constant(v); }
  run(ops, input_pairs) { return this._.run(ops, input_pairs); }

  reduce_mean() {}
  add(l, r) { return this._.add(l, r); }
  matmul(l, r) { return this._.matmul(l, r); }
  reduce_sum() {}
  log() {}

};
