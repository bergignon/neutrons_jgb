#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4AnalysisManager.hh"
#include "G4Neutron.hh"
#include "G4Gamma.hh"
#include "G4VProcess.hh"
#include "G4Proton.hh"

SteppingAction::SteppingAction(EventAction *eventAction) : eventAction_(eventAction)
{
  outputFile_.open("output.csv");
}

SteppingAction::~SteppingAction()
{
  if (outputFile_.is_open())
  {
    outputFile_.close();
  }
}

void SteppingAction::UserSteppingAction(const G4Step *step)
{
  /*
   *
   *      VOLUME CHECK SECTION
   *
   */

  if (!scoringVolume_)
  {
    const auto detConstruction = static_cast<const DetectorConstruction *>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    scoringVolume_ = detConstruction->getScoringVolume();
  }

  G4LogicalVolume *currentVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  if (currentVolume != scoringVolume_)
  {
    return; // Avoid looking at events outside the target
  }

  /*
   *
   *     SECTION TO CHECK ENERGY DEPOSIT
   *
   */

  G4double edepStep = step->GetTotalEnergyDeposit();
  eventAction_->AddEDeposit(edepStep);

  /*
   *
   *    THIS SECTION IS FOR SECONDARY PARTICLE ANALYSIS
   *
   */

  const std::vector<const G4Track *> *secondaries = step->GetSecondaryInCurrentStep();
  auto analysisManager = G4AnalysisManager::Instance();
  if (!secondaries->empty())
  {
    for (const auto &secondary : *secondaries)
    {
      if (secondary->GetDefinition() == G4Proton::ProtonDefinition())
      {
        G4String processName = secondary->GetCreatorProcess()->GetProcessName();
        if (processName == "hadElastic")
        {
          G4double protonEnergy = secondary->GetKineticEnergy();
          G4double lightEnergy = (0.62 * protonEnergy) - (1.3 * (1 - std::exp(-0.39 * std::pow(protonEnergy, 0.97))));
          eventAction_->AddLightOutput(lightEnergy);
        }
      }
    }
  }
}
