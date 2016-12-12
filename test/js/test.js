const assert = require('chai').assert;
const tf = require('../../index');

describe("Tensorflow Test", function() {

  it("has expected types", function() {
    (new tf.Test()).run();
  });
});
