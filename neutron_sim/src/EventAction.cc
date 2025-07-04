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
  totalLightOutput_ = 0.;
  nScintillationPhotons_ = 0;
  scintillationPlusCherenkov_ = 0;
  particleEnergy_ = event->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy();
}

void EventAction::EndOfEventAction(const G4Event *event)
{
  // G4cout << "Energy deposit of : " << totalEDeposited_ << " MeV" << G4endl;
  // G4cout << "Scintillation photons : " << nScintillationPhotons_ << G4endl;
  G4int runID = G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID();
  auto analysisManager = G4AnalysisManager::Instance();
  if (totalEDeposited_ != 0)
  {
    // analysisManager->FillH1(runID, totalEDeposited_ / particleEnergy_ * 100);
    // analysisManager->FillH1(runID, scintillationPlusCherenkov_ / 12.3 * keV / particleEnergy_ * 100);
    analysisManager->FillH1(runID, totalLightOutput_);
  }
}

void EventAction::AddEDeposit(G4double eDeposit)
{
  totalEDeposited_ += eDeposit;
}

void EventAction::AddLightOutput(G4double lightEnergy)
{
  totalLightOutput_ += lightEnergy;
}

void EventAction::incrementPhotonCount()
{
  nScintillationPhotons_++;
}

void EventAction::incrementCherenkov()
{
  scintillationPlusCherenkov_++;
}
