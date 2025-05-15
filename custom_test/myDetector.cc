#include "myDetector.hh"

MyDetector::MyDetector() {}
MyDetector::~MyDetector() {}

G4VPhysicalVolume* MyDetector::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4Material* silDio = new G4Material("SiO2", 2.201*g/cm3, 2);
    silDio->AddElement(nist->FindOrBuildElement("Si"), 1);
    silDio->AddElement(nist->FindOrBuildElement("O"), 2);

    G4Material* wat = new G4Material("H20", 1.000*g/cm3, 2);
    wat->AddElement(nist->FindOrBuildElement("H"), 2);
    wat->AddElement(nist->FindOrBuildElement("O"), 1);

    G4Element* car = nist->FindOrBuildElement("C");

    G4Material* aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    aerogel->AddMaterial(silDio, 62.5*perCent);
    aerogel->AddMaterial(wat, 37.4*perCent);
    aerogel->AddElement(car, 0.1*perCent);

    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double rindexAerogel[2] = {1.1, 1.1};
    G4double rindexWorld[2] = {1.0, 1.0};

    G4MaterialPropertiesTable* mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);

    G4MaterialPropertiesTable* mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

    aerogel->SetMaterialPropertiesTable(mptAerogel);
    worldMat->SetMaterialPropertiesTable(mptWorld);

    G4Box* solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);

    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,
                                                      worldMat, "logicWorld");

    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0),
                                                    logicWorld, "physWorld", 0,
                                                    false, 0, true);

    G4Box* solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);

    G4LogicalVolume* logicRadiator = new G4LogicalVolume(solidRadiator,
                                                         aerogel, "logicRadiator");

    G4VPhysicalVolume* physRadiator = new G4PVPlacement(0, G4ThreeVector(0,0,0.25*m),
                                                        logicRadiator, "physRadiator",
                                                        logicWorld, false, 0, true);


    G4Box* solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);

    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

    for (G4int i = 0; i < 100; i++) {
        for (G4int j = 0; j < 100; j++) {
            G4VPhysicalVolume* physDetector = new G4PVPlacement(0,
                                                               G4ThreeVector(-0.5*m + (i+0.5)*m/100,
                                                                             -0.5*m + (j+0.5)*m/100,
                                                                             0.49*m),
                                                               logicDetector,
                                                               "physDetector",
                                                               logicWorld,
                                                               false,
                                                               i*100 + j,
                                                               true);

        }
    }
    return physWorld;
}

void MyDetector::ConstructSDandField()
{
    MySensitiveDetector* sensDet = new MySensitiveDetector("MyPhotonDetector");
    logicDetector->SetSensitiveDetector(sensDet);
}
