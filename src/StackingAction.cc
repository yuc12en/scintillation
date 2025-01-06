#include "StackingAction.hh"


G4ClassificationOfNewTrack MyStackingAction::ClassifyNewTrack(const G4Track* aTrack){

  // if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  // {  // particle is optical photon
  //   if(aTrack->GetParentID() > 0)
  //   {  // particle is secondary
  //     if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
  //     {
  //     	G4int trackID = aTrack->GetTrackID();
  //     	G4cout<<"Scintillation just Happend!\t" << "ID: "<< trackID <<G4endl;
  //     }
  //   }
  // }

	// if (particleDef==opticalphoton){
	// 	G4int trackID = aTrack->GetTrackID();
	// 	G4cout<<"Stacking Photon ... \tID: "<<trackID<<G4endl;
	    // G4double thermal_T = 273.15;
		// G4double K = 8.314;  // Boltzmann constant in Mole
		// G4double quenching_celcius = 375;

		// G4double activation_energy = 15000;  // J/Mole, which decides the rate of degradation
		// G4double scale_factor = G4Exp(activation_energy/(K*(thermal_T+quenching_celcius)));  // which decides the magnitude of thermal quenching rate
		// G4double current_celcius = 25;
	//   	G4double delta = aTrack -> GetStepLength();
	//   	G4double velocity = aTrack -> GetVelocity();
	//   	if(velocity == 0)
	//   		return fUrgent;
	//   	else{
	//   		quenching_probability = deltaTime*scale_factor*G4Exp(-activation_energy/(K*(thermal_T+current_celcius)));
	//   		G4double rand = G4UniformRand();
	//   		if (rand<quenching_probability):
	//   			return fKill;
	//   		else
	//   			return fUrgent;
	//   	}
	// }
	return fUrgent;
}
