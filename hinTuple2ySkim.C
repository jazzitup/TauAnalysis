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

  TString fname =  "upcDatahinTupleExample.root";
  //  TFile* f1  = new TFile(fname.Data());
  
  TChain *hltTree = new TChain("hltanalysis/HltTree");
  //  TTree *hltTree = (TTree*)f1->Get("hltanalysis/HltTree");
  hltTree->Add(fname);
  
  int trigger0 ; 
  TBranch        *b_trigger0;
  hltTree->SetBranchAddress("HLT_HIUPC_SingleMuOpen_NotMBHF2AND_v1", &trigger0, &b_trigger0);

  //  hltTree->Add(fname.Data());



    
  TChain *mytree = new TChain("ggHiNtuplizer/EventTree");
  //  TTree *mytree = (TTree*)f1->Get("ggHiNtuplizer/EventTree");
  mytree->Add(fname);
  
  Int_t   nEle;

  vector<float>   *eleEta;
  vector<float>   *elePhi;
  vector<float>   *elePt;

  eleEta=0;
  elePt=0;
  elePhi=0;
    
  TBranch        *b_nEle;   //!
  TBranch        *b_elePt;   //!
  TBranch        *b_eleEta;   //!
  TBranch        *b_elePhi;   //!
  
  mytree->SetBranchAddress("nEle", &nEle, &b_nEle);
  mytree->SetBranchAddress("elePt", &elePt, &b_elePt);
  mytree->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
  mytree->SetBranchAddress("elePhi", &elePhi, &b_elePhi);

  //  mytree->Add(fname.Data());
  
  // event loop start
  if(nevt == -1) nevt = mytree->GetEntries();
  for(int iev=0; iev<nevt ; ++iev)
  {

    hltTree->GetEntry(iev);
    mytree->GetEntry(iev);

    //    cout << " trigger0 =" << trigger0 << endl;
    //    cout << " nEle = " << nEle << endl;
    if ( nEle>0)   {
      cout << "nEle = " << nEle << endl;
      cout << "pt = " << elePt->at(0) << endl;
      cout << "eta = " << eleEta->at(0) << endl;
      cout << "phi = " << elePhi->at(0) << endl;
      
    }
    
  }
}
