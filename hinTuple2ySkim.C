// 
#include <ctime>

//#include "cutsAndBin.h"
//#include "RooRealVar.h"

//#include "RooDataSet.h"
//#include "RooGaussian.h"
#include <TLorentzVector.h>
//#include "TriggerManipulation.h" 
#include <TChain.h>

#include "commonUtility.h"
static const long MAXTREESIZE = 10000000000;

TString getDayAndTime();
//bool isTrackMatched(float pt1, float eta1, float phi1, float pt2, float eta2, float phi2) ;
void hinTuple2ySkim( int nevt = -1) { 

  using namespace std;

  //  TString fname =  "/eos/cms/store/group/phys_diffraction/lbyl_2018/HIForward_Reco/ntuples/ntuples_data/HIForward/ntuples_data_lbl/*/*/*.root";
  TString fname = "/eos/cms/store/group/phys_diffraction/lbyl_2018/HIForward_Reco/ntuples/ntuples_data/HIForward/ntuples_data_lbl/200617_140125/0000/*.root";

  //  TString fname = "upcDatahinTupleExample.root";
  //  TFile* f1  = new TFile(fname.Data());
  
  TChain *hltTree = new TChain("hltanalysis/HltTree");
  //  TTree *hltTree = (TTree*)f1->Get("hltanalysis/HltTree");
  hltTree->Add(fname.Data());
  
  int trigger0 ; 
  TBranch        *b_trigger0;
  hltTree->SetBranchAddress("HLT_HIUPC_SingleMuOpen_NotMBHF2AND_v1", &trigger0, &b_trigger0);

  //  hltTree->Add(fname.Data());



    
  TChain *mytree = new TChain("ggHiNtuplizer/EventTree");
  //  TTree *mytree = (TTree*)f1->Get("ggHiNtuplizer/EventTree");
  mytree->Add(fname.Data());
  
  Int_t   nEle;
  vector<float>   *eleEta;
  vector<float>   *elePhi;
  vector<float>   *elePt;
  eleEta=0;  // This initialization is CRUCIAL.  DON'T DELETE! 
  elePt=0;
  elePhi=0;
  TBranch        *b_nEle;   //!
  TBranch        *b_elePt;   //!
  TBranch        *b_eleEta;   //!
  TBranch        *b_elePhi;   //!

  Int_t           nTrk;
  TBranch        *b_nTrk;   //!

  mytree->SetBranchAddress("nEle", &nEle, &b_nEle);
  mytree->SetBranchAddress("elePt", &elePt, &b_elePt);
  mytree->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
  mytree->SetBranchAddress("elePhi", &elePhi, &b_elePhi);
  mytree->SetBranchAddress("nTrk", &nTrk, &b_nTrk);


  // muon
  Int_t           nMu;
  vector<float>   *muPt;
  vector<float>   *muEta;
  vector<float>   *muPhi;

  TBranch        *b_nMu;   //!
  TBranch        *b_muPt;   //!
  TBranch        *b_muEta;   //!
  TBranch        *b_muPhi;   //!

  
  muPt = 0;
  muEta = 0;
  muPhi = 0;
  mytree->SetBranchAddress("nMu", &nMu, &b_nMu);
  mytree->SetBranchAddress("muPt", &muPt, &b_muPt);
  mytree->SetBranchAddress("muEta", &muEta, &b_muEta);
  mytree->SetBranchAddress("muPhi", &muPhi, &b_muPhi);
   
  
  // Output Tree:
  TTree *outt = new TTree("tau","Tau Tree");
  outt->SetMaxTreeSize(MAXTREESIZE);
  
  float mPt, mEta, mPhi, ePt, ePhi, eEta;
  int trig; 
  outt->Branch("mPt", &mPt, "mPt/F");
  outt->Branch("mEta", &mEta, "mEta/F");
  outt->Branch("mPhi", &mPhi, "mPhi/F");
  outt->Branch("ePt", &ePt, "ePt/F");
  outt->Branch("eEta", &eEta, "eEta/F");
  outt->Branch("ePhi", &ePhi, "ePhi/F");
  outt->Branch("nTrk", &nTrk, "nTrk/I"); // Resue nTrk from MyTree
  outt->Branch("trig", &trig, "trig/I"); // Resue nTrk from MyTree
  
  
  
  
  //  mytree->Add(fname.Data());
  
  // event loop start
  if(nevt == -1) nevt = mytree->GetEntries();

  cout << " total number of events = " << nevt << endl;

  for(int iev=0; iev<nevt ; ++iev)
  {
    if ( iev%10000 == 0 )
      cout << iev <<"/"<<nevt << " ("<< int(iev*100./nevt) <<"%%) are done" << endl;
    
    hltTree->GetEntry(iev);
    mytree->GetEntry(iev);
    
    //    cout << " trigger0 =" << trigger0 << endl;
    if ( trigger0 != 1 )
      continue;
    if ( nEle != 1 )
      continue;
    if ( nMu != 1 )
      continue;
    if ( nTrk > 3 )
      continue;
    
    trig = trigger0;
    cout << " found!" << endl;
    //    cout << "nEle = " << nEle << endl;
    //    cout << "pt = " << elePt->at(0) << endl;
    //    cout << "eta = " << eleEta->at(0) << endl;
    //    cout << "phi = " << elePhi->at(0) << endl;
    //    cout << "nTrk = " << nTrk << endl;

    ePt = elePt->at(0);
    eEta = eleEta->at(0);
    ePhi = elePhi->at(0);
    mPt = muPt->at(0);
    mEta = muEta->at(0);
    mPhi = muPhi->at(0);

    outt->Fill();
  }

  TFile* outf = new TFile("output.root","recreate");
  outt->Write();
  outf->Close();
}
