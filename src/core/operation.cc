#include <iostream>
#include "operation.h"

Operation::Operation(TF_Operation* operation) { m_operation = operation; }
  
TF_Operation* Operation::operation() { return m_operation; }
