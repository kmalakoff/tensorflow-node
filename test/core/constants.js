const assert = require('chai').assert;
const tf = require('../../index');

describe("Tensorflow", function() {

  describe("Version", function() {
    it("has a version", function() {
      assert.equal(tf.VERSION, '0.11.0');
    });
  });
});
