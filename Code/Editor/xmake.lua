
target("Editor")
    set_kind("binary")
    add_files("*.cpp")
    add_headerfiles("**.h")
    add_deps("Framework")