const assert = require('chai').assert;
const tf = require('../../index');

describe("Tensorflow Types", function() {

  it("has expected types", function() {
    assert.equal(tf.float32, 1);
    // TODO: add more types
  });
});
