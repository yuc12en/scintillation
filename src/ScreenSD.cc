#include "ScreenSD.hh"

ScreenSD::ScreenSD(const G4String& name,
		   const G4String& hitsCollectionName)
  : G4VSensitiveDetector(name)
{
  collectionName.insert(hitsCollectionName);
}

void ScreenSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection

  fHitsCollection
    = new ScreenHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce

  G4int hcID
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection );
}

G4bool ScreenSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{

  auto newHit = new ScreenHit();
  newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
  fHitsCollection->insert( newHit );

    static G4ParticleDefinition* opticalphoton =
      G4OpticalPhoton::OpticalPhotonDefinition();

    const G4ParticleDefinition* particleDef =
      aStep->GetTrack()->GetDynamicParticle()->GetParticleDefinition();


	if (particleDef==opticalphoton)
	{
    G4Track* aTrack = aStep->GetTrack();
    G4double energy = aTrack->GetKineticEnergy();

    auto man = G4AnalysisManager::Instance();
    man->FillNtupleDColumn(0, energy);
	man->AddNtupleRow(0);
	}
    return true;
}
