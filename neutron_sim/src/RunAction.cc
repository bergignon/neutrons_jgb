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
    analysisManager->CreateH1("neutronD", "Energy deposited by gammas", 70, 0, 700 * keV);
    // analysisManager->CreateH1("neutronE", "Energy of neutrons", 1000, 0, 1000 * keV);
}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run *)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("output.csv");
}

void RunAction::EndOfRunAction(const G4Run *run)
{
    auto analysisManager = G4AnalysisManager::Instance();
    // analysisManager->Write();
    // analysisManager->CloseFile();
}
