void entries(){
  TFile* f = new TFile("Statistics.root", "READ");
  TTree* tree = (TTree*)f->Get("Detector");
  int nEntry = tree->GetEntries();

  std::cout<<nEntry<<std::endl;
}
