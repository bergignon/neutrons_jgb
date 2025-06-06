#ifndef SimOutputManager_h
#define SimOutputManager_h 1

#include "G4AnalysisManager.hh"
#include "globals.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4Run.hh"

#include <fstream>
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SimOutputManagerMsgr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SimOutputManager
{
public:
  SimOutputManager();
  ~SimOutputManager();

  void Initialize();

  void BeginOfEventAction(const G4Event *event);
  void EndOfEventAction(const G4Event *event);

public: // UI commands
  void AddEdep(G4double edep) { mEdep += edep; }
  void AddEProton(G4double protonE) { eProtons += protonE; }
  void AddEElectron(G4double electronE) { eElectrons += electronE; }
  void AddEGamma(G4double gammaE) { eGammas += gammaE; }
  void AddEC12(G4double c12E) { eC12 += c12E; }
  void AddEDeuteron(G4double deuteronE) { eDeuteron += deuteronE; }

private:
  void Reset();
  void SetStackingActionOutputs();

  template <typename T>
  T GetHitsCollection(const G4String &name,
                      const G4Event *event) const;

private: // members
  // General outputs
  int mEventID;
  double mEdep;
  double eProtons;
  double eElectrons;
  double eGammas;
  double eC12;
  double eDeuteron;
  int mEmittedScntPhotonNum;
  int mEmittedCerenkovPhotonNum;

  std::vector<G4double> mOPEnergyVec;
  std::vector<G4double> mOPWavelengthVec;
  std::vector<G4double> mOPTimeVec;
  std::ofstream outputFile_;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

template <typename T>
T SimOutputManager::GetHitsCollection(
    const G4String &name,
    const G4Event *event) const
{
  // Get hits collections IDs (only once)
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(name);

  auto hitsCollection = static_cast<T>(event->GetHCofThisEvent()->GetHC(hcID));

  if (!hitsCollection)
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
                "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
