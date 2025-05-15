#include "myPhysics.hh"

MyPhysics::MyPhysics()
{
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4OpticalPhysics());
}

MyPhysics::~MyPhysics() {}
