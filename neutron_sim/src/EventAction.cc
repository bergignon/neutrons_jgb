#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include <iostream>

EventAction::EventAction(RunAction *runAction) : runAction_(runAction) {}

void EventAction::BeginOfEventAction(const G4Event *event)
{
  totalEDeposited_ = 0.;
  nScintillationPhotons_ = 0;
  // particleEnergy_  = event->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy();
}

void EventAction::EndOfEventAction(const G4Event *event)
{
  G4cout << "Energy deposit of : " << totalEDeposited_ << " MeV" << G4endl;
  auto analysisManager = G4AnalysisManager::Instance();
  if (totalEDeposited_ != 0)
  {
    analysisManager->FillH1(0, totalEDeposited_);
  }
}

void EventAction::AddEDeposit(G4double eDeposit)
{
  totalEDeposited_ += eDeposit;
}

void EventAction::incrementPhotonCount()
{
  nScintillationPhotons_++;
}
