{

std::ofstream data_txt("./data_D0_daughtersPT_Eta_Phi_Mass_dau1_dau2_AND_D0PT_Y_Phi_Mass.txt");

//auto f = TFile::Open("root://eos.cms.rcac.purdue.edu//store/user/wxie/Run3_D0_MC_AllGens_wBDT_v1/promptD0ToKPi_PT-0_TuneCP5_5p36TeV_pythia8-evtgen/Run3_D0_MC_AllGens_wBDT_v1/260414_135739/0000/TTree_MC_1.root");

//auto t = (TTree*)f->Get("d0Analyzer/VertexCompositeNtuple"); 

const char* treeName = "d0Analyzer/VertexCompositeNtuple";
TChain *t = new TChain(treeName);
std::ifstream infile("mc-list-100files.txt");
std::string filename;
while (std::getline(infile, filename)) {
   if (!filename.empty()) {
       std::cout << "Adding: " << filename << std::endl;
       t->Add(filename.c_str());
   }
}
infile.close();
std::cout << "Total entries: " << t->GetEntries() << std::endl;
    
int candSize;
int centrality;
float PvtxZ;
float pT[100000];
float y[100000];
float phi[100000];
float mass[100000];
bool isSwap[100000];
bool matchGEN[100000];
float pTD1[100000];
float EtaD1[100000];
float PhiD1[100000];
int idD1_reco[100000];
float pTD2[100000];
float EtaD2[100000];
float PhiD2[100000];
int idD2_reco[100000];

t->SetBranchAddress("candSize",&candSize);
t->SetBranchAddress("centrality",&centrality);
t->SetBranchAddress("PvtxZ",&PvtxZ);
t->SetBranchAddress("pT",&pT);
t->SetBranchAddress("y",&y);
t->SetBranchAddress("phi",&phi);
t->SetBranchAddress("mass",&mass);
t->SetBranchAddress("isSwap",&isSwap);
t->SetBranchAddress("matchGEN",&matchGEN);
t->SetBranchAddress("pTD1",&pTD1);
t->SetBranchAddress("EtaD1",&EtaD1);
t->SetBranchAddress("PhiD1",&PhiD1);
t->SetBranchAddress("idD1_reco",&idD1_reco);
t->SetBranchAddress("pTD2",&pTD2);
t->SetBranchAddress("EtaD2",&EtaD2);
t->SetBranchAddress("PhiD2",&PhiD2);
t->SetBranchAddress("idD2_reco",&idD2_reco);

Int_t nevents = t->GetEntries();

auto th_Dpt = new TH1F("Dpt","Dpt",100,0,30);
auto th_Dy = new TH1F("Dy","Dy",100,-3,3);
auto th_Dphi = new TH1F("Dphi","Dphi",100,-3.3,3.3);
auto th_Dmass = new TH1F("Dmass","Dmass",100,1.4,2.2);

auto th_Dau1pt = new TH1F("Dau1pt","Dau1pt",100,0,30);
auto th_Dau1eta = new TH1F("Dau1eta","Dau1eta",100,-3,3);
auto th_Dau1phi = new TH1F("Dau1phi","Dau1phi",100,-3.3,3.3);
auto th_Dau2pt = new TH1F("Dau2pt","Dau2pt",100,0,30);
auto th_Dau2eta = new TH1F("Dau2eta","Dau2eta",100,-3,3);
auto th_Dau2phi = new TH1F("Dau2phi","Dau2phi",100,-3.3,3.3);


for (Int_t i=0;i<nevents;i++) {

   t->GetEntry(i);

   if(centrality>140 || fabs(PvtxZ)>15.0) continue;

   for(Int_t j=0;j<candSize;j++){

      //if(!((matchGEN[j]==1 && isSwap[j]==0) || (matchGEN[j]==1 && isSwap[j]==1))) continue; //select signal+swap
      if(!(matchGEN[j]==1 && isSwap[j]==0)) continue; //select signal only (no swap)

      float aux_Dpt = pT[j];
      th_Dpt->Fill(aux_Dpt);
      float aux_Dy = y[j];
      th_Dy->Fill(aux_Dy);
      float aux_Dphi = phi[j];
      th_Dphi->Fill(aux_Dphi);
      float aux_Dmass = mass[j];
      th_Dmass->Fill(aux_Dmass);  
            
      float aux_Dau1pt = pTD1[j];
      th_Dau1pt->Fill(aux_Dau1pt);
      float aux_Dau1eta = EtaD1[j];
      th_Dau1eta->Fill(aux_Dau1eta);
      float aux_Dau1phi = PhiD1[j];
      th_Dau1phi->Fill(aux_Dau1phi);

      float aux_Dau2pt = pTD2[j];
      th_Dau2pt->Fill(aux_Dau2pt);
      float aux_Dau2eta = EtaD2[j];
      th_Dau2eta->Fill(aux_Dau2eta);
      float aux_Dau2phi = PhiD2[j];
      th_Dau2phi->Fill(aux_Dau2phi);

      float aux_Dau1mass=0.;
      float aux_Dau2mass=0.;
      if(abs(idD1_reco[j])==211) aux_Dau1mass = 0.13957039;
      if(abs(idD1_reco[j])==321) aux_Dau1mass = 0.493677;
      if(abs(idD2_reco[j])==211) aux_Dau2mass = 0.13957039;
      if(abs(idD2_reco[j])==321) aux_Dau2mass = 0.493677;

      data_txt<<aux_Dau1pt<<" "<<aux_Dau2pt<<" "<<aux_Dau1eta<<" "<<aux_Dau2eta<<" "<<aux_Dau1phi<<" "<<aux_Dau2phi<<" "<<aux_Dau1mass<<" "<<aux_Dau2mass<<" "<<aux_Dpt<<" "<<aux_Dy<<" "<<aux_Dphi<<" "<<aux_Dmass<<endl;

   }	   

}


auto tc_D0_pt = new TCanvas();
tc_D0_pt->cd();
th_Dpt->Draw();

auto tc_D0_y = new TCanvas();
tc_D0_y->cd();
th_Dy->Draw();

auto tc_D0_phi = new TCanvas();
tc_D0_phi->cd();
th_Dphi->Draw();

auto tc_D0_mass = new TCanvas();
tc_D0_mass->cd();
th_Dmass->Draw();

auto tc_Dau_pt = new TCanvas();
tc_Dau_pt->cd();
th_Dau1pt->Draw();
th_Dau1pt->SetLineColor(2);
th_Dau1pt->SetMarkerColor(2);
th_Dau2pt->Draw("same");

auto tc_Dau_eta = new TCanvas();
tc_Dau_eta->cd();
th_Dau1eta->Draw();
th_Dau1eta->SetLineColor(2);
th_Dau1eta->SetMarkerColor(2);
th_Dau2eta->Draw("same");

auto tc_Dau_phi = new TCanvas();
tc_Dau_phi->cd();
th_Dau1phi->Draw();
th_Dau1phi->SetLineColor(2);
th_Dau1phi->SetMarkerColor(2);
th_Dau2phi->Draw("same");


}
