#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) :
G4VSensitiveDetector(name)
{}
MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory* ROhist)
{
    G4Track* track = aStep->GetTrack();


    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint* postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();

    //G4cout << "Photon position: " << posPhoton << G4endl;

    const G4VTouchable* touchable = preStepPoint->GetTouchable();
    G4VPhysicalVolume* physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();
    G4cout << "DEtector hit : " << posDetector << G4endl;
}
