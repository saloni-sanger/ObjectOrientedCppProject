using namespace std;
#include <ctime>
#include <string>

#include "hiit.h"

hiit::hiit() {}

hiit::hiit(string name, double repGoal, double timeGoal, double restGoal) {
    this->name = name;
    this->repGoal = repGoal;
    this->timeGoal = timeGoal;
    this->restGoal = restGoal;
}

double hiit::getRepGoal() const {
    return repGoal;
}

double hiit::getTimeGoal() const {
    return timeGoal;
}

double hiit::getRestGoal() const {
    return restGoal;
}

double hiit::getPerformedTime() const {
    return performedTime;
}

double hiit::getPerformedRest() const {
    return performedRest;
}

double hiit::getPerformedReps() const {
    return performedReps;
}

double hiit::percentOfGoal() const {
    return ((performedReps + performedTime + performedRest) / (repGoal + timeGoal + restGoal)) * 100;
}

double hiit::score() const {
    return (performedReps + performedTime - (performedRest/10) );
}

void hiit::setPerformedReps(double performedReps) {
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

void hiit::setPerformedTime(double performedTime) {
    if (timeChanged == true) {
        invalid = true;
    }
    this->performedTime = performedTime;
    timeChanged = true;
}

void hiit::setPerformedRest(double performedRest) {
    if (restChanged == true) {
        invalid = true;
    }
    this->performedRest = performedRest;
    restChanged = true;
}

bool hiit::isComplete() const {
    if (timeChanged && restChanged && repsChanged) {
        return true;
    }
    else {
        return false;
    }
}

string hiit::getType() const {
    return "hiit";
}

workout* hiit::clone() const {
    return new hiit(*this);
}

workout* hiit::operator+=(const int num) {
    repGoal += num;
    timeGoal += num;
    restGoal += num;
    return this;
}

workout* hiit::operator-=(const int num) {
    return operator+=(-num);
}