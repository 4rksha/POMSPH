
no_project = true
dofile "./premake4.lua"

-- master_MecaSim
gfx_masterMecaSim_dir = path.getabsolute(".")

master_MecaSim_files = {	gfx_masterMecaSim_dir .. "/src/master_MecaSim/src-etudiant/*.cpp", 
							gfx_masterMecaSim_dir .. "/src/master_MecaSim/src-etudiant/*.h"
	}
	
project("master_MecaSim_etudiant")
    language "C++"
    kind "ConsoleApp"
    targetdir ( gfx_masterMecaSim_dir .. "/bin" )
	includedirs { gfx_masterMecaSim_dir .. "/src/master_MecaSim/src-etudiant/" }
    files ( gkit_files )
    files ( master_MecaSim_files )
