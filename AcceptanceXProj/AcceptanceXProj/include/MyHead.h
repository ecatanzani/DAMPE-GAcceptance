///// Head file	///////

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <ctime>

///// ROOT libraries

#include "TFile.h"
#include "TRandom3.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"

///////////////////////////////////////

const static Int_t trials_number = 1e+4;
const static Int_t events_per_trial = 1e+6;

const static time_t time_stamp = time(0);                                     //Setting timestamp for the out files

const static Double_t Ldet = 0.026*22;                                        //Side of the square detector in meters
const static Double_t Hdet = 0.026*14;                                        //Height of the square detector in meters

const static Double_t h_layer = -Hdet/2;

const static Double_t phi_min = 0;
const static Double_t phi_max = 2*TMath::Pi();
const static Double_t cos2_theta_min = 0;
const static Double_t cos2_theta_max = 1;

const static UInt_t trandom3_seed = 9;

//////////////////////////// Outh paths for logs and ROOT files:

const static std::string output_log = "/Users/enrico/Documents/Università/Magistrale/Tesi/MyCode/MyRepos/GitHub/Stuff/DAMPE-GAcceptance/logs/";
const static std::string output_root = "/Users/enrico/Documents/Università/Magistrale/Tesi/MyCode/MyRepos/GitHub/Stuff/DAMPE-GAcceptance/results/";

//////////////////////////////////////////////////////////////////////////////////


////////////////// Stuff functions //////////////////

extern std::string output_path_creator(const Int_t out_choose);
extern void create_and_initialize_log(std::ofstream &log_file);
extern void log_file_init(std::ofstream &out_file);

//////////////// Analysis functions /////////////////

extern void generate_coordinate(Double_t X[],TRandom3 &r_gen);
extern void generate_theta_phi(Double_t &theta,Double_t &phi,TRandom3 &r_gen,TH1D &cos2theta_gen);
extern void obtain_direction(Double_t theta,Double_t phi,Double_t dir[]);
extern void check_acceptance(Double_t X[],Double_t dir[],Double_t theta,Bool_t &accepted_event);
extern void propagate(Double_t X[],Double_t dir[],Double_t theta,Double_t X_detector[],const Double_t h_layer);
extern Double_t Get_Telescope_Analysical_Acceptance(Double_t _l, Double_t _a1, Double_t _b1, Double_t _a2, Double_t _b2);
extern Double_t Get_Acceptance(Double_t ratio);
