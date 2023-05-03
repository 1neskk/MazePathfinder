-- premake5.lua

workspace "Maze"
    architecture "x64"
    
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "Maze"
        location "Maze"
        kind "ConsoleApp"
        language "C++"
        
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
        
        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs
        {
            "%{prj.name}/thirdparty/SFML-2.5.1/include"
            
        }

        libdirs
        {
            "%{prj.name}/thirdparty/SFML-2.5.1/lib"
        }

        links
        {
            "opengl32.lib",
            "sfml-graphics.lib",
            "sfml-window.lib",
            "sfml-system.lib"
        }

        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"
            
            defines
            {
                "PLATFORM_WINDOWS",
            }
            
        filter "configurations:Debug"
            defines "ENGINE_DEBUG"
            symbols "On"
            
        filter "configurations:Release"
            defines "ENGINE_RELEASE"
            optimize "On"
            
        filter "configurations:Dist"
            defines "ENGINE_DIST"
            optimize "On"