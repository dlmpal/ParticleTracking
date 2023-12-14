mkdir -p bin
mkdir -p data
(cd src; g++ main.cc particle_system.cc flow_cylinder.cc force.cc -o ../bin/partSim -O3)
./bin/partSim
paraview state_..vtk