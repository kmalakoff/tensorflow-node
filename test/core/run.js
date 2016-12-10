const assert = require('chai').assert;
const tf = require('../../index');

describe("Tensorflow run", function() {
  // it("can multiply constants", function() {
  //   const g = new tf.Graph();
  //   const matrix1 = g.constant([[1, 0], [0, 1]]);
  //   const matrix2 = g.constant([[4, 1], [2, 2]]);
  //   const product = g.matmul(matrix1, matrix2);
  //   const [result] = g.run([product]);
  //   assert.deepEqual(result, [[4, 1], [2, 2]]);
  // });

  it("can use inputs", function() {
    const g = new tf.Graph();
    const input = g.input();
    const two = g.constant(2);
    const add = g.add(input, two);
    const result = g.run(add, [[input, 3]]);
    assert.deepEqual(result, 5);
  });

  // it("can use sessions", function() {
  //   const g = new tf.Graph();
  //   const input = g.input();
  //   const two = g.constant(2);
  //   const add = g.add(input, two);

  //   const session = tf.Session(g);
  //   const result = session.run(add, [[input, 3]]);
  //   assert.deepEqual(result, 5);
  // });
});
