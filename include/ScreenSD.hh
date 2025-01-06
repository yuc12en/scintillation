#ifndef SENSITIVE_HH
#define SENSITIVE_HH

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4OpticalPhoton.hh"
#include "G4Step.hh"
#include "G4Track.hh"

#include "G4AnalysisManager.hh"

#include "ScreenHit.hh"

class ScreenSD : public G4VSensitiveDetector
{
public:
  ScreenSD(const G4String& name, const G4String& hitsCollectionName);
	~ScreenSD() override = default;
	void   Initialize(G4HCofThisEvent* hitCollection) override;

	G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
  private:
    ScreenHitsCollection* fHitsCollection = nullptr;
};

#endif
