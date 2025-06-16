#ifndef NEUTRONSD_HH
#define NEUTRONSD_HH

#include "G4VSensitiveDetector.hh"

class SensitiveDetector : public G4VSensitiveDetector
{
public:
    SensitiveDetector(const G4String &name);
    virtual ~SensitiveDetector() = default;

    virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history) override;
};

#endif