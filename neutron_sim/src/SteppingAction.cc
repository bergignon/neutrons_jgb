#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

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

  G4double edepStep = step->GetTotalEnergyDeposit();
  // G4cout << "Stepping action with deposit  : " << edepStep << G4endl;
  eventAction_->AddEDeposit(edepStep);
}
