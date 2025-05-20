#include "PhysicsList.hh"
// Plein de fichier d'inclusion natifs de G4 (gère les phénomènes physiques
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4IonElasticPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"

PhysicsList::PhysicsList(): G4VModularPhysicsList()
{
    // EM Physics
    RegisterPhysics(new G4EmStandardPhysics_option4(0));

    // Synchroton Radiation & GN Physics
    RegisterPhysics(new G4EmExtraPhysics(0));

    // Decays
    RegisterPhysics(new G4DecayPhysics(0));
    RegisterPhysics(new G4RadioactiveDecayPhysics(0));

    // Hadron Elastic scattering
    RegisterPhysics(new G4HadronElasticPhysicsHP(0));

    // Hadron Physics
    RegisterPhysics( new G4HadronPhysicsQGSP_BIC_HP(0));

    // Stopping Physics
    RegisterPhysics(new G4StoppingPhysics(0));

    // Ion Physics
    RegisterPhysics(new G4IonElasticPhysics(0));
    RegisterPhysics(new G4IonPhysics(0));

}

PhysicsList::~PhysicsList() {}




