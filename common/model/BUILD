package(default_visibility = ["//visibility:public"])

cc_library(
    name = "bundle",
    srcs = ["bundle.c"],
    hdrs = ["bundle.h"],
    deps = [
        ":transaction",
        "//common/model:transfer",
        "//common/sign/v1:iss_kerl",
        "//common/trinary:flex_trit",
        "//common/trinary:trit_tryte",
        "//common/trinary:tryte_long",
        "@com_github_uthash//:uthash",
    ],
)

cc_library(
    name = "milestone",
    hdrs = ["milestone.h"],
    deps = ["//common/trinary:flex_trit"],
)

cc_library(
    name = "transaction",
    srcs = ["transaction.c"],
    hdrs = ["transaction.h"],
    deps = [
        "//common/curl-p:digest",
        "//common/trinary:flex_trit",
        "//common/trinary:trit_long",
    ],
)

cc_library(
    name = "transfer",
    srcs = ["transfer.c"],
    hdrs = ["transfer.h"],
    deps = [
        "//common/helpers:sign",
        "//common/kerl",
        "//common/model:transaction",
    ],
)

cc_library(
    name = "tryte_transaction",
    srcs = ["tryte_transaction.cc"],
    hdrs = ["tryte_transaction.h"],
    deps = [
        "//common/model:transaction",
    ],
)
