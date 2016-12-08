var assert = require('chai').assert;
var tf = require('../../index');

describe("Tensorflow", function() {

  // describe("Version", function() {
  //   it("has a version", function() {
  //     assert.equal(tf.version, '(0.11.0)');
  //   });
  // });

  describe("Run something", function() {

    it("simple", function() {
      let graph = new tf.Graph();

      const matrix1 = graph.constant([[3., 3.]]);
      const matrix2 = graph.constant([[2.],[2.]]);
      const product = graph.matmul(matrix1, matrix2);
      const [result] = graph.run([product], {});
      assert.deepEqual([[result.readFloatLE()]], [[12.]]);
    });

    it("can be run", function() {
      let graph = new tf.Graph();
      const input = graph.Placeholder();
      const two = graph.ScalarConst(2.);
      const add = graph.Add(input, two);
      const [result] = graph.Run([add], {input: 3.});
      assert.deepEqual(result.readFloatLE(), 5.);
    });
  });
});

// var buf = new Buffer(4); buf.writeInt32LE(2);
// const two = graph.ScalarConst(buf);
