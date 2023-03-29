using namespace std;
#include <ctime>
#include <string>

#include "workout.h"

workout::workout() {}

string workout::getName() const {
    return name;
}

bool workout::getInvalid() const {
    return invalid;
}

string workout::getCompletionDate() const {
    return completionDate;
}