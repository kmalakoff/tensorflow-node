const _tf = require('./addons');

module.exports = class Session {
  constructor(graph) {
    this._ = new _tf.Session(graph._);
  }

  run(...args) { return this._.run.apply(this._, args); }
};
