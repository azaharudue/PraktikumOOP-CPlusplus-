#include "train.h"
#include <iostream>

Train::Train(const std::string trainNum, 
             const std::string destination, 
             const std::string over)
            : no(trainNum), to(destination), over(over) {}

Train::~Train() {
    std::cout << "Train " << no << " to " << to << " deleted" << std::endl;
}

const std::string Train::GetTrainNumber() {
    return no;
}

const std::string Train::GetDestination() {
    return to;
}

const std::string Train::GetOver() {
    return over;
}

