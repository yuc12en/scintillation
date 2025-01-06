#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4Threading.hh"
#include "G4ios.hh"
#include "G4String.hh"

#include <stdlib.h>

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
// #include "G4OpticalPhysics.hh"

#include "FTFP_BERT.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4ios.hh"

#include "MyOpticalPhysics.hh"

int main(int argc,char** argv)
{

  G4double temperature = 25.0;
  G4String filename = "Statistics.root";
  G4double Activation = 7200;
  G4double LY = 15;
  for(G4int i = 1; i < argc; i = i + 2){
    if(G4String(argv[i]) == "-T")
      temperature = strtod(argv[i + 1],NULL);
    if(G4String(argv[i]) == "-f")
      filename= argv[i+1];
    if(G4String(argv[i]) == "-A")
      Activation= strtod(argv[i+1],NULL);
    if(G4String(argv[i]) == "-Y")
      LY = strtod(argv[i+1],NULL);
  }
  auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
  // auto runManager = new G4RunManager();

  auto theDetectorConstruction = new MyDetectorConstruction(LY);
  runManager->SetUserInitialization(theDetectorConstruction);

  
  
  auto thePhysicsList = new FTFP_BERT();
  thePhysicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
  // G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  // thePhysicsList->RegisterPhysics(opticalPhysics);
  // runManager->SetUserInitialization(thePhysicsList);
  MyOpticalPhysics* opticalPhysics = new MyOpticalPhysics(temperature, Activation,0,"Optical");
  thePhysicsList->RegisterPhysics(opticalPhysics);
  runManager->SetUserInitialization(thePhysicsList);
  
  auto theActionInitialization = new MyActionInitialization(filename);
  runManager->SetUserInitialization(theActionInitialization);

  runManager -> SetVerboseLevel(2);
  runManager -> Initialize();
  runManager -> BeamOn(1000);
 
  // auto visManager = new G4VisExecutive();
  // auto *ui = new G4UIExecutive(argc, argv);
  // visManager->Initialize();
  
  // auto UImanager = G4UImanager::GetUIpointer();


  // UImanager->ApplyCommand("/control/execute init_vis.mac");
  // ui->SessionStart();
  
  // delete ui;
  // delete visManager;
  delete runManager;
  return 0;
  }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
