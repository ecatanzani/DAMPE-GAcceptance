#include "TH1F.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TF1.h"
#include "TMath.h"
#include "TFile.h"

void Injection() {

  Int_t n_events = 1e+7;
  Double_t cos2theta,costheta,theta;

  TFile *out_file = new TFile("results.root","RECREATE");
  
  TRandom3* r_gen = new TRandom3(9);
  TH1F *h_cos2theta = new TH1F("h_cos2theta","cos^2 theta histo",100,0,1);
  TH1F *h_costheta = new TH1F("h_costheta","costheta histo",100,0,1);
  TH1F *h_theta = new TH1F("h_theta","theta histo",100,0,TMath::Pi()/2);
  
  for(Int_t idx=0; idx<n_events; idx++) {

    cos2theta=r_gen->Uniform(0,1);
    costheta = sqrt(cos2theta);
    theta = acos(costheta);

    //printf("%f %f %f\n", cos2theta, costheta, theta);
    
    h_cos2theta->Fill(cos2theta);
    h_costheta->Fill(costheta);
    h_theta->Fill(theta);
    
  }

  h_cos2theta->Write();
  h_costheta->Write();
  h_theta->Write();

  TCanvas *c1 = new TCanvas();
  c1->Divide(1,3);
  c1->cd(1);
  h_cos2theta->Draw();
  c1->cd(2);
  h_costheta->Draw();
  c1->cd(3);
  h_theta->Draw();
  
}
