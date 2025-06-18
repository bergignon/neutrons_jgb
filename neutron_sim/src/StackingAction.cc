#include "StackingAction.hh"
#include "G4OpticalPhoton.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::StackingAction(EventAction *eventAction)
{
    eventAction_ = eventAction;
}

StackingAction::~StackingAction() {}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(
    const G4Track *aTrack)
{
    if (aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
    {
        if (aTrack->GetParentID() > 0)
        {
            if (aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
            {
                eventAction_->incrementPhotonCount();
                G4cout << "Scintillation photon" << G4endl;
            }
        }
    }
    return fUrgent;
}
