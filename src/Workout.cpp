#include "Workout.h"


//destructor
//       copy constructor
//        move constructor

//        move assignment operator
Workout::Workout(int w_id,
                 std::string w_name,
                 int w_price,
                 WorkoutType w_type)
                 :id(w_id),name(w_name),price(w_price),type(w_type){}


//        copy assignment operator
//Workout &Workout::operator=(const Workout &other) {
//    if (this != &other){
//        this->id(other.id)
//
//    }
//
//    return *this;
//}

// Destructor
//Workout::~Workout() { clear(); }
//
//void Workout::clear()
//{
//    if (cstring)
//    {
//        delete[] cstring; // deallocate
//        cstring = nullptr;
//        cstringlen = 0;
//    }
//}


int Workout::getId() const {
    return id;
}
std::string Workout::getName() const {
    return name;
}

int Workout::getPrice() const {
    return  price;
}

WorkoutType Workout::getType() const {
    return type;// return num of enum! should return a string?
}

//void Workout::copy(const int &other_id, const std::string &other_name, const int &other_price,const WorkoutType &other_type){
//    id = other_id;
//    name = other_name;
//    price = other_price;
//    type = other_type;
////    cstring = new char[cstringlen + 1]; // allocate
////    strcpy_s(cstring, cstringlen + 1, other_cstring); // populate
//}

//Workout::~charArray() { clear(); }
//
//void charArray::clear()
//{
//    if (cstring)
//    {
//        delete[] cstring; // deallocate
//        cstring = nullptr;
//        cstringlen = 0;
//    }
//}




