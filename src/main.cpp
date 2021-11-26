#include "Studio.h"
#include <iostream>


#include <fstream>
#include <sstream>
#include <algorithm>

#include "Action.h"

using namespace std;

Studio *backup = nullptr;

BaseAction *BuildAction(char command[500]);

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "usage: studio <config_path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
    ifstream infile(configurationFile);
    Studio studio(configurationFile);

    string line;
    int numberOfTrainers;
    while (infile) {

        getline(infile, line);
        if (line == "# Number of trainers") {
            numberOfTrainers = studio.readNumberOfTrainers(infile);
        }
        if (line == "# Traines") {
            studio.initializeTrainer(infile, numberOfTrainers);
        }

        if (line == "# Work Options") {
            studio.initializeWorkoutOption(infile);
        }
    }

    studio.start();
    if (backup != nullptr) {
        delete backup;
        backup = nullptr;
    }

    //cout << studio.getTrainer(2)->getCustomers().at(0)->getName() << endl;
    studio.getNumOfTrainers();
//    string option;
//    Trainer tmpTrainer = *studio.getTrainer(0);

    //  cout << studio.getWorkoutOptions().at(0).getType();
//    Customer S




//        cin >> option;
//        while (option != "closeall") {
//            cin >> option;
//                studio.getNumOfTrainers();
//
//            }
//    cout << "closing" << '\n';




    return 0;
}





