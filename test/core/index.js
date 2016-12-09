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
      const g = new tf.Graph();
      const matrix1 = g.constant([[5., 4.]]);
      const matrix2 = g.constant([[3.], [2.]]);
      const product = g.matmul(matrix1, matrix2);
      const [result] = g.run([product]);
      assert.deepEqual([[result.readFloatLE()]], [[23.]]);
    });

    it("can be run", function() {
      const g = new tf.Graph();
      const input = g.input();
      const two = g.constant(2);
      const add = g.add(input, two);
      const [result] = g.run([add], [[input, 3]]);
      assert.deepEqual(result, 5);
    });
  });
});

// var buf = new Buffer(4); buf.writeInt32LE(2);
// const two = graph.ScalarConst(buf);
