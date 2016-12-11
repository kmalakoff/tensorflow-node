const assert = require('chai').assert;
const tf = require('../../index');
const mnist_data = require('mnist-data');
require('pyextjs'); const np = window.numpy;

function oneHot(v, l) { var result = np.zeros([10]); result[v] = 1; return result; }

class MnistData {
  constructor(data) { this.data = data; }
  get images() { return np.array(this.data.images.values).reshape([100, 784]); }
  get labels() { return this.data.labels.values.map(x => oneHot(x, 10)); }
  next_batch() { return [1, 2]; }
}

class Mnist {
  constructor(train_count, test_count) {
    this.train = new MnistData(mnist_data.training(train_count));
    this.test = new MnistData(mnist_data.testing(test_count));
  }
}

describe("Tensorflow training", function() {

  describe("mnist", function() {
    it("should load mnist dataset", function() {
      const mnist = new Mnist(1000, 100);

      const g = new tf.Graph();
      const x = g.placeholder(tf.float32, [100, 784]); // TODO: handle variable input dimensions
      const y_ = g.placeholder(tf.float32, [100, 10]); // TODO: handle variable input dimensions

      const W = g.variable(np.zeros([784, 10]));
      const b = g.variable(np.zeros([10]));
      const y = g.matmul_add(x, W, b);

      // loss = g.reduce_mean(g.nn.softmax_cross_entropy_with_logits(y, y_));
      // // train_step = g.train.GradientDescentOptimizer(0.5).minimize(loss);
      // train_step = g.train.GradientDescentOptimizer(0.5, loss);

      sess = new tf.Session(g);
      sess.runNoOut(g.variable_initializers());

      for(let i = 0; i < 10; i++) {
        // [batch_xs, batch_ys] = mnist.train.next_batch(100);
        // sess.run(train_step, [[x, batch_xs], [y_, batch_ys]]);
         
        correct_prediction_op = g.equal(g.argmax(y,1), g.argmax(y_,1));
        accuracy_op = g.reduce_mean(g.cast(correct_prediction_op, tf.float32));
        accuracy = sess.run(accuracy_op, [[x, mnist.test.images], [y_, mnist.test.labels]])
        console.log(accuracy);
      }
    });
  });
});
