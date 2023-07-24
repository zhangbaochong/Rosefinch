add_rules("mode.debug", "mode.release")
add_requires("imgui 1.88", {configs = {glfw_opengl3 = true}})

target("imgui-demo")
    set_kind("binary")
    add_files("Code/Editor/main.cpp")
    add_packages("imgui")