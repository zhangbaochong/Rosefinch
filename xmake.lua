add_rules("mode.debug", "mode.release")
set_languages("c++20")
set_project("Rosefinch")
add_rules("plugin.vsxmake.autoupdate")

add_requires("spdlog")
add_requires("glm")
add_requires("gtest")

includes("Code")
add_includedirs("Code/")

task("test")
    on_run(function ()
        os.exec("xmake f -m debug")
        os.exec("xmake")
        os.exec("xmake run -g test")
    end)
    set_menu{}

task("vs")
    on_run(function()
        os.exec("xmake project -k vsxmake")
    end)
    set_menu{}