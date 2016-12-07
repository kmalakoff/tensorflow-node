%module "tensorflow"

%{
#include "tensorflow/core/public/version.h"
%}

%include "../vendor/bazel-org_tensorflow/tensorflow/core/public/version.h"
