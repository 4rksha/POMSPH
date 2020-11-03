# POMSPH
Smoothed Particle Hydrodynamics

Dépendances à installer 
```
apt-get install libsdl2-dev libsdl2-image-dev libglew-dev premake4
```
Pour compiler le code sous Linux - makefile
```
premake/premake4.linux --file=master_MecaSim.lua gmake
make -f master_MecaSim_etudiant.make
./bin/master_MecaSim_etudian
```
Les sources utiles se trouvent dans le dossier POMSPH/src/master_MecaSim/src-etudiant/
