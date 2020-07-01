#ifndef TRAIN_H
#define TRAIN_H

#include <string>

class Train {
    private:
        const std::string no;
        const std::string to;
        const std::string over;
    public:
        Train(const std::string trainNum, const std::string destination, const std::string over);
        ~Train();
        const std::string GetTrainNumber();
        const std::string GetDestination();
        const std::string GetOver();

};

#endif