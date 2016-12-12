{
  'targets': [{ 
    'target_name': 'tensorflow-node', 
    'sources': [
      'src/native/lib/conversions.cc',
      'src/native/lib/utils.cc',

      'src/native/cc/register_module.cc',
      'src/native/cc/addons/constants.cc',
      'src/native/cc/addons/graph.cc',
      'src/native/cc/addons/math_ops.cc',
      'src/native/cc/addons/neural_network.cc',
      'src/native/cc/addons/operation.cc',
      'src/native/cc/addons/session.cc',
      'src/native/cc/addons/test.cc',
      'src/native/cc/addons/train.cc',
      'src/native/cc/addons/types.cc',

      'src/native/cc/tf/graph.cc',
      'src/native/cc/tf/math_ops.cc',
      'src/native/cc/tf/neural_network.cc',
      'src/native/cc/tf/session.cc',
      'src/native/cc/tf/train.cc'
    ],

    'libraries' : [
      '<!(pwd)/vendor/protobuf/libprotobuf.a',
      '<!(pwd)/vendor/tensorflow/libtensorflow_cc.dylib'
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
