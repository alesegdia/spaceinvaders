AETHER_DIR = path.getabsolute("../module/aether")

dofile(path.join(AETHER_DIR, "scripts/util/aether-project.lua"))
dofile(path.join(AETHER_DIR, "scripts/util/common-lib-setup.lua"))

solution "spaceinvaders"
	startproject("spaceinvaders")
	location "../build/"
	configurations { "debug", "release" }
	platforms { "x32", "x64" }
	
	dofile(path.join(AETHER_DIR, "scripts/aether-common.lua"))
	dofile(path.join(AETHER_DIR, "scripts/backends/sdl-backend.lua"))
	dofile(path.join(AETHER_DIR, "scripts/aether-lib.lua"))

	aetherProject("spaceinvaders-game")
		debugdir ("..")
		targetdir ("../build")
		files {
			"../src/**.cpp",
			"../src/**.h"
		}

