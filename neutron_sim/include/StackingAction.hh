#ifndef StackingAction_h
#define StackingAction_h 1

#include <vector>
#include "globals.hh"
#include "G4UserStackingAction.hh"
#include "EventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class StackingAction : public G4UserStackingAction
{
public:
    StackingAction(EventAction *eventAction);
    ~StackingAction();
    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track *aTrack) override;

private:
    EventAction *eventAction_ = nullptr;
};

#endif