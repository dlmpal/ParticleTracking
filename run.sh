mkdir -p bin
mkdir -p data
rm data/*
(cd src; g++ main.cc particle_system.cc flow.cc force.cc -o ../bin/partSim -O3)
./bin/partSim
paraview data/state_..vtk