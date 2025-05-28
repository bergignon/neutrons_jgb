#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include <iostream>

EventAction::EventAction(RunAction* runAction) : runAction_(runAction) {}

void EventAction::BeginOfEventAction(const G4Event* event)
{
  totalEDeposited_ = 0.;
  particleEnergy_  = event->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy();
}

void EventAction::EndOfEventAction(const G4Event* event)
{
  // G4cout << "Energy Deposited : " << totalEDeposited_ << G4endl;
  auto analysisManager = G4AnalysisManager::Instance();
  // if (totalEDeposited_ != 0) {
  //   analysisManager->FillH1(0, totalEDeposited_);
  // }
  if (totalEDeposited_ != 0) {
    analysisManager->FillH2(0, totalEDeposited_, particleEnergy_);
  } 
}
