#include "DetectorConstruction.hh"
#include "G4Threading.hh"
#include "G4ios.hh"
#include "ScreenSD.hh"
#include "G4SubtractionSolid.hh"

MyDetectorConstruction::MyDetectorConstruction(G4double aLY)
{
  LY = aLY;
}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
  SetMaterial();
  SetMaterialProperty();

  // solid
  G4double world_size = 10 *mm;
  G4double sample_size = 5 *mm;
  G4double sample_thickness = 1 *mm;

  G4double screen_thickness = 1 *mm;


  auto solidWorld = new G4Box("World", 0.5*world_size+screen_thickness, 0.5*world_size+screen_thickness,0.5*world_size+screen_thickness);
  auto solidSpace = new G4Box("World", 0.5*world_size,0.5*world_size, 0.5*world_size);

  auto solidScreen = new G4SubtractionSolid("Screen", solidWorld, solidSpace);

    // new G4Box("Screen", 0.5*screen_size, 0.5*screen_size, 0.5*screen_thickness);


  auto logicWorld = new G4LogicalVolume(solidWorld, world_mat, "logicWorld");
  auto physicWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physicWorld", 0, false,0, true);

  auto solidSample = new G4Box("Sample", 0.5*sample_size, 0.5*sample_size, 0.5*sample_thickness);
  auto logicSample = new G4LogicalVolume(solidSample, scintillator_mat, "logicSample");
  auto physicSample = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),logicSample, "physicSample",logicWorld, false, 0, true);
  logicScreen = new G4LogicalVolume(solidScreen, vacuum_mat, "logicScreen");  // however it should be vaccum
  // auto physicScreen = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.5*world_size-0.5*screen_thickness),logicScreen, "physicScreen",logicWorld, false, 0, true);

  auto physicScreen = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicScreen, "physicScreen",logicWorld, false, 0, true);

  // -------------------------------------------------------------------------------
  return physicWorld;
}

void MyDetectorConstruction::SetMaterial(){
  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;

  auto nist = G4NistManager::Instance();

  // world material
  world_mat = nist->FindOrBuildMaterial("G4_AIR");

  // inner layer material
  scintillator_mat = new G4Material("scintillator_mat", 2.54*g/cm3, 5);
  G4Material *SiO2 = new G4Material("SiO2", 2.2021*g/cm3, 2);
  SiO2->AddElement(nist->FindOrBuildElement("Si"),1);
  SiO2->AddElement(nist->FindOrBuildElement("O"),2);

  G4Material *MgO = new G4Material("MgO", 3.58*g/cm3, 2);
  MgO->AddElement(nist->FindOrBuildElement("Mg"),1);
  MgO->AddElement(nist->FindOrBuildElement("O"),1);

  G4Material *Al2O3 = new G4Material("Al2O3", 4.0*g/cm3, 2);
  Al2O3->AddElement(nist->FindOrBuildElement("Al"),2);
  Al2O3->AddElement(nist->FindOrBuildElement("O"),3);
  
  G4Material *Li2O = new G4Material("Li2O", 2.013*g/cm3, 2);
  Li2O->AddElement(nist->FindOrBuildElement("Li"),2);
  Li2O->AddElement(nist->FindOrBuildElement("O"),1);

  G4Material *Ce2O3 = new G4Material("Ce2O3", 6.2*g/cm3, 2);
  Ce2O3->AddElement(nist->FindOrBuildElement("Ce"),2);
  Ce2O3->AddElement(nist->FindOrBuildElement("O"),3);

  scintillator_mat->AddMaterial(SiO2, 57*perCent);
  scintillator_mat->AddMaterial(MgO, 4*perCent);
  scintillator_mat->AddMaterial(Al2O3, 18*perCent);
  scintillator_mat->AddMaterial(Li2O, 18*perCent);
  scintillator_mat->AddMaterial(Ce2O3, 3*perCent);

  // outer layer mateiral
  sillica_mat = SiO2;

  vacuum_mat = new G4Material("Vacuum", z = 1., a = 1.01 * g / mole,
                           density = CLHEP::universe_mean_density, kStateGas,
                           0.1 * kelvin, 1.e-19 * pascal);
}


void MyDetectorConstruction::SetMaterialProperty(){
  auto inner_MPT = new  G4MaterialPropertiesTable();
  auto outer_MPT = new  G4MaterialPropertiesTable();
  auto world_MPT = new  G4MaterialPropertiesTable();
  auto vacuum_MPT = new G4MaterialPropertiesTable();

  // std::vector<G4double> scint_SCINT = { 0.1, 1.0, 0.1 };
  // std::vector<G4double> scint_RIND  = { 1.59, 1.57, 1.54 };


  // using fused silica refractive index
  std::vector<G4double> refractiveEnergy = { 7.0 * eV, 7.07 * eV, 7.14 * eV };
  std::vector<G4double> refractiveIndex = {1.55, 1.55, 1.55};
  inner_MPT->AddProperty("RINDEX",refractiveEnergy, refractiveIndex);

  // ABSLENGTH parameter void
  std::vector<G4double> absorbEnergy = { 7.0 * eV, 7.07 * eV, 7.14 * eV };
  std::vector<G4double> absorbLength = { 10. * mm, 10. * mm, 10. * mm };
  inner_MPT->AddProperty("ABSLENGTH", absorbEnergy, absorbLength);

 // parameter converted from experiement data
  
  std::vector<G4double> energy = {2.106*eV, 2.18*eV, 2.259*eV, 2.344*eV, 2.436*eV, 2.535*eV, 2.643*eV, 2.761*eV, 2.889*eV, 3.03*eV, 3.186*eV, 3.358*eV, 3.55*eV, 3.765*eV, 4.008*eV};
  std::vector<G4double> scintillation = {0.035, 0.029, 0.027, 0.058, 0.041, 0.056, 0.05, 0.081, 0.104, 0.144, 0.17, 0.097, 0.042, 0.027, 0.039};
  inner_MPT->AddProperty("SCINTILLATIONCOMPONENT1", energy, scintillation);
  inner_MPT->AddConstProperty("RESOLUTIONSCALE", 1.0);

  // G4OpticalParameters::Instance()->SetScintByParticleType(true);
  inner_MPT->AddConstProperty("SCINTILLATIONYIELD", LY / keV);
  inner_MPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 20. * ns);
  inner_MPT->AddConstProperty("SCINTILLATIONYIELD1", 1.0);

  // onlyl one component at current stage
  // inner_MPT->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 45. * ns);
  // inner_MPT->AddProperty("SCINTILLATIONCOMPONENT2", scint_Energy, scint_SCINT);
  // inner_MPT->AddConstProperty("SCINTILLATIONYIELD2", 0.0);


  scintillator_mat->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);
  scintillator_mat->SetMaterialPropertiesTable(inner_MPT);


  outer_MPT->AddProperty("RINDEX", "Fused Silica");
  sillica_mat->SetMaterialPropertiesTable(outer_MPT);

  world_MPT->AddProperty("RINDEX", "Air");
  world_mat->SetMaterialPropertiesTable(world_MPT);

  std::vector<G4double> vacuum_Energy = { 7.0 * eV, 7.07 * eV, 7.14 * eV };
  std::vector<G4double> vacuum_RIND = {1., 1., 1.};
  vacuum_MPT->AddProperty("RINDEX", vacuum_Energy, vacuum_RIND);
  vacuum_mat->SetMaterialPropertiesTable(vacuum_MPT);

}

void MyDetectorConstruction::ConstructSDandField()
{
  G4String SDname = "SensitiveScreen";
  G4String HitCollectionName =  "ScreenHitCollection";
  auto aSD = new ScreenSD(SDname, HitCollectionName);
  G4SDManager::GetSDMpointer()->AddNewDetector(aSD);
  SetSensitiveDetector(logicScreen,aSD);
}
