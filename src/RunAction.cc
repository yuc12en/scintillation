#include "RunAction.hh"

RunAction::RunAction(G4String afilename){
	filename = afilename;
	auto man = G4AnalysisManager::Instance();
	man->SetNtupleMerging(true);
	man->CreateNtuple("Detector", "Photon");
	man->CreateNtupleDColumn("energy");
	man->FinishNtuple(0);

}

void RunAction::BeginOfRunAction(const G4Run*){
	auto man = G4AnalysisManager::Instance();
	man->OpenFile(filename);
}
void RunAction::EndOfRunAction(const G4Run*){
	auto man = G4AnalysisManager::Instance();
	man->Write();
	man->CloseFile();
}
