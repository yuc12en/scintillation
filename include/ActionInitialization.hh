#ifndef ACTION_HH 
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "StackingAction.hh"
#include "RunAction.hh"
// #include "EventAction.hh"
// #include "SteppingAction.hh"
#include "DetectorConstruction.hh"


class MyActionInitialization : public G4VUserActionInitialization
{
  public:
    MyActionInitialization(G4String afilename);
    ~MyActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build() const override;
private:
  G4String filename;
};


#endif
