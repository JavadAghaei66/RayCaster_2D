add_rules("mode.debug", "mode.release")

add_requires("libsdl")

target("RayCaster")
    set_kind("binary")
    add_files("*.cpp")
    add_includedirs(".")

    add_packages("libsdl")

    if is_mode("debug") then
        add_defines("DEBUG")
        set_symbols("debug")
        set_optimize("none")
    else
        add_defines("NDEBUG")
        set_symbols("hidden")
        set_optimize("fast")
    end
