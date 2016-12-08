var assert = require('chai').assert;
var tf = require('../index');

describe("Tensorflow", function() {

  // describe("Version", function() {
  //   it("has a version", function() {
  //     assert.equal(tf.version, '(0.11.0)');
  //   });
  // });

  describe("Run something", function() {
    it("can be run", function() {
      let graph = new tf.Graph();
      const input = graph.Placeholder();
      var buf = new Buffer(4); buf.writeInt32LE(2);
      const two = graph.ScalarConst(buf);
      const add = graph.Add(input, two);
      const result = graph.Run([add], {input: 3});
      assert.equal(result[0].readInt32LE(), 5);
    });
  });
});
