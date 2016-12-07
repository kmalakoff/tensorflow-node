var assert = require('chai').assert;
var tf = require('../index');

describe("Tensorflow", function() {

  describe("Version", function() {
    it("has a version", function() {
      assert.equal(tf.version, '(0.11.0)')
    });
  });

  describe("Run something", function() {
    it("can be run", function() {
      let graph = new tf.Graph();
      const place = graph.placeholder();
      // const one = graph.scalar(1);
      const two = graph.scalar(2);
      const add = graph.add(place, two);
      const result = graph.run(place, add);
      console.log(result);
    });
  });
});
