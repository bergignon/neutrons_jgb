#include "Generator.hh"

PrimaryGenerator::PrimaryGenerator()
{
  particleSource_ = new G4GeneralParticleSource();
}

PrimaryGenerator::~PrimaryGenerator()
{
  delete particleSource_;
}

void PrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
{
  particleSource_->GeneratePrimaryVertex(anEvent);
}



