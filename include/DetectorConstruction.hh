#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4Material.hh"
#include "G4OpticalParameters.hh"

// #include "SensitiveDetector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{

  public:
    MyDetectorConstruction(G4double aLY);
    ~MyDetectorConstruction() override = default;

    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

    G4LogicalVolume* GetInnerLayer() const {return logicInnerLayer;};
    G4LogicalVolume* GetOuterLayer() const {return logicOuterLayer;};
    G4LogicalVolume* GetlogicScreen() const {return logicScreen;};

    
    void SetMaterial();
    void SetMaterialProperty();
    
  private:
    G4double LY;
    G4Material* scintillator_mat;
    G4Material* sillica_mat;
    G4Material* world_mat;
    G4Material* vacuum_mat;


    G4LogicalVolume* logicInnerLayer=nullptr;
    G4LogicalVolume* logicOuterLayer=nullptr;
    G4LogicalVolume* logicScreen=nullptr;
};

#endif
