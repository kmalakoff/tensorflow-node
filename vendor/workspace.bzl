def workspace():
  native.http_archive(
    name = "org_tensorflow",
    url = "https://github.com/tensorflow/tensorflow/archive/0.12.0-rc1.tar.gz",
    sha256 = "13f4b4dc7183b44b0cf0e6b1e4da9f215f67b6e982d23c91a315d49b429bf5c9",
    strip_prefix = "tensorflow-0.12.0-rc1"
  )
