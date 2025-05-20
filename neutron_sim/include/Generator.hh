#ifndef GENERATOR_H
#define GENERATOR_H

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

class G4Event;

class PrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGenerator();
  ~PrimaryGenerator();

  const G4GeneralParticleSource* getParticleSource() const {return particleSource_;}
  virtual void GeneratePrimaries(G4Event* anEvent);

private:
  G4GeneralParticleSource* particleSource_;

};

#endif
