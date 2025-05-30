#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <iostream>


RunAction::RunAction()
{
    auto analysisManager = G4AnalysisManager::Instance();
    // analysisManager->CreateH1("Edep", "Energy deposited by neutrons", 420, 0., 420*keV);
    analysisManager->CreateH1("Edep", "Energy deposited by neutrons", 1300, 0., 1300*keV);
    // analysisManager->CreateH2("Edep", "Energy deposited by neutrons", 
    //                             420, 0., 420*keV,
    //                             50, 1., 10.*MeV);
}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("output.csv");
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    auto analysisManager = G4AnalysisManager::Instance();
    // analysisManager->Write();
    // analysisManager->CloseFile();
}



