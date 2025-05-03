add_rules("mode.debug", "mode.release")
set_languages("c++23")
add_cxflags("-Wall", "-Wextra", "-Wuninitialized", {force = true})


add_requires("antlr4-runtime 4.13.2")
add_packages("antlr4-runtime", {include="isystem"})

target("antlr-g4")
    set_kind("static")
    add_files("antlr/*.cpp")
    set_warnings("none")

target("LTL-verifier")
    set_kind("binary")
    add_files("src/**.cpp")
    add_deps("antlr-g4")
    add_includedirs("antlr", {public = true})
    add_includedirs("src")
    set_rundir("$(projectdir)")
