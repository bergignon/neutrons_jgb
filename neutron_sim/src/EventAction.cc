#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include <iostream>

EventAction::EventAction(RunAction* runAction) : runAction_(runAction) {}

void EventAction::BeginOfEventAction(const G4Event*)
{
  totalEDeposited_ = 0.;
}

void EventAction::EndOfEventAction(const G4Event*)
{
  // G4cout << "Energy Deposited : " << totalEDeposited_ << G4endl;
  auto analysisManager = G4AnalysisManager::Instance();
  if (totalEDeposited_ != 0) {
    analysisManager->FillH1(0, totalEDeposited_);
  }
}
