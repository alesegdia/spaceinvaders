AETHER_DIR = path.getabsolute("../module/aether")

dofile(path.join(AETHER_DIR, "scripts/util/util.lua"))

aetherConfig()

solution "spaceinvaders"
	startproject("spaceinvaders-game")
	location "../build/"
	configurations { "debug", "release" }
	platforms { "x32", "x64" }
	
	aetherBuild()

	aetherProject("spaceinvaders-game")
		debugdir ("..")
		targetdir ("../build")
		files {
			"../src/**.cpp",
			"../src/**.h"
		}

