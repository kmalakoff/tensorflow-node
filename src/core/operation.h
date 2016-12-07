#ifndef TENSORFLOW_JS_OPERATION_H_
#define TENSORFLOW_JS_OPERATION_H_

#include <vector>
#include "tensorflow/c/c_api.h"
#include "tensorflow/core/platform/types.h"

class Operation {
  public:
    Operation(TF_Operation* operation);
    TF_Operation* operation();

  private:
    TF_Operation* m_operation = nullptr;
};

#endif  // TENSORFLOW_JS_OPERATION_H_