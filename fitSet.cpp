using namespace std;
#include <ctime>
#include <string>

#include "fitSet.h"

fitSet::fitSet() {}

fitSet::fitSet(string name, string classification, int weight, int targetReps) {
    this->name = name;
    this->classification = classification;
    this->weight = weight;
    this->targetReps = targetReps;
}

string fitSet::getClassification() const {
    return classification;
}

int fitSet::getWeight() const {
    return weight;
}

int fitSet::getTargetReps() const {
    return targetReps;
}

int fitSet::getPerformedReps() const {
    return performedReps;
}

int fitSet::getPerformedWeight() const {
    return performedWeight;
}

double fitSet::percentOfGoal() const {
    return ( ((performedReps * 1.0) / (targetReps * 1.0)) * 100);
}

double fitSet::score() const {
    return ( performedReps + performedWeight );
}

void fitSet::setPerformedReps(int performedReps) {
    if (repsChanged == true) {
        invalid = true;
    }
    this->performedReps = performedReps; 
    repsChanged = true; 
    time_t t = time(0);
    tm* now = localtime(&t);
    completionDate = to_string(now->tm_year + 1900) + "-" + to_string(now->tm_mon +1) + "-" + to_string(now->tm_mday); 
    //date is set when user reports completion
    //"year-month-day"
} 

void fitSet::setPerformedWeight(int performedWeight) {
    if (weightChanged == true) {
        invalid = true;
    }
    this->performedWeight = performedWeight; 
    weightChanged = true;
}

bool fitSet::isComplete() const {
    if (repsChanged && weightChanged) {
        return true;
    }
    else {
        return false;
    }
}

string fitSet::getType() const {
    return "fitSet";
}

workout* fitSet::clone() const {
    return new fitSet(*this);
}

workout* fitSet::operator+=(const int num) {
    weight += num;
    targetReps += num;
    return this;
}

workout* fitSet::operator-=(const int num) {
    return operator+=(-num);
}