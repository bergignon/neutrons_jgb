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
    // analysisManager->CreateH1("np", "Number of scintillation + cerenkov photons", 200, 0, 2000 * keV);
}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run *run)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("output.csv");
    // analysisManager->CreateH1("nd" + to_string(run->GetRunID()), "Energy deposited by neutrons (%)", 1000, 0, 150);
    // analysisManager->CreateH1("pe", "Energy of secondary protons", 300, 0, 1 * MeV);
    analysisManager->CreateH1("lo" + to_string(run->GetRunID()), "Light output", 1000, 0, 12 * MeV);
}

void RunAction::EndOfRunAction(const G4Run *run)
{
    auto analysisManager = G4AnalysisManager::Instance();
    // analysisManager->Write();
    // analysisManager->CloseFile();
}
