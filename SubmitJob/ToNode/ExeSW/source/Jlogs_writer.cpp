
#include "MyJHead.h"

string output_path_creator(const Int_t out_choose) {
  // out_choose == 0 means we are creating the path for a log file
  // out_choose == 0 means we are creating the path for a ROOT output file

  string output;
  
  switch(out_choose) {

  case 0:
    output = output_log;
    output+=to_string((long long)time_stamp);
    output+=".txt";
    cout<<"\nWritten log file: -> \t "<<output<<endl;
    break;

  case 1:
    output = output_root;
    output+=to_string((long long)time_stamp);
    output+="_acceptance_result.root";
    cout<<"\nWritten ROOT file: -> \t "<<output<<endl;
    break;

  }
  
  return output;
}

void log_file_init(ofstream &out_file) {
  out_file << "********************* Automatic Log File Generator *******************"<<endl<<endl;
  
  out_file << "////////////////////////// Simulation Parameters //////////////////////////"<<endl<<endl;
  out_file << "Simulation timestamp: "<<time_stamp<<endl;
  out_file << "Simulation TRandom3 seed: "<<trandom3_seed<<endl;
  out_file << "Number of trials: "<<trials_number<<endl;
  out_file << "Number of events per trial: "<<events_per_trial<<endl<<endl;
  
  out_file << "////////////////////////// Detector Parameters //////////////////////////"<<endl<<endl;
  out_file << "Generation plane (in meters): "<<Lgen<<endl;
  out_file << "Detector lenght (in meters): "<<Ldet<<endl;
  out_file << "Detector high (in meters): "<<Hdet<<endl;
  out_file << "Number of checked layers for geometrical acceptace computing: "<<n_checked_detectors<<endl;

  out_file << "*\n*\n*\n"<<endl<<endl;
}
