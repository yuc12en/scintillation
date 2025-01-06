#ifndef STACK_HH
#define STACK_HH

#include "G4UserStackingAction.hh"
#include "G4ios.hh"
#include "G4OpticalPhoton.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "Randomize.hh"


class MyStackingAction : public G4UserStackingAction
{
public:
	MyStackingAction() = default;
	~MyStackingAction()= default;

	G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack) override;
};







#endif