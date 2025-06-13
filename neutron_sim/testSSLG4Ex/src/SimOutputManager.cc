#include "SimOutputManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UserRunAction.hh"
#include "StackingAction.hh"
#include "G4UImanager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimOutputManager::SimOutputManager() : mEdep{0.},
                                       mEmittedScntPhotonNum{-1}
{
  Initialize();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimOutputManager::~SimOutputManager()
{
  if (outputFile_.is_open())
  {
    outputFile_.close();
  }
}

void SimOutputManager::Initialize()
{
  outputFile_.open("output.csv");
}

void SimOutputManager::BeginOfEventAction(const G4Event *event)
{
}

void SimOutputManager::EndOfEventAction(const G4Event *event)
{
  SetStackingActionOutputs();
  // G4cout << mEmittedScntPhotonNum << '\n';
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(0, mEdep);
  outputFile_ << mEmittedScntPhotonNum << ',' << mEdep << ',' << eProtons << ',' << eC12 << '\n';
  outputFile_.flush();
  Reset();
}

void SimOutputManager::SetStackingActionOutputs()
{
  const G4UserStackingAction *sa = G4RunManager::GetRunManager()->GetUserStackingAction();

  const StackingAction *userSA = dynamic_cast<const StackingAction *>(sa);

  if (userSA)
  {
    mEmittedScntPhotonNum = userSA->GetEmittedScintillationPhotonNumber();
    mOPEnergyVec = userSA->GetOPEnergyVector();
    mOPWavelengthVec = userSA->GetOPWavelengthVector();
    mOPTimeVec = userSA->GetOPTimeVector();
  }
}

void SimOutputManager::Reset()
{
  // General
  mEdep = 0.;
  eProtons = 0.;
  eC12 = 0.;
  mEmittedScntPhotonNum = -1;
}