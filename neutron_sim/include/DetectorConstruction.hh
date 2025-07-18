// On évite de définir la classe DetectorConstruction plusieurs fois si DetectorConstruction.hh est inclus dans le main et le DetectorConstruction.cc par exemple
#ifndef DETECTORCONSTRUCTION_H
#define DETECTORCONSTRUCTION_H

// Inclusion de bibliothèques Geant4
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4tgrMessenger.hh"
#include "G4SubtractionSolid.hh"

// Inclusion de bibliothèque propre à C++ :std::vector est la classe que l'on peut utiliser
#include <vector>

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume *Construct();
    void defineMaterials();
    G4LogicalVolume *getScoringVolume() const { return scoringVolume_; }

private:
    // Par convention C++, il est standard d'ecrire les attributs prives en camelCase
    // avec un _ pour indiquer que ce sont des attributs prives

    // On définit un pointeur (scoringVolume_) qui nous donne un volume logique
    // qui sera sensitive! (collecte de données)

    G4LogicalVolume *scoringVolume_;

    G4Material *worldMaterial_;
    G4Material *targetMaterial_;
    G4Material *casingMaterial_;

    // Geometry
    // Puisqu'on ne calcule que le depot d'energie du neutron
    // on a pas besoin d'un detecteur

    // Solid volumes
    G4Box *solidWorld_;
    G4SubtractionSolid *solidDetector_;
    G4Tubs *solidTarget_;
    G4Tubs *solidCasing_;
    G4SubtractionSolid *hollowCasing_;

    // Logical volumes
    G4LogicalVolume *logicalDetector_;
    G4LogicalVolume *logicalWorld_;
    G4LogicalVolume *logicalTarget_;
    G4LogicalVolume *logicalCasing_;

    // Physical volumes
    G4VPhysicalVolume *physicalDetector_;
    G4VPhysicalVolume *physicalWorld_;
    G4VPhysicalVolume *physicalTarget_;
    G4VPhysicalVolume *physicalCasing_;
};

#endif
