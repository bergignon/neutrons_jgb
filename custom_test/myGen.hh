#ifndef MYGEN_HH
#define MYGEN_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

class MyGen : public G4VUserPrimaryGeneratorAction
{
public:
    MyGen();
    ~MyGen();

    virtual void GeneratePrimaries(G4Event* anEvent);
private:
    G4ParticleGun* particleGun;
};
#endif // MYGEN_HH
