#include "TrackingAction.hh"
#include "G4Track.hh"
#include "G4Neutron.hh"
#include "G4SystemOfUnits.hh"
#include "G4TrackStatus.hh"
#include "G4ios.hh" // for G4cout
#include "G4AnalysisManager.hh"
#include "G4Gamma.hh"
#include "G4OpticalPhoton.hh"
#include "G4VProcess.hh"

TrackingAction::TrackingAction(EventAction *eventAction)
{
    eventAction_ = eventAction;
}

TrackingAction::~TrackingAction() {}

void TrackingAction::PreUserTrackingAction(const G4Track *aTrack)
{
}

void TrackingAction::PostUserTrackingAction(const G4Track *track)
{
    // if (track->GetDefinition() == G4Gamma::Definition())
    // {
    //     G4TrackStatus status = track->GetTrackStatus();
    //     G4double finalKE = track->GetKineticEnergy();

    //     auto analysisManager = G4AnalysisManager::Instance();
    //     analysisManager->FillH1(0, 1 * MeV - finalKE / MeV);
    //     trackCount_++;
    //     G4cout << trackCount_ << G4endl;

    //     G4cout << "\n[Neutron Track Ended]" << G4endl;
    //     G4cout << "  Energy difference of gamma : " << 1 * MeV - finalKE / MeV << " MeV" << G4endl;
    // }
}