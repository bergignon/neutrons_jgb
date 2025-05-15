#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_hh

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "detector.hh"



class MyDetector : public G4VUserDetectorConstruction
{
public:
    MyDetector();
    ~MyDetector();

    virtual G4VPhysicalVolume* Construct();

private:
    G4LogicalVolume* logicDetector;
    virtual void ConstructSDandField();

};

#endif // CONSTRUCTION_HH
