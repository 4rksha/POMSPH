
cd ..

.\premake\premake4.exe --os=windows --file=./master_MecaSim.lua gmake
.\premake\premake4.exe --os=windows --file=./master_MecaSim.lua codeblocks

.\premake\premake5.exe --os=windows --file=./master_MecaSim.lua vs2013
.\premake\premake5.exe --os=windows --file=./master_MecaSim.lua vs2015

pause
