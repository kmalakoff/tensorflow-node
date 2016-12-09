def workspace():
  native.http_archive(
    name = "org_tensorflow",
    url = "http://github.com/tensorflow/tensorflow/archive/v0.11.0.tar.gz",
    sha256 = "24242ff696234bb1e58d09d45169b148525ccb706f980a4a92ddd3b82c7546dc",
    strip_prefix = "tensorflow-0.11.0",
  )
