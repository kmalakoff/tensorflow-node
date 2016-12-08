{
  'targets': [{ 
    'target_name': 'tensorflow', 
    'sources': [
      'src/core/graph.cc',
      'src/nan_addons/graph.cc', 'src/nan_addons/operation.cc', 'src/nan_addons/addons.cc'
    ],
    
    'libraries' : [
      '<!(pwd)/vendor/bazel-out/host/bin/external/protobuf/libprotobuf.a',
      '<!(pwd)/vendor/bazel-out/local-opt/bin/tensorflow/libtensorflow.dylib'
    ],

    'include_dirs' : [ 
      'vendor/bazel-org_tensorflow',
      'vendor/bazel-org_tensorflow/external/protobuf/src',
      'vendor/bazel-org_tensorflow/external/eigen_archive',
      'vendor/bazel-genfiles',
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
