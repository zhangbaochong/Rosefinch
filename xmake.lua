add_rules("mode.debug", "mode.release")
set_languages("c++20")
set_project("Rosefinch")
add_rules("plugin.vsxmake.autoupdate")

add_requires("spdlog")
add_requires("glm")
add_requires("gtest")
add_requires("glfw")
add_requires("vulkansdk")
add_requires("imgui")

includes("Code")
add_includedirs("Code/")

rule("module")
    on_load(function (target)
        if is_mode("debug", "releasedbg") then
            target:set("kind", "shared")
            if is_plat("windows") then
                import("core.project.rule")
                local rule = rule.rule("utils.symbols.export_all")
                target:rule_add(rule)
                target:extraconf_set("rules", "utils.symbols.export_all", {export_classes = true})
            end
        elseif is_mode("release") then
            target:set("kind", "static")
        else
            assert(false, "Unknown build kind")
        end
    end)
rule_end()

task("test")
    on_run(function ()
        os.exec("xmake")
        os.exec("xmake run -g test")
    end)
    set_menu{}

task("vs")
    on_run(function()
        os.exec("xmake project -k vsxmake")
    end)
    set_menu{}

task("e")
    on_run(function()
        os.exec("xmake")
        os.exec("xmake run Editor")
    end)
    set_menu{}

task("d")
    on_run(function ()
        os.exec("xmake f -m debug")
        os.exec("xmake")
        os.exec("xmake run -d Editor")
    end)
    set_menu{}
