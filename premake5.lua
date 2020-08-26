workspace "Hazel"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

--��ǰ·��Ϊpremake5.lua���ڵ�·��
--create outputdir macro
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Hazel/vendor/GLFW"


project "Hazel"
    location "%{prj.name}" -- �涨��targetdir��objdir����Ҫ�������Ҫ�������location�����ɵ�vcproj��λ��
    kind "SharedLib"
    language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}") --�ǵ�Ҫ������
	objdir   ("bin-int/" .. outputdir .. "/%{prj.name}") --�������Ӣ�����ſ���ȥ����
	links {"GLFW", "opengl32.lib"}

    pchheader "hzpch.h"
    pchsource "%{prj.name}/Src/hzpch.cpp"

	files
	{
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/Src",
		"%{prj.name}/vendor/GLFW/include"
	}


	filter { "system:windows" }
	    systemversion "latest"
		cppdialect "C++17"
	    staticruntime "on"
		defines {"HZ_PLATFORM_WINDOWS"}
		
		postbuildcommands
		{
		    -- "copy default.config bin\\project.config"
			-- copy freom relative path to ... ע�������COPYǰ��û��%
		    ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.."\\Sandbox")
		}

    filter { "configurations:Debug" }
        defines { "DEBUG", "HZ_BUILD_DLL"}
		buildoptions {"/MDd"}
        symbols "On"
		runtime "Debug" -- ����ʱ���ӵ�dll��debug���͵�

    filter { "configurations:Release"}
        defines { "NDEBUG", "HZ_BUILD_DLL"}
		buildoptions {"/MD"}
        optimize "On"
		runtime "Release" -- ����ʱ���ӵ�dll��release���͵�

    filter { "configurations:Dist"}
		defines { "NDEBUG", "HZ_BUILD_DLL"}
		buildoptions {"/MD"}
	    optimize "On"


project "Sandbox"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
	targetdir  ("bin/"..outputdir.."/%{prj.name}")
	objdir  ("bin-int/"..outputdir.."/%{prj.name}")
    
	files { "%{prj.name}/Src/**.h", "%{prj.name}/Src/**.cpp"}

    includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/Src"
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


