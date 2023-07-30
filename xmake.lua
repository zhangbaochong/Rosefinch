add_rules("mode.debug", "mode.release")
set_languages("c++20")
set_project("Rosefinch")

add_requires("spdlog")

includes("Code")
add_includedirs("Code/")