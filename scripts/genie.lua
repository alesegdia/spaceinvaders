AETHER_DIR = path.getabsolute("../module/aether")
print(AETHER_DIR)

dofile(path.join(AETHER_DIR, "scripts/aether-project.lua"))

solution "game"
	location "../build/"
	configurations { "debug", "release" }
	platforms { "x32", "x64" }
	
	dofile(path.join(AETHER_DIR, "scripts/aether-build.lua"))

	newAetherExample("game")
		debugdir (AETHER_DIR)
		files {
			"../src/**.cpp",
			"../src/**.h"
		}
		flags {
			"Symbols",
			"StaticRuntime"
		}

