#ifndef PHYSICSLIST_H
#define PHYSICSLIST_H

#include "G4VModularPhysicsList.hh"

// Définit comment les particules intéragissent avec les volumes définis dans DetectorConstruction
class PhysicsList: public G4VModularPhysicsList
{
public:
    PhysicsList();
    ~PhysicsList();
};
#endif
