{
  'targets': [{ 
    'target_name': 'tensorflow-node', 
    'sources': [
      'cc/addons/index.cc',
      'cc/addons/constants.cc',
      'cc/addons/graph.cc',
      'cc/addons/math_ops.cc',
      'cc/addons/neural_network.cc',
      'cc/addons/operation.cc',
      'cc/addons/session.cc',
      'cc/addons/train.cc',
      'cc/addons/types.cc',

      'cc/lib/conversions.cc',
      'cc/lib/utils.cc',

      'cc/tensorflow/graph.cc',
      'cc/tensorflow/math_ops.cc',
      'cc/tensorflow/neural_network.cc',
      'cc/tensorflow/session.cc',
      'cc/tensorflow/train.cc'
    ],

    'libraries' : [
      '<!(pwd)/vendor/protobuf/libprotobuf.a',
      '<!(pwd)/vendor/tensorflow/libtensorflow.dylib'
    ],

    'include_dirs' : [ 
      'vendor/tensorflow/Headers',
      'vendor/tensorflow/Generated',
      'vendor/protobuf/Headers',
      'vendor/eigen/Headers',
      'vendor/eigen/Generated',
      "<!(node -e \"require('nan')\")"
    ],

    "conditions": [
      [ "OS==\"mac\"", {
        "xcode_settings": {
          "OTHER_CFLAGS": [
            "-mmacosx-version-min=10.7",
            "-std=c++",
            "-stdlib=libc++",
          ],
          "OTHER_LDFLAGS": [
            '-stdlib=libc++',
          ],
          "OTHER_CPLUSPLUSFLAGS": [
            '-std=c++11',
            '-stdlib=libc++',
            '-v'
          ],
          "GCC_ENABLE_CPP_RTTI": "YES",
          "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
          'MACOSX_DEPLOYMENT_TARGET': '10.12',
        },
      }]
    ],
    'cflags': [
    ],
    "cflags!": [
      "-fno-exceptions"
    ],
    'cflags_cc!': [
      "-fno-rtti", "-fno-exceptions" 
    ]
  }]
}
