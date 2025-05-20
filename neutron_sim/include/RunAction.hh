#ifndef RUN_H
#define RUN_H

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"

class RunAction : public G4UserRunAction
{
public:

    RunAction();
    ~RunAction();

    void BeginOfRunAction(const G4Run* run) override;
    void EndOfRunAction(const G4Run* run) override;

};

#endif
