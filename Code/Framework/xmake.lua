
target("Framework")
    add_packages("spdlog", {public = true})
    add_packages("glm", {public = true})
    add_files("**.cpp")
    add_headerfiles("**.h")
    set_kind("static")