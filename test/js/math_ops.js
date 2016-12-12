const assert = require('chai').assert;
const tf = require('../../index');

describe("Tensorflow MathOps", function() {

  describe("equal", function() {
    it("arrays", function() {
      const g = new tf.Graph();
      const a = g.constant([0, 1, 2]);
      const b = g.constant([0, 1, 1]);
      const op = g.equal(a, b);
      const result = g.run(op);
      assert.deepEqual(result, [true, true, false]);
    });
  });

  describe("argmax", function() {
    // TODO: cannot skip dimension like numpy?
    // it("argmax matrix", function() {
    //   const g = new tf.Graph();
    //   const values = g.constant([
    //     [0, 1, 2], 
    //     [3, 4, 5]
    //   ]);
    //   const argmax = g.argmax(values);
    //   const result = g.run(argmax);
    //   assert.deepEqual(result, 5);
    // });

    // it("argmax matrix", function() {
    //   const g = new tf.Graph();
    //   const values = g.constant([
    //     [0, 1, 2], 
    //     [3, 4, 5]
    //   ]);
    //   const op = g.argmax(values, 0);
    //   const result = g.run(op);
    //   assert.deepEqual(result, [1, 1, 1]);
    // });

    // it("argmax matrix", function() {
    //   const g = new tf.Graph();
    //   const values = g.constant([
    //     [0, 1, 2], 
    //     [3, 4, 5]
    //   ]);
    //   const op = g.argmax(values, 1);
    //   const result = g.run(op);
    //   assert.deepEqual(result, [2, 2]);
    // });
  });
});
