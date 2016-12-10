const _tf = require('./addons');

function bindFn(target, key, obj) { return function(...args) { return obj[key].apply(obj, [target._].concat(args)); }; }
function bindFns(target, obj) { for (var key in obj) target[key] = bindFn(target, key, obj); }

module.exports = class target {
  constructor() {
    this._ = new _tf.Graph();

    bindFns(this, _tf.MathOps);
    bindFns(this, _tf.NeuralNetwork);
    bindFns(this, _tf.Train);
  }

  input(...args) { return this._.placeholder.apply(this._, args); }
  variable(...args) { return this._.variable.apply(this._, args); }
  constant(...args) { return this._.constant.apply(this._, args); }
  run(...args) { return this._.run.apply(this._, args); }
};
