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
    // auto analysisManager = G4AnalysisManager::Instance();
    // analysisManager->CreateH1("nd", "Energy deposited by gammas", 200, 0, 2000 * keV);
    // analysisManager->CreateH1("np", "Number of scintillation photons", 240, 0, 1200 * keV);
    // analysisManager->CreateH1("npc", "Number of scintillation + cerenkov photons", 200, 0, 2000 * keV);
}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run *run)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("output.csv");
    analysisManager->CreateH1("nd" + to_string(run->GetRunID()), "Energy deposited by neutrons (%)", 300, 0, 150);
}

void RunAction::EndOfRunAction(const G4Run *run)
{
    auto analysisManager = G4AnalysisManager::Instance();
    // analysisManager->Write();
    // analysisManager->CloseFile();
}
