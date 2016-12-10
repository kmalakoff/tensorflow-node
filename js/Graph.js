const _tf = require('./addons');

function bindFn(graph, key, fns) { return function(...args) { return fns[key].apply(fns, [graph._].concat(args)); }; }
function bindFns(graph, root, fns) { for (var key in fns) root[key] = bindFn(graph, key, fns); }

module.exports = class Graph {
  constructor() {
    this._ = new _tf.Graph();

    bindFns(this, this, _tf.MathOps);
    this.nn = {}; bindFns(this, this.nn, _tf.NeuralNetwork);
    this.train = {}; bindFns(this, this.train, _tf.Train);
  }

  input(...args) { return this._.placeholder.apply(this._, args); }
  variable(...args) { return this._.variable.apply(this._, args); }
  variable_initializers(...args) { return this._.variable_initializers.apply(this._, args); }
  constant(...args) { return this._.constant.apply(this._, args); }
  run(...args) { return this._.run.apply(this._, args); }
};
