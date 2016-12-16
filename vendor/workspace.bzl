def workspace():
  native.http_archive(
    name = "org_tensorflow",
    url = "http://github.com/tensorflow/tensorflow/archive/93812423fcd5878aa2c1d0b68dc0496980c8519d.tar.gz",
    sha256 = "ede7242c4f7d4dfd581f747b5bca26b98f801f3a0319c50bf6a446408329ca39",
    strip_prefix = "tensorflow-93812423fcd5878aa2c1d0b68dc0496980c8519d"
  )
