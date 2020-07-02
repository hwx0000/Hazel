workspace "Hazel"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

--当前路径为premake5.lua所在的路径
--create outputdir macro
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Hazel"
    location "%{prj.name}" -- 规定了targetdir和objdir还需要这个吗，需要，这里的location是生成的vcproj的位置
    kind "SharedLib"
    language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}") --记得要加括号
	objdir   ("bin-int/" .. outputdir .. "/%{prj.name}") --这里的中英文括号看上去好像

    
	files
	{
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}


	filter { "system:windows" }
	    systemversion "latest"
		cppdialect "C++17"
	    staticruntime "on"
		defines {"HZ_PLATFORM_WINDOWS"}
		
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

    filter { "configurations:Release", "HZ_BUILD_DLL"}
        defines { "NDEBUG" }
        optimize "On"
		runtime "Release" -- 运行时链接的dll是release类型的

    filter { "configurations:Dist", "HZ_BUILD_DLL"}
    defines { "NDEBUG" }
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


