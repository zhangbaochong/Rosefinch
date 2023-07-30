rule("module.test")
    on_load(function (target)
        target:set("policy", "build.warning", true)
        target:set("rundir", "$(projectdir)")
        target:set("group", "test")
        -- gtest
        target:add("packages", "gtest")
        target:add("deps", "Framework")
    end)
rule_end()

-- all test cpp has main function
for _, file in ipairs(os.files("**.cpp")) do
    local name = path.basename(file)

    target("test." .. name)
        add_rules("module.test")
        set_kind("binary")
        add_files(file)
    target_end()
end