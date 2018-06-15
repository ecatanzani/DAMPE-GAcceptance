
#include "MyHead.h"

void create_and_initialize_log(std::ofstream &log_file) {
    if(!log_file.is_open()) {
        std::cout<<"\n\nCannot create output log file! Program finished !"<<std::endl;
        exit(-2);
    }
    log_file_init(log_file);
}


std::string output_path_creator(const Int_t out_choose) {
    // out_choose == 0 means we are creating the path for a log file
    // out_choose == 0 means we are creating the path for a ROOT output file
    
    std::string output;
    
    switch(out_choose) {
            
        case 0:
            output = output_log;
            output+=std::to_string((long long)time_stamp);
            output+=".txt";
            std::cout<<"\nWritten log file: -> \t "<<output<<std::endl;
            break;
            
        case 1:
            output = output_root;
            output+=std::to_string((long long)time_stamp);
            output+="_maps_result.root";
            std::cout<<"\nWritten ROOT file: -> \t "<<output<<std::endl;
            break;
            
    }
    
    return output;
}


void log_file_init(std::ofstream &out_file) {
    out_file << "********************* Automatic Log File Generator *******************"<<std::endl<<std::endl;
  
    out_file << "////////////////////////// Simulation Parameters //////////////////////////"<<std::endl<<std::endl;
    out_file << "Simulation timestamp: "<<time_stamp<<std::endl;
    out_file << "Simulation TRandom3 seed: "<<trandom3_seed<<std::endl;
    out_file << "Number of trials: "<<trials_number<<std::endl;
    out_file << "Number of events per trial: "<<events_per_trial<<std::endl<<std::endl;
  
    out_file << "////////////////////////// Detector Parameters //////////////////////////"<<std::endl<<std::endl;
    out_file << "Generation plane (in meters): "<<Lgen<<std::endl;
    out_file << "Detector lenght (in meters): "<<Ldet<<std::endl;
    out_file << "Detector high (in meters): "<<Hdet<<std::endl;
    out_file << "Number of checked layers for geometrical acceptace computing: "<<n_checked_detectors<<std::endl;

    out_file << "*\n*\n*\n"<<std::endl<<std::endl;
}
