add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("RosefinchEditor")
    set_kind("binary")
    includes("Code")