#ifndef EventAction_h
#define EventAction_h

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;

class EventAction : public G4UserEventAction
{
public:
  EventAction(RunAction *runAction);
  ~EventAction() override = default;

  void BeginOfEventAction(const G4Event *event) override;
  void EndOfEventAction(const G4Event *event) override;

  void AddEDeposit(G4double eDeposit);
  void AddLightOutput(G4double lightEnergy);
  void incrementPhotonCount();
  void incrementCherenkov();

private:
  RunAction *runAction_ = nullptr;
  G4double totalEDeposited_ = 0.;
  G4double totalLightOutput_ = 0.;
  G4int nScintillationPhotons_ = 0;
  G4int scintillationPlusCherenkov_ = 0;
  G4double particleEnergy_ = 0.;
};

#endif
