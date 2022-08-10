workspace "Hazel"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }
	startproject "HazelEditor"

--当前路径为premake5.lua所在路径
--create outputdir macro
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/Glad"
include "Hazel/vendor/imgui"
include "Hazel/vendor/yaml-cpp"

project "Hazel"
    location "%{prj.name}" -- 规定了targetdir和objdir还需要这个吗，需要，这里的location是生成的vcproj的位置
    kind "StaticLib"
    language "C++"
	staticruntime "off"
	cppdialect "C++17"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}") --记得要加括号
	objdir   ("bin-int/" .. outputdir .. "/%{prj.name}") --这里的中英文括号看上去好像
	links {"GLFW", "opengl32.lib", "Glad", "imgui", "YAML_CPP"}

    pchheader "hzpch.h"
    pchsource "%{prj.name}/Src/hzpch.cpp"

	defines
	{
	    "_CRT_SECURE_NO_WARNINGS"
	}
	files
	{
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp",
		"%{prj.name}/vendor/**.hpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/Src",
		"%{prj.name}/Src/Hazel",
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/Glad/include",
		"%{prj.name}/vendor/imgui",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/vendor/stb_image",
		"%{prj.name}/vendor/entt/include",
		"%{prj.name}/vendor/yaml-cpp/include"
	}


	filter { "system:windows" }
	    systemversion "latest"
		defines {"HZ_PLATFORM_WINDOWS", "GLFW_INCLUDE_NONE", "HZ_ENABLE_ASSERTS"}
		
		postbuildcommands
		{
		    -- "copy default.config bin\\project.config"
			-- copy freom relative path to ... 注意这里的COPY前面没有%
		    ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.."\\Sandbox")
		}

    filter { "configurations:Debug" }
        defines { "DEBUG", "HZ_BUILD_DLL"}
        symbols "On"
		runtime "Debug" -- 运行时链接的dll是debug类型的	

    filter { "configurations:Release"}
        defines { "NDEBUG", "HZ_BUILD_DLL"}
        optimize "On"
		runtime "Release" -- 运行时链接的dll是release类型的


    filter { "configurations:Dist"}
		defines { "NDEBUG", "HZ_BUILD_DLL"}
	    optimize "On"


project "Sandbox"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir  ("bin/"..outputdir.."/%{prj.name}")
	objdir  ("bin-int/"..outputdir.."/%{prj.name}")
    
	files { "%{prj.name}/Src/**.h", "%{prj.name}/Src/**.cpp"}

    includedirs
	{
        "Hazel/vendor/spdlog/include",
		"Hazel/Src",
		"Hazel/Src/Hazel",
		"Hazel/vendor/glm",
		"Hazel/vendor/imgui",
		"Hazel/vendor/entt/include",
		"Hazel/vendor/yaml-cpp/include"
	}

	links { "Hazel" }

    filter { "system:Windows" }
	    systemversion "latest"
		 defines { "HZ_PLATFORM_WINDOWS"}

    filter { "configurations:Debug"}
        defines { "DEBUG"}
        symbols "On"

    filter { "configurations:Release"}
        defines { "NDEBUG" }
        optimize "On"

    filter { "configurations:Dist"}
		defines { "NDEBUG"}
		optimize "On"


project "HazelEditor"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir  ("bin/"..outputdir.."/%{prj.name}")
	objdir  ("bin-int/"..outputdir.."/%{prj.name}")
    
	files { "%{prj.name}/Src/**.h", "%{prj.name}/Src/**.cpp"}

    includedirs
	{
        "Hazel/vendor/spdlog/include",
		"Hazel/Src",
		"Hazel/Src/Hazel",
		"Hazel/vendor/glm",
		"Hazel/vendor/imgui",
		"Hazel/vendor/entt/include",
		"Hazel/vendor/yaml-cpp/include"
	}

	links { "Hazel" }

    filter { "system:Windows" }
	    systemversion "latest"
		 defines { "HZ_PLATFORM_WINDOWS"}

    filter { "configurations:Debug"}
        defines { "DEBUG"}
        symbols "On"

    filter { "configurations:Release"}
        defines { "NDEBUG" }
        optimize "On"

    filter { "configurations:Dist"}
		defines { "NDEBUG"}
		optimize "On"


