AETHER_DIR = path.getabsolute("../module/aether")

dofile(path.join(AETHER_DIR, "scripts/aether-project.lua"))

solution "spaceinvaders"
	startproject("spaceinvaders")
	location "../build/"
	configurations { "debug", "release" }
	platforms { "x32", "x64" }
	
	dofile(path.join(AETHER_DIR, "scripts/aether-build.lua"))

	aetherProject("spaceinvaders-game")
		debugdir ("..")
		targetdir ("../build")
		files {
			"../src/**.cpp",
			"../src/**.h"
		}

