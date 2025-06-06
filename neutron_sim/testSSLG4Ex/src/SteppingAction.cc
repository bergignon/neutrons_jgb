#include "SteppingAction.hh"
#include "SimOutputManager.hh"
#include "G4Step.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(SimOutputManager *simMan)
    : mSimOutputManager(simMan)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step *step)
{
  G4ParticleDefinition *particleDef = step->GetTrack()->GetDefinition();
  if (particleDef == G4OpticalPhoton::OpticalPhotonDefinition())
    return;

  // get volume of the current step
  G4VPhysicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  // check if we are in scoring volume
  if (volume->GetName() != "physicalTarget")
    return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  mSimOutputManager->AddEdep(edepStep);

  // G4cout << edepStep << " : Deposit" << G4endl;
  G4Track *track = step->GetTrack();

  const std::vector<const G4Track *> *secondaries = step->GetSecondaryInCurrentStep();

  if (secondaries && !secondaries->empty())
  {
    for (size_t i = 0; i < secondaries->size(); ++i)
    {
      const G4Track *secTrack = (*secondaries)[i];
      const G4ParticleDefinition *particleDef = secTrack->GetDefinition();

      G4String particleName = particleDef->GetParticleName();
      G4double kineticEnergy = secTrack->GetKineticEnergy();

      // if (particleName != "opticalphoton")
      // {
      //   G4cout << "Secondary " << particleName << " : " << kineticEnergy << G4endl;
      // }

      if (particleName == "proton")
      {
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillH1(0, kineticEnergy);
        // outputFile_ << std::fixed << std::setprecision(7) << kineticEnergy << "\n";
        mSimOutputManager->AddEProton(kineticEnergy);
      }
      else if (particleName == "e-")
      {
        mSimOutputManager->AddEElectron(kineticEnergy);
      }
      else if (particleName == "gamma")
      {
        mSimOutputManager->AddEGamma(kineticEnergy);
      }
      else if (particleName == "deuteron")
      {
        mSimOutputManager->AddEDeuteron(kineticEnergy);
      }
      else if (particleName == "C12")
      {
        mSimOutputManager->AddEC12(kineticEnergy);
      }
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
