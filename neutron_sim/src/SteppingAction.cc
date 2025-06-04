#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4AnalysisManager.hh"

SteppingAction::SteppingAction(EventAction* eventAction) : eventAction_(eventAction) {}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!scoringVolume_) {

    const auto detConstruction = static_cast<const DetectorConstruction*>(
      G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    scoringVolume_ = detConstruction->getScoringVolume();
  }

  // get volume of the current step
  G4LogicalVolume* currentVolume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  // Exit if not in the scintillator
  if (currentVolume != scoringVolume_) {return;}

  // G4double edepStep = step->GetTotalEnergyDeposit();
  // G4cout << "Stepping action with deposit  : " << edepStep << G4endl;
  // eventAction_->AddEDeposit(edepStep);

   const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();

  if (secondaries && !secondaries->empty()) {
      for (size_t i = 0; i < secondaries->size(); ++i) {
        const G4Track* secTrack = (*secondaries)[i];
        const G4ParticleDefinition* particleDef = secTrack->GetDefinition();

        G4String particleName = particleDef->GetParticleName();
        G4double kineticEnergy = secTrack->GetKineticEnergy();

        if (particleName == "proton") {
          auto analysisManager = G4AnalysisManager::Instance();
          analysisManager->FillH1(0, kineticEnergy);
        }

      //   G4cout << "Secondary: " << particleName 
      //  << " | Type: " << particleType 
      //  << " | Energy: " << kineticEnergy / MeV << " MeV" 
      //  << G4endl;
    }
  }
}
