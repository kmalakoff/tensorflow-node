var assert = require('chai').assert;
var tf = require('../index');

describe("Tensorflow", function() {

  describe("Version", function() {
    it("has a version", function() {
      assert.equal(tf.version, '(0.11.0)');
    });
  });

  describe("Run something", function() {
    it("can be run", function() {
      let graph = new tf.Graph();
      const input = graph.Placeholder();
      const two = graph.ScalarConst(2);
      const add = graph.Add(input, two);
      const result = graph.Run(input, add);
      assert.equal(result, 5);
    });
  });
});
