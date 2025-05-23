#include "DetectorConstruction.hh"
#include "G4tgbVolumeMgr.hh"


const G4double WORLD_RADIUS  = 1.2*m;
const G4double TARGET_RADIUS = 2.54*cm;
const G4double TARGET_HEIGHT = 5.08*cm;
const G4double TARGET_POS_SHIFT = 101.27*cm;

DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

void DetectorConstruction::defineMaterials()
{
  G4NistManager* manager = G4NistManager::Instance();
  manager->SetVerbose(1); // Utile pour debug

  worldMaterial_ = manager->FindOrBuildMaterial("G4_Galactic");
  targetMaterial_= manager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  casingMaterial_ = manager->FindOrBuildMaterial("G4_Al");
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
  defineMaterials();

  // World Geometry :  Ici on définit le World, donc l'espace de simulation qui est parent
  // à tout ce qu'on voudrait ajouter par la suite !

  // Géométrie de l'objet : Définition purement géométrique de l'objet qu'on veut simuler (cubique ici)
  solidWorld_ = new G4Box("solidWorld", WORLD_RADIUS/3, WORLD_RADIUS/2, WORLD_RADIUS);

  // Volume Logique :  On associe le matériau à la géométrie et on lui ajoute des propriétés
  logicalWorld_= new G4LogicalVolume(solidWorld_,
                                  worldMaterial_,
                                  "logicalWorld");

  // Volume Physique : On place l'objet à un endroit précis dans l'espace de simulation avec une orientation/position spécifique
  physicalWorld_ = new G4PVPlacement(0,                     // Rotation
                                 G4ThreeVector(0,0,0),      // Coordinate
                                 logicalWorld_,             // Logical volume
                                 "physicalWorld",           // Name
                                 0,                         // Mother volume
                                 false,                     // No boolean operation
                                 0,                         // Copy number
                                 true);                     // Overlaps checking

  solidTarget_ = new G4Tubs("solidTarget",
                           0.*cm, TARGET_RADIUS, TARGET_HEIGHT,
                           0*deg, 360.*deg);

  logicalTarget_ = new G4LogicalVolume(solidTarget_,
                                       targetMaterial_,
                                       "logicalTarget");

  G4RotationMatrix* rotation = new G4RotationMatrix();

  rotation->rotateX(90*deg);
  rotation->rotateY(0*deg);
  rotation->rotateZ(0*deg);

  physicalTarget_ = new G4PVPlacement(rotation,                                    // Rotation
                                    G4ThreeVector(0.,0.,TARGET_POS_SHIFT),  // Coordinate
                                    logicalTarget_,                         // Logical volume
                                    "physicalTarget",                       // Name
                                    logicalWorld_,                          // Mother volume
                                    false,                                  // No boolean operation
                                    0,                                      // Copy number
                                    true);                                  // Overlaps checking

  solidCasing_ = new G4Tubs("solidCasing", 0.*cm, TARGET_RADIUS + 2.*mm,
      TARGET_HEIGHT + 2.*mm, 0*deg, 360.*deg);

  hollowCasing_ = new G4SubtractionSolid("hollowCasing", solidCasing_, solidTarget_);

  logicalCasing_ = new G4LogicalVolume(hollowCasing_,
                                        casingMaterial_,
                                        "logicalCasing");

  physicalCasing_ = new G4PVPlacement(rotation,                                    // Rotation
                                     G4ThreeVector(0.,0.,TARGET_POS_SHIFT),  // Coordinate
                                     logicalCasing_,                         // Logical volume
                                     "physicalCasing",                       // Name
                                     logicalWorld_,                          // Mother volume
                                     false,                                  // No boolean operation
                                     0,                                      // Copy number
                                     true);                                  // Overlaps checking
  scoringVolume_ = logicalTarget_;

  return physicalWorld_;
}
