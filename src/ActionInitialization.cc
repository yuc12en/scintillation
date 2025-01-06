#include "ActionInitialization.hh"

MyActionInitialization::MyActionInitialization(G4String afilename){
  filename = afilename;
}

void MyActionInitialization::BuildForMaster() const{

  auto runAction = new RunAction(filename);
  SetUserAction(runAction);
}
void MyActionInitialization::Build() const
{
  auto runAction = new RunAction(filename);
  SetUserAction(runAction);
  SetUserAction(new PrimaryGeneratorAction());
  SetUserAction(new MyStackingAction());
  // auto steppingAction = new SteppingAction();
  // SetUserAction(steppingAction);
}
