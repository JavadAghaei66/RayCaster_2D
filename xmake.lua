add_requires("libsdl")

target("RayCaster")
    set_kind("binary")
    add_files("*.cpp")
    add_includedirs(".")

    add_packages("libsdl")
