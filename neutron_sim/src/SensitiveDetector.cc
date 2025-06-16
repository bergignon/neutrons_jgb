#include "SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4Neutron.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4AnalysisManager.hh"

SensitiveDetector::SensitiveDetector(const G4String &name) : G4VSensitiveDetector(name) {}

G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *)
{
    /*
     *
     * THIS SECTION ENDS UP BEING USELESS; THE PROCESSING IS DONE IN STEPPINGACTION
     *
     */

    auto track = step->GetTrack();
    if (track->GetDefinition() == G4Neutron::Definition())
    {
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillH1(1, track->GetKineticEnergy());
        G4cout << "HIT !" << G4endl;
    }
    return true;
}