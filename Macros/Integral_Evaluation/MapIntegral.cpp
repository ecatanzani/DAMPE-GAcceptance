#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"

void ComputeIntegral(const TString result_path) {
    
    Double_t integral = 0;
    Double_t wX = 0,wY = 0;
    
    TFile input_results_file(result_path.Data());
    if(input_results_file.IsZombie()) {
        cout<<"\n\nError opening input file. Macro finished\n\n";
        exit(-1);
    }
    TH2D *theta_phi_acceptance = (TH2D*)input_results_file->Get("Acceptance");
    TH1D *numerical_acc = (TH1D*)input_results_file->Get("hacc");
    TH1D *acc_rel_diff = (TH1D*)input_results_file->Get("haccreldiff");
    
    ////////////////////////////////  Maps integral evaluation   //////////////////////////
    
    wX =  theta_phi_acceptance->GetXaxis()->GetBinWidth(bx);
    wY = theta_phi_acceptance->GetYaxis()->GetBinWidth(by);
    
    for(Int_t bx=1; bx<=theta_phi_acceptance->GetNbinsX(); ++bx)
        for(Int_t by=1; by<=theta_phi_acceptance->GetNbinsY(); ++by)
            integral+=wX*wY*theta_phi_acceptance->GetBinContent(bx,by);
    
    std::cout<<"\n\nDifferential acceptance integral: "<<integral<<"\n\n";
    
    TCanvas *c1 = new TCanvas("c1","Acceptance Distribution");
    c1->Divide(1,2);
    c1->cd(1);
    numerical_acc->Draw();
    c1->cd(2);
    acc_rel_diff->Draw();
    
}
