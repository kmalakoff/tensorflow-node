const assert = require('chai').assert;
const tf = require('../../index');

describe("Tensorflow", function() {

  // describe("Version", function() {
  //   it("has a version", function() {
  //     assert.equal(tf.version, '(0.11.0)');
  //   });
  // });

  describe("Run something", function() {

    it("can multiply constants", function() {
      const g = new tf.Graph();
      const matrix1 = g.constant([[1, 0], [0, 1]]);
      const matrix2 = g.constant([[4, 1], [2, 2]]);
      const product = g.matmul(matrix1, matrix2);
      const [result] = g.run([product]);
      assert.deepEqual(result, [[4, 1], [2, 2]]);
    });

    // it("can multiply constants", function() {
    //   const g = new tf.Graph();
    //   const a = [[1, 0], [0, 1]];
    //   const b = [[4, 1], [2, 2]];
    //   assert.deepEqual(g.matmul(a, b)(), [[4, 1], [2, 2]]);
    // });

    it("can use inputs", function() {
      const g = new tf.Graph();
      const input = g.input();
      const two = g.constant(2);
      const add = g.add(input, two);
      const result = g.run(add, [[input, 3]]);
      assert.deepEqual(result, 5);
    });

    // it("can use inputs", function() {
    //   const g = new tf.Graph();
    //   const input = g.input();
    //   assert.deepEqual(g.add(input, 2)([[input, 3]]), 5);
    // });

    // it("can use inputs", function() {
    //   const g = new tf.Graph();
    //   const input = g.input();
    //   const add = g.add(input, 2);
    //   const result = g.run(add, input(3));
    //   assert.deepEqual(result, 5);
    // });

    // it("can use inputs", function() {
    //   const g = new tf.Graph();
    //   const input = g.input();
    //   const result = g.add(input, 2)(input(3));
    //   assert.deepEqual(result, 5);
    // });
  });
});

// var buf = new Buffer(4); buf.writeInt32LE(2);
// const two = graph.ScalarConst(buf);
