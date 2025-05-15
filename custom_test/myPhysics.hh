#ifndef MYPHYSICS_HH
#define MYPHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"

class MyPhysics : public G4VModularPhysicsList
{
public:
    MyPhysics();
    ~MyPhysics();


};
#endif // MYPHYSICS_HH
