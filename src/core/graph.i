%module "tensorflow"

%{
#include "core/graph.cc"
%}

%include "core/graph.h"
