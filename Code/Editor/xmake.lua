
target("RosefinchEditor")
    set_kind("binary")
    add_files("*.ixx")
    add_files("*.cpp")

    add_deps("Framework")