licenses(["notice"])  # Apache 2.0

package(default_visibility = ["//visibility:public"])

# TODO: Once TF exports symbols in a DLL we can enable parse_time_op for windows
# https://github.com/tensorflow/addons/issues/782
py_library(
    name = "text",
    srcs = glob(["*.py"]),
    data = [
        "//tensorflow_addons/custom_ops/text:_skip_gram_ops.so",
        "//tensorflow_addons/rnn",
        "//tensorflow_addons/testing",
        "//tensorflow_addons/utils",
    ] + select({
        "//tensorflow_addons:windows": [],
        "//conditions:default": [
            "//tensorflow_addons/custom_ops/text:_parse_time_op.so",
        ],
    }),
)

py_test(
    name = "text_test",
    size = "small",
    srcs = glob(["tests/*"]),
    main = "tests/run_all_test.py",
    deps = [
        ":text",
        "//tensorflow_addons/layers",
    ],
)
