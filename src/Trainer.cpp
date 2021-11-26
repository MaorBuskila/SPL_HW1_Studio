#include "Trainer.h"
#include "Customer.h"
#include "Action.h"
#include <algorithm>
#include <iostream>

//move co
//copy assignment operator
//move assignment operator
//destructor

//copy constructor
Trainer::Trainer(const Trainer &other) : capacity(other.capacity), open(other.open) {
//    open = other.open;
//    capacity = other.capacity;
}

// auto generated , need to check
Trainer::Trainer(Trainer *pTrainer) {

}

//Trainer constructor
Trainer::Trainer(int t_capacity) {
    this->capacity = t_capacity;
}

int Trainer::getCapacity() const {
    return capacity;
}

void Trainer::addCustomer(Customer *customer) {
    this->customersList.push_back(customer); //should be new or not?
}

void Trainer::removeCustomer(int id) {
    for (int i = 0; i < customersList.size(); i++) {
        if (customersList[i]->getId() == id)
            customersList.erase(customersList.begin() + i);
    }
}

std::vector<Customer *> &Trainer::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Trainer::getOrders() {
    return orderList;
}

void
Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for (auto i = workout_ids.begin(); i < workout_ids.end(); i++) {
        for (auto j = workout_options.begin(); j < workout_options.end(); j++) {
            if (i[0] == j->getId())
                orderList.push_back(OrderPair(customer_id, j[0]));
        }
    }
}

void Trainer::openTrainer() {
    if (!open) {
        open = true;
    } else {
        std::cout << "Trainer already opened" << std::endl;
    }
}

void Trainer::closeTrainer() {
    if (open)
        open = false;
    customersList.clear();
    orderList.clear();
}

int Trainer::getSalary() {
    int sum = 0;
    for (int i = 0; i < orderList.size(); i++) {
        sum += (orderList.at(i).second.getPrice());
    }
    return sum;
}

bool Trainer::isOpen() {
    if (open)
        return true;
    else
        return false;
}

void Trainer::addOrder(int id, Workout workout) {
    orderList.push_back(OrderPair(id, workout));
}

Customer *Trainer::getCustomer(int id) {
    return customersList.at((id));
}

void Trainer::deleteAndUpdateOrder(std::vector<OrderPair> tmp) {
    orderList.clear();
    for (int i = 0; i < tmp.size(); i++) {
        this->addOrder(tmp[i].first, tmp[i].second);
    }
}







