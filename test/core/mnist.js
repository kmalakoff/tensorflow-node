const assert = require('chai').assert;
const tf = require('../../index');
const _ = require('lodash');
const mnist_data = require('mnist-data');
require('pyextjs'); const np = window.numpy;

class MnistData {
  next_batch() { return [1, 2]; }
}

class Mnist {
  constructor(train_count, test_count) {
    this.train = new MnistData(mnist_data.training(train_count));
    this.test = new MnistData(mnist_data.testing(test_count));
  }
}
 
describe("Tensorflow", function() {

  describe("mnist", function() {
    it("should load mnist dataset", function() {
      const mnist = new Mnist(1000, 100);

      const g = new tf.Graph();
      const x = g.input('float32', [-1, 784]);
      const W = g.variable(np.zeros([784, 10]));
      const b = g.variable(np.zeros([10]));

      const y = g.nn.softmax(g.matmul(x, W) + b);
      // const y = g.nn.softmax(g.matmul(x, W) + b)
      const y_ = g.input('float32', [-1, 10]);

      cross_entropy = g.reduce_mean(-g.reduce_sum(y_ * g.log(y), {reduction_indices: [1]}))
      train_step = g.train.GradientDescentOptimizer(0.5).minimize(cross_entropy)

      // init = tf.initialize_all_variables()
      // sess = tf.Session()
      // sess.run(init)

      _.times(10, () => {
        console.log(mnist.train.next_batch);
        [batch_xs, batch_ys] = mnist.train.next_batch(100);
        // g.run(train_step, [[x, batch_xs], [y_, batch_ys]]);
 
      // correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))
      // accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
      // print(sess.run(accuracy, feed_dict={x: mnist.test.images, y_: mnist.test.labels}))
      })

      // assert.equal(true, true);
    });
  });
});
