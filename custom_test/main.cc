#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "myDetector.hh"
#include "myPhysics.hh"
#include "myGun.hh"
#include "myGen.hh"

int main(int argc, char** argv)
{
    G4RunManager* runManager = new G4RunManager();
    runManager->SetUserInitialization(new MyDetector());
    runManager->SetUserInitialization(new MyPhysics());
    runManager->SetUserInitialization(new MyGun());
    runManager->Initialize();

    G4UIExecutive* ui = new G4UIExecutive(argc, argv);

    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();


    G4UImanager* UIManager = G4UImanager::GetUIpointer();

    UIManager->ApplyCommand("/control/execute vis.mac");
    //UIManager->ApplyCommand("/vis/open OGL");
    //UIManager->ApplyCommand("/vis/drawVolume");
    //UIManager->ApplyCommand("/vis/scene/add/trajectories smooth");
    //UIManager->ApplyCommand("/vis/viewer/set/autoRefresh true");


    ui->SessionStart();

    return 0;
}
