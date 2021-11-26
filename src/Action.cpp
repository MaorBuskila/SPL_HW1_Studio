
#include <Action.h>
#include <Studio.h>
extern Studio* backup;

BaseAction::BaseAction() {
}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = COMPLETED;
}

void BaseAction::error(std::string errorMsg) {
    status = ERROR;
    this->errorMsg = errorMsg;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id) {
    customers = customersList;

}

void OpenTrainer::act(Studio &studio) {

    if (trainerId >= studio.getNumOfTrainers() || trainerId < 0) {
        this->error("Workout session does not exit or is already open");
    }
    else {


        Trainer *trainer = studio.getTrainer(trainerId);
        int trainerCap = trainer->getCapacity();
        trainer->openTrainer();
        if (trainerCap < customers.size()) {
            for (int i = 0; i < trainer->getCapacity(); i++)
                trainer->addCustomer(customers.at(i));
            for (int j = trainerCap; j < customers.size(); j++)
                delete customers.at(j);
        } else
            for (int i = 0; i < customers.size(); i++) {

                trainer->addCustomer(customers.at(i));
            }
        this->complete();

    }
}

std::string OpenTrainer::toString() const {

    std::string line= cIn;
    if(this->getStatus()==COMPLETED)
        line+= " Completed";
    else
        line+= " Error: " + getErrorMsg();
    return line;
}


Order::Order(int id) : trainerId(id) {
}

void Order::act(Studio &studio) {
    if(trainerId >= studio.getNumOfTrainers() || !studio.getTrainer(trainerId)->isOpen()){
        this->error("Trainer does not exist or is not open");
        return;
    }
    std::vector<int> desiredWorkout;
    for (int i = 0; i < studio.getTrainer(trainerId)->getCustomers().size(); i++) {
        desiredWorkout = studio.getTrainer(trainerId)->getCustomers().at(i)->order(studio.getWorkoutOptions());
        studio.getTrainer(trainerId)->order(studio.getTrainer(trainerId)->getCustomers().at(i)->getId(), desiredWorkout,
                                            studio.getWorkoutOptions());
    }
    for (int i = 0; i < studio.getTrainer(trainerId)->getOrders().size(); i++) {
        std::cout << studio.getTrainer(trainerId)->getCustomer(
                studio.getTrainer(trainerId)->getOrders().at(i).first)->getName() << " is doing "
                  << studio.getTrainer(trainerId)->getOrders().at(i).second.getName() << std::endl;
    }
    this->complete();

}
std::string Order::toString() const {
    std::string line=cIn;
    if(this->getStatus()==COMPLETED)
        line+= " Completed";
    else
    {
        line+= " Error: " + getErrorMsg();

    }
    return line;

}

MoveCustomer::MoveCustomer(int src, int dst, int customerId) :
        srcTrainer(src), dstTrainer(dst), id(customerId) {

}

void MoveCustomer::act(Studio &studio) {

    if (srcTrainer > studio.getNumOfTrainers() || dstTrainer > studio.getNumOfTrainers()
        || !studio.getTrainer(srcTrainer)->isOpen() || !studio.getTrainer(dstTrainer)->isOpen()
        || studio.getTrainer(srcTrainer)->getCustomers().size() < id
        || studio.getTrainer(dstTrainer)->getCapacity() == studio.getTrainer(dstTrainer)->getCustomers().size()) {


        this->error("Cannot move customer");
        return;
    }

    Customer *tmpCustomer = studio.getTrainer(srcTrainer)->getCustomer(id);
    studio.getTrainer(srcTrainer)->removeCustomer(id);
    studio.getTrainer(dstTrainer)->addCustomer(tmpCustomer);
    for (auto i = studio.getTrainer(srcTrainer)->getCustomers().begin();
         i < studio.getTrainer(srcTrainer)->getCustomers().end(); i++) {
        if (i[0]->getId() == id) {
        }
    }
    std::vector<OrderPair> tmp;
    for (int i = 0; i < studio.getTrainer(srcTrainer)->getOrders().size(); i++) {
        if (studio.getTrainer(srcTrainer)->getOrders()[i].first == id) {
            studio.getTrainer(dstTrainer)->addOrder(id, studio.getTrainer(srcTrainer)->getOrders()[i].second);
        } else {
            tmp.push_back(studio.getTrainer(srcTrainer)->getOrders()[i]);
        }
    }
    studio.getTrainer(srcTrainer)->deleteAndUpdateOrder(tmp);
    this->complete();
}
std::string MoveCustomer::toString() const {
    std::string line=cIn;
    if(this->getStatus()==COMPLETED)
        line+= " Completed";
    else
    {
        line+= " Error: "+getErrorMsg();
    }
    return line;
}

Close::Close(int id) : trainerId(id) {}

void Close::act(Studio &studio) {
    //Change trainer open to false
    if (trainerId > studio.getNumOfTrainers() || !studio.getTrainer(trainerId)->isOpen()) {
        this->error("Trainer does not exist or is not open");
        return;
    }
    std::cout << "Trainer " << trainerId << " closed. Salary " << studio.getTrainer(trainerId)->getSalary() << "NIS"
              << std::endl;
    this->complete();
    studio.getTrainer(trainerId)->closeTrainer();
}
std::string Close::toString() const {
    std::string line=cIn;
    if(this->getStatus()==COMPLETED)
        line+= " Completed";
    else
        line+= " Error: "+getErrorMsg();
    return line;
}


CloseAll::CloseAll() {};

void CloseAll::act(Studio &studio) {

    for (int i = 0; i < studio.getNumOfTrainers(); i++) {
        if (studio.getTrainer(i)->isOpen()) {
            Close a = Close(i);
            a.act(studio);
        }

    }
    this->complete();
}
std::string CloseAll::toString() const {
    std::string line="closeall Completed";
    return line;


}

PrintWorkoutOptions::PrintWorkoutOptions() {

}

void PrintWorkoutOptions::act(Studio &studio) {

    for (int i = 0;
         i < studio.getWorkoutOptions().size(); i++)    /// return to me Workout Vector that include id name price type
    {
        std::cout << studio.getWorkoutOptions().at(i).getName() << ", " << studio.getWorkoutOptions().at(i).getType() <<
                  ", " << studio.getWorkoutOptions().at(i).getPrice() << std::endl;
    }
    this->complete();
}
std::string PrintWorkoutOptions::toString() const {
    return "PrintWorkOutOptions Completed";
}

PrintActionsLog::PrintActionsLog() {

}

void PrintActionsLog::act(Studio &studio) {


    for (int k = 0; k < studio.getActionsLog().size()-1; k++) {
    std::cout << studio.getActionsLog().at(k)->toString() << std::endl;
    }

}
std::string PrintActionsLog::toString() const {

    return "PrintActionsLog Completed";
}



PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id) {

}

void PrintTrainerStatus::act(Studio &studio) {
    if (studio.getTrainer(trainerId)->isOpen()) {
        std::cout << "Trainer " << trainerId << " status: open" << std::endl;
        std::cout << "Customers:" << std::endl;
        for (int i = 0; i < studio.getTrainer(trainerId)->getCustomers().size(); i++) {
            std::cout << studio.getTrainer(trainerId)->getCustomers().at(i)->getId() << " " <<
                      studio.getTrainer(trainerId)->getCustomers().at(i)->getName() << std::endl;
        }
        for (int k = 0; k < studio.getTrainer(trainerId)->getOrders().size(); k++) {
            std::cout << studio.getTrainer(trainerId)->getOrders().at(k).second.getName() << " " <<
                      studio.getTrainer(trainerId)->getOrders().at(k).second.getPrice() << "NIS "
                      << studio.getTrainer(trainerId)->getOrders().at(k).first << std::endl;

        }
        std::cout << "Current Trainer's Salary: " << studio.getTrainer(trainerId)->getSalary() << "NIS" << std::endl;


    }
     else
        std::cout << "Trainer " << trainerId << " status: closed" << std::endl;

}
std::string PrintTrainerStatus::toString() const {
    return "PrintTrainerStatus Completed";;
}

BackupStudio::BackupStudio() {

}
void BackupStudio::act(Studio& studio) {

    if(backup== nullptr) {
        backup = new Studio(studio);
    }
    else {
        delete backup;
        backup = nullptr;
        backup = new Studio(studio);
    }
    complete();
}
std::string BackupStudio::toString() const {
    return "nrewa";
}
RestoreStudio::RestoreStudio() {}
void RestoreStudio ::act(Studio &studio){
    if (backup == nullptr){
        error("No backup available");
    }
    else{
        studio = *backup;
        complete();
    }
}

std::string RestoreStudio::toString() const {
    return "nrewa";
}

void BaseAction::deleteSpace(std::string line) {
    while (line[0] == ' ') {
        line.erase(0);
    }
}

void BaseAction::Setc_IN(std::string line) {

    cIn = line;
}

std::string BaseAction::getc_IN() {
    return cIn;
}
