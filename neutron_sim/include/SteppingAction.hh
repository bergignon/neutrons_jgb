#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4LogicalVolume;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(EventAction* eventAction);
    ~SteppingAction() override = default;

    void UserSteppingAction(const G4Step*) override;

  private:
    EventAction* eventAction_ = nullptr;
    G4LogicalVolume* scoringVolume_ = nullptr;
};

#endif
