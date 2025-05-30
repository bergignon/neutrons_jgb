#include <iostream>
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4ParticleHPManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
//#include "G4MPImanager.hh"
//#include "G4MPIsession.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "Action.hh"

int main(int argc, char** argv)
{
  // --------------------------------------------------------------------
  // MPI session
  // --------------------------------------------------------------------
  // At first, G4MPImanager/G4MPIsession should be created.
  // G4MPImanager* g4MPI = new G4MPImanager(argc, argv);
  // MPI session (G4MPIsession) instead of G4UIterminal
  // Terminal availability depends on your MPI implementation.
  // G4MPIsession* session = g4MPI-> GetMPIsession();

  G4long seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);
  G4Random::setTheSeed(seed);

  // #ifdef G4MULTITHREADED
  // auto runManager = new G4MTRunManager();
  // #else

  auto runManager = new G4RunManager();

  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization());
  runManager->Initialize();

  G4UImanager* UIManager = G4UImanager::GetUIpointer();

  if (argc == 2) {
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    UIManager->ApplyCommand("/control/execute vis.mac");
    UIManager->ApplyCommand("/control/execute run.mac");
    ui->SessionStart();

    delete ui;
    delete visManager;
    delete runManager;
    return 0;
  }  

  UIManager->ApplyCommand("/control/execute run.mac");

  delete runManager;
  return 0;
}
