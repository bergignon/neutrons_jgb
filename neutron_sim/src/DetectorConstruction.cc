#include "DetectorConstruction.hh"
#include "G4tgbVolumeMgr.hh"
#include "G4MaterialPropertiesTable.hh"

const G4double WORLD_RADIUS = 1.2 * m;
const G4double TARGET_RADIUS = 2.54 * cm;
const G4double TARGET_HEIGHT = 5.08 * cm;
const G4double TARGET_POS_SHIFT = 102.54 * cm;

DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

void DetectorConstruction::defineMaterials()
{
  G4NistManager *manager = G4NistManager::Instance();

  worldMaterial_ = manager->FindOrBuildMaterial("G4_Galactic");
  // targetMaterial_= manager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  casingMaterial_ = manager->FindOrBuildMaterial("G4_Al");

  G4Element *elH = manager->FindOrBuildElement("H");
  G4Element *elC = manager->FindOrBuildElement("C");

  G4double density = 0.959 * g / cm3;
  G4Material *EJ309 = new G4Material("EJ309", density, 2, kStateLiquid, 293.15 * kelvin, 1 * atmosphere);
  EJ309->AddElement(elH, 0.0948);
  EJ309->AddElement(elC, 0.9052);
  targetMaterial_ = EJ309;

  G4MaterialPropertiesTable *EJ309_MPT = new G4MaterialPropertiesTable();

  G4double photonEnergy[2] = {1.549 * eV, 6.199 * eV};
  G4double rIndex[2] = {1.57, 1.57};
  G4double absLength[2] = {100.0, 100.0};

  G4double photonWavelength[77] = {
      525.000, 523.026, 521.053, 519.079, 517.105, 515.132, 513.158, 511.184, 509.211,
      507.237, 505.263, 503.289, 501.316, 499.342, 497.368, 495.395, 493.421, 491.447,
      489.474, 487.500, 485.526, 483.553, 481.579, 479.605, 477.632, 475.658, 473.684,
      471.711, 469.737, 467.763, 465.789, 463.816, 461.842, 459.868, 457.895, 455.921,
      453.947, 451.974, 450.000, 448.026, 446.053, 444.079, 442.105, 440.132, 438.158,
      436.184, 434.211, 432.237, 430.263, 428.289, 426.316, 424.342, 422.368, 420.395,
      418.421, 416.447, 414.474, 412.500, 410.526, 408.553, 406.579, 404.605, 402.632,
      400.658, 398.684, 396.711, 394.737, 392.763, 390.789, 388.816, 386.842, 384.868,
      382.895, 380.921, 378.947, 376.974, 375.000};

  G4double intensity[77] = {
      0.000, 0.017, 0.056, 0.117, 0.196, 0.296, 0.380, 0.475, 0.553,
      0.615, 0.654, 0.670, 0.682, 0.693, 0.709, 0.726, 0.760, 0.799,
      0.855, 0.899, 0.933, 0.966, 0.989, 1.000, 0.989, 0.955, 0.899,
      0.849, 0.804, 0.788, 0.777, 0.765, 0.760, 0.754, 0.737, 0.715,
      0.687, 0.659, 0.631, 0.603, 0.575, 0.547, 0.520, 0.503, 0.486,
      0.469, 0.453, 0.436, 0.419, 0.402, 0.385, 0.363, 0.346, 0.330,
      0.313, 0.296, 0.279, 0.263, 0.246, 0.223, 0.207, 0.190, 0.173,
      0.162, 0.151, 0.140, 0.128, 0.117, 0.106, 0.095, 0.089, 0.084,
      0.073, 0.073, 0.067, 0.061, 0.050};

  for (int i = 0; i < 77; i++)
  {
    photonWavelength[i] = 1239.8 / photonWavelength[i];
  }

  EJ309_MPT->AddProperty("RINDEX", photonEnergy, rIndex, 2);
  EJ309_MPT->AddProperty("ABSLENGTH", photonEnergy, absLength, 2);
  EJ309_MPT->AddProperty("SCINTILLATIONCOMPONENT1", photonWavelength, intensity, 77);

  EJ309_MPT->AddConstProperty("SCINTILLATIONYIELD", 12300.0 / MeV);
  EJ309_MPT->AddConstProperty("SCINTILLATIONYIELD1", 1);
  EJ309_MPT->AddConstProperty("RESOLUTIONSCALE", 1.0);
  EJ309_MPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 3.5 * ns);
  EJ309_MPT->AddConstProperty("SCINTILLATIONRISETIME1", 1.0 * ns);

  EJ309->SetMaterialPropertiesTable(EJ309_MPT);
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
  defineMaterials();

  // World Geometry :  Ici on définit le World, donc l'espace de simulation qui est parent
  // à tout ce qu'on voudrait ajouter par la suite !

  // Géométrie de l'objet : Définition purement géométrique de l'objet qu'on veut simuler (cubique ici)
  solidWorld_ = new G4Box("solidWorld", WORLD_RADIUS / 3, WORLD_RADIUS / 2, WORLD_RADIUS);

  // Volume Logique :  On associe le matériau à la géométrie et on lui ajoute des propriétés
  logicalWorld_ = new G4LogicalVolume(solidWorld_,
                                      worldMaterial_,
                                      "logicalWorld");

  // Volume Physique : On place l'objet à un endroit précis dans l'espace de simulation avec une orientation/position spécifique
  physicalWorld_ = new G4PVPlacement(0,                      // Rotation
                                     G4ThreeVector(0, 0, 0), // Coordinate
                                     logicalWorld_,          // Logical volume
                                     "physicalWorld",        // Name
                                     0,                      // Mother volume
                                     false,                  // No boolean operation
                                     0,                      // Copy number
                                     true);                  // Overlaps checking

  solidTarget_ = new G4Tubs("solidTarget",
                            0. * cm, TARGET_RADIUS, TARGET_HEIGHT / 2,
                            0 * deg, 360. * deg);

  G4NistManager *manager = G4NistManager::Instance();
  G4Material *lead = manager->FindOrBuildMaterial("G4_Pb");
  G4Material *NaI = manager->FindOrBuildMaterial("G4_SODIUM_IODIDE");

  logicalTarget_ = new G4LogicalVolume(solidTarget_,
                                       targetMaterial_,
                                       "logicalTarget");

  G4RotationMatrix *rotation = new G4RotationMatrix();

  rotation->rotateX(90 * deg);
  rotation->rotateY(0 * deg);
  rotation->rotateZ(0 * deg);

  physicalTarget_ = new G4PVPlacement(rotation,                                // Rotation
                                      G4ThreeVector(0., 0., TARGET_POS_SHIFT), // Coordinate
                                      logicalTarget_,                          // Logical volume
                                      "physicalTarget",                        // Name
                                      logicalWorld_,                           // Mother volume
                                      false,                                   // No boolean operation
                                      0,                                       // Copy number
                                      true);                                   // Overlaps checking

  solidCasing_ = new G4Tubs("solidCasing", 0. * cm, TARGET_RADIUS + 1.5 * mm,
                            TARGET_HEIGHT / 2 + 1.5 * mm, 0 * deg, 360. * deg);

  hollowCasing_ = new G4SubtractionSolid("hollowCasing", solidCasing_, solidTarget_);

  logicalCasing_ = new G4LogicalVolume(hollowCasing_,
                                       casingMaterial_,
                                       "logicalCasing");

  physicalCasing_ = new G4PVPlacement(rotation,                                // Rotation
                                      G4ThreeVector(0., 0., TARGET_POS_SHIFT), // Coordinate
                                      logicalCasing_,                          // Logical volume
                                      "physicalCasing",                        // Name
                                      logicalWorld_,                           // Mother volume
                                      false,                                   // No boolean operation
                                      0,                                       // Copy number
                                      true);

  // Overlaps checking
  scoringVolume_ = logicalTarget_;

  G4Box *detectorBox = new G4Box("solidBox", WORLD_RADIUS / 3 - 2 * mm, WORLD_RADIUS / 2 - 2 * mm, WORLD_RADIUS - 2 * mm);

  solidDetector_ = new G4SubtractionSolid("solidDetector", solidWorld_, detectorBox);

  logicalDetector_ = new G4LogicalVolume(solidDetector_, worldMaterial_, "logicalDetector");

  physicalDetector_ = new G4PVPlacement(0,
                                        G4ThreeVector(0, 0, 0),
                                        logicalDetector_,
                                        "physicalDetector",
                                        logicalWorld_, false, 0, true);
  return physicalWorld_;
}
