add_rules("mode.debug", "mode.release")
set_languages("c++20")
set_project("Rosefinch")
add_rules("plugin.vsxmake.autoupdate")

add_requires("spdlog")
add_requires("glm")

includes("Code")
add_includedirs("Code/")

-- unit test
rule("module.test")
    on_load(function (target)
        target:set("policy", "build.warning", true)
        target:set("rundir", "$(projectdir)")
        target:set("group", "test")
        -- gtest
        target:add("packages", "gtest")
    end)
rule_end()

-- all test cpp has main function
for _, file in ipairs(os.files("Code/test/**.cpp")) do
    local name = path.basename(file)

    target("test." .. name)
        add_rules("module.test")
        set_kind("binary")
        add_files(file)
    target_end()
end

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