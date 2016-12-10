{
  'targets': [{ 
    'target_name': 'tensorflow', 
    'sources': [
      'cc/addons/index.cc',
      'cc/addons/CONSTANTS.cc',
      'cc/addons/Graph.cc',
      'cc/addons/MathOps.cc',
      'cc/addons/NeuralNetwork.cc',
      'cc/addons/Operation.cc',
      'cc/addons/Session.cc',
      'cc/addons/Train.cc',
      'cc/addons/TYPES.cc',

      'cc/lib/Conversions.cc',
      'cc/lib/Utils.cc',

      'cc/tensorflow/Graph.cc',
      'cc/tensorflow/Session.cc'
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
