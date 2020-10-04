set -e
genie.exe vs2019
MSBuild.exe build/spaceinvaders.sln -t:Clean
MSBuild.exe build/spaceinvaders.sln
build/aether-spaceinvaders-game.exe
