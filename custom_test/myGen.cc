#include "myGen.hh"

MyGen::MyGen()
{
    particleGun = new G4ParticleGun(1);
}

MyGen::~MyGen()
{
    delete particleGun;
}

void MyGen::GeneratePrimaries(G4Event* anEvent)
{
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "proton";
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName);

    G4ThreeVector pos(0,0,0);
    G4ThreeVector mom(0,0,1);

    particleGun->SetParticlePosition(pos);
    particleGun->SetParticleMomentumDirection(mom);
    particleGun->SetParticleMomentum(1000*GeV);
    particleGun->SetParticleDefinition(particle);

    particleGun->GeneratePrimaryVertex(anEvent);
}
