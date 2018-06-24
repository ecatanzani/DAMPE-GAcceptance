#include "MyHead.h"

int main(int argc,char *argv[]) {
    
    ////////////////////////////// Declaring simulation variables
    
    Double_t X[3],dir[3];
    Double_t theta = 0,phi = 0,analytical_acceptance = 0,costheta = 0, bin_content = 0;
    Double_t acceptance[trials_number],acceptance_rel_diff[trials_number];
    Int_t perc,accepted_events[trials_number];
    Bool_t accepted_event;
    
    ///////////////////////////// Stuff variables
    
    std::string log_path = output_path_creator(0),root_out_path = output_path_creator(1);
    std::ofstream output_log_file(log_path);
    create_and_initialize_log(output_log_file);
    
    ///////////////////////// Defining histos....
    
    ///////////////////////////////////////////////////////// Geometrical acceptance histos
    
    TH1F hacc("hacc","Acceptance",100,0.34,0.35);
    hacc.GetXaxis()->SetTitle("Acceptance (m^{2}sr)");
    hacc.GetYaxis()->SetTitle("Trials");
    hacc.SetLineColor(kBlack);
    hacc.SetFillColor(kOrange-9);

    TH1F haccreldiff("haccreldiff","Acceptance Relative Error",100, -0.02, 0.02);
    haccreldiff.GetXaxis()->SetTitle("(Acc_{Meas} - Acc_{True}) / Acc_{True}");
    haccreldiff.GetYaxis()->SetTitle("Trials");
    haccreldiff.SetLineColor(kBlack);
    haccreldiff.SetFillColor(kSpring+1);
    
    TH2D costheta_phi_acceptance("Acceptance","Theta/Phi Acceptance", 500, 0, 1, 500, 0, 2.0*TMath::Pi());
    costheta_phi_acceptance.SetXTitle("cos(#theta)");
    costheta_phi_acceptance.SetYTitle("#phi (rad)");
    costheta_phi_acceptance.SetZTitle("Acceptance (m^{2})");
    
    TH2D* pcostheta_phi_acceptance = &costheta_phi_acceptance;
    
    TH1D Acceptance_X_Proj("Acceptance_X_Proj"," cos(#theta) distribution ",1000,0,1);
    Acceptance_X_Proj.SetXTitle("cos(#theta)");
    Acceptance_X_Proj.SetYTitle("entries");
    
    TH1D Acceptance_Y_Proj("Acceptance_Y_Proj"," #phi distribution ",1000,0,2*TMath::Pi());
    Acceptance_X_Proj.SetXTitle("#phi");
    Acceptance_X_Proj.SetYTitle("entries");
    
    ///////////////////////////////////////////////////////// Events distribution histos
    
    TH2D costheta_phi_inside("EventsDistribution","Events Angular Distibution", 500, 0, 1, 500, 0, 2.0*TMath::Pi());
    costheta_phi_inside.SetXTitle("cos(#theta)");
    costheta_phi_inside.SetYTitle("#phi (rad)");
    costheta_phi_inside.SetZTitle("#events");
    
    ///////////////////////////////////////////////////////// Generated events histos

    TH2D costheta_phi_all("Generated_CosTheta_Phi","Generated Theta/Phi", 500, 0, 1, 500, 0, 2.0*TMath::Pi());
    costheta_phi_all.SetXTitle("cos(#theta)");
    costheta_phi_all.SetYTitle("#phi (rad)");
    
    TH2D* pcostheta_phi_all = &costheta_phi_all;
    
    TH1D cos2theta_gen("cos2theta_gen"," cos^2(#theta) distribution ",1000,0,1);
    cos2theta_gen.SetXTitle("cos^2(#theta)");
    cos2theta_gen.SetYTitle("entries");
    
    TH1D costheta_gen("costheta_gen"," cos(#theta) distribution ",1000,0,1);
    costheta_gen.SetXTitle("cos(#theta)");
    costheta_gen.SetYTitle("entries");
    
    TH1D phi_gen("phi_gen"," #phi distribution ",1000,0,2*TMath::Pi());
    phi_gen.SetXTitle("#phi");
    phi_gen.SetYTitle("entries");
    
    ///////////////////////////////////////////////////////// Selected events histos
    
    TH1D costheta_sel("costheta_sel"," cos(#theta) distribution ",1000,0,1);
    costheta_sel.SetXTitle("cos(#theta)");
    costheta_sel.SetYTitle("entries");
    
    TH1D phi_sel("phi_sel"," #phi distribution ",1000,0,2*TMath::Pi());
    phi_sel.SetXTitle("#phi");
    phi_sel.SetYTitle("entries");
    
  //////////////////////////////////////////////////////////////////
  
  
    TRandom3 rand_gen(trandom3_seed);

    for(Int_t idx=0; idx<trials_number; idx++)
        accepted_events[idx]=0;
  
    for(Int_t idx_trial=0; idx_trial<trials_number; idx_trial++) {
        printf("\n Try[%i]\n",idx_trial);
        output_log_file << "\n Try["<<idx_trial<<"]\n";
        perc=0;
        for(Int_t idx_event=0; idx_event<events_per_trial; idx_event++) {
            if(((Double_t)idx_event/events_per_trial)*100>=perc) {
                perc++;
                printf("\t-> %i%%",perc);
                output_log_file<<"\t-> "<<perc<<"%";
            }
            generate_coordinate(X,rand_gen);
            generate_theta_phi(theta,phi,rand_gen,cos2theta_gen);
            costheta_phi_all.Fill(fabs(cos(theta)),phi);
            costheta_gen.Fill(fabs(cos(theta)));
            phi_gen.Fill(phi);
            obtain_direction(theta,phi,dir);
            check_acceptance(X,dir,theta,accepted_event);
            if(accepted_event) {
                accepted_events[idx_trial]++;
                costheta_phi_acceptance.Fill(fabs(cos(theta)),phi);
                costheta_phi_inside.Fill(fabs(cos(theta)),phi);
                costheta_sel.Fill(cos(theta));
                phi_sel.Fill(phi);
                Acceptance_X_Proj.Fill(fabs(cos(theta)));
                Acceptance_Y_Proj.Fill(phi);
            }
        } //end for on events for each trial
    } //end for on trials

    ///////////////////// Computing acceptance /////////////////////

    analytical_acceptance = Get_Telescope_Analysical_Acceptance(Hdet,Ldet,Ldet,Ldet,Ldet);

    for(Int_t idx_trial=0; idx_trial<trials_number; idx_trial++) {
        acceptance[idx_trial] = Get_Acceptance( (Double_t)accepted_events[idx_trial]/events_per_trial );
        acceptance_rel_diff[idx_trial] = (acceptance[idx_trial] - analytical_acceptance) / analytical_acceptance;
        std::cout<<"\n\nAccepted "<<accepted_events[idx_trial]<<" events over "<<events_per_trial<<std::endl;
        std::cout<<"Acceptance: "<<acceptance[idx_trial]<<" m^2sr"<<std::endl;
        std::cout<<"Acceptance relatice difference: "<<acceptance_rel_diff[idx_trial]<<std::endl;

        output_log_file << "\n\nAccepted "<<accepted_events[idx_trial]<<" events over "<<events_per_trial<<std::endl;
        output_log_file << "Acceptance: "<<acceptance[idx_trial]<<" m^2sr"<<std::endl;
        output_log_file << "Acceptance relatice difference: "<<acceptance_rel_diff[idx_trial]<<std::endl;
        
        hacc.Fill(acceptance[idx_trial]);
        haccreldiff.Fill(acceptance_rel_diff[idx_trial]);
    }

    ///////////////////// Computing final histos /////////////////////
    
    pcostheta_phi_acceptance->Divide(pcostheta_phi_all);
    costheta_phi_acceptance.Scale(TMath::Power(Ldet,2));
    
    //costheta_phi_inside->Scale(TMath::Power(Lgen,2));
    
    for (Int_t xx=1; xx<=costheta_phi_acceptance.GetNbinsX(); xx++) {
        costheta = costheta_phi_acceptance.GetXaxis()->GetBinCenter(xx);
        for (Int_t yy=1; yy<=costheta_phi_acceptance.GetNbinsY(); yy++) {
            bin_content = costheta_phi_acceptance.GetBinContent(xx, yy);
            costheta_phi_acceptance.SetBinContent(xx, yy, costheta*bin_content);
        }
    }
    
  
    /////////////////////////// Closing files and writing objects ////////////////////////
    
    TFile acceptance_results(root_out_path.c_str(),"RECREATE");
    
    hacc.Fit("gaus");
    hacc.Write();

    haccreldiff.Fit("gaus");
    haccreldiff.Write();

    costheta_phi_all.Write();
    costheta_phi_acceptance.Write();
    costheta_phi_inside.Write();
    
    costheta_sel.Write();
    phi_sel.Write();

    cos2theta_gen.Fit("pol0");
    cos2theta_gen.Write();
    
    costheta_gen.Fit("pol1");
    costheta_gen.Write();

    phi_gen.Fit("pol0");
    phi_gen.Write();
  
    Acceptance_X_Proj.Write();
    Acceptance_Y_Proj.Write();
  
    acceptance_results.Close();

    std::cout<<"\n\nSimulation Completed !\n\n";
    output_log_file << "\n\nSimulation Completed !\n\n";
  
    output_log_file.close();
    
    return 0;
  
}
