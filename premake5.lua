workspace "Hazel"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

--��ǰ·��Ϊpremake5.lua����·��
--create outputdir macro
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/Glad"
include "Hazel/vendor/imgui"


project "Hazel"
    location "%{prj.name}" -- �涨��targetdir��objdir����Ҫ�������Ҫ�������location�����ɵ�vcproj��λ��
    kind "StaticLib"
    language "C++"
	staticruntime "on"
	cppdialect "C++17"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}") --�ǵ�Ҫ������
	objdir   ("bin-int/" .. outputdir .. "/%{prj.name}") --�������Ӣ�����ſ���ȥ����
	links {"GLFW", "opengl32.lib", "Glad", "imgui"}

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
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/Glad/include",
		"%{prj.name}/vendor/imgui",
		"%{prj.name}/vendor/glm"
	}


	filter { "system:windows" }
	    systemversion "latest"
		defines {"HZ_PLATFORM_WINDOWS", "GLFW_INCLUDE_NONE", "HZ_ENABLE_ASSERTS"}
		
		postbuildcommands
		{
		    -- "copy default.config bin\\project.config"
			-- copy freom relative path to ... ע�������COPYǰ��û��%
		    ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.."\\Sandbox")
		}

    filter { "configurations:Debug" }
        defines { "DEBUG", "HZ_BUILD_DLL"}
        symbols "On"
		runtime "Debug" -- ����ʱ���ӵ�dll��debug���͵�

    filter { "configurations:Release"}
        defines { "NDEBUG", "HZ_BUILD_DLL"}
        optimize "On"
		runtime "Release" -- ����ʱ���ӵ�dll��release���͵�

    filter { "configurations:Dist"}
		defines { "NDEBUG", "HZ_BUILD_DLL"}
	    optimize "On"


project "Sandbox"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir  ("bin/"..outputdir.."/%{prj.name}")
	objdir  ("bin-int/"..outputdir.."/%{prj.name}")
    
	files { "%{prj.name}/Src/**.h", "%{prj.name}/Src/**.cpp"}

    includedirs
	{
        "Hazel/vendor/spdlog/include",
		"Hazel/Src",
		"Hazel/vendor/glm"
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


