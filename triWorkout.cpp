using namespace std;
#include <ctime>
#include <string>
#include <stdexcept>

#include "triWorkout.h"

triWorkout::triWorkout() {}

triWorkout::triWorkout(string name, double timeGoal, double distanceGoal) {
    if (name == "running" || name == "cycling" || name == "swimming") {
        this->name = name;
        this->timeGoal = timeGoal;
        this->distanceGoal = distanceGoal;
    } else {
        throw invalid_argument("incorrect name");
    }
}

double triWorkout::getTimeGoal() const {
    return timeGoal;
}

double triWorkout::getDistanceGoal() const {
    return distanceGoal;
}

double triWorkout::getPerformedTime() const {
    return performedTime;
}

double triWorkout::getPerformedDistance() const {
    return performedDistance;
}

double triWorkout::pace() const {
    if (name == "running") {
        return performedTime / performedDistance;
    } if (name == "swimming"){
        return performedTime / (performedDistance / 100);
    }
    else { //cycling
        return performedDistance / performedTime;
    }
}

double triWorkout::percentOfGoal() const {
    if (name == "running") {
        return (((timeGoal / distanceGoal) / pace()) * 100); 
    } if (name == "swimming"){
        return (((timeGoal / distanceGoal) / (pace() / 100)) * 100);
    }
    else { //cycling
        return ((pace() / (distanceGoal / timeGoal)) * 100); 
    }
}

double triWorkout::score() const {
    return (performedTime + performedDistance + pace());
}

void triWorkout::setPerformedTime(double performedTime) {
    if (timeChanged == true) {
        invalid = true;
    }
    this->performedTime = performedTime;
    timeChanged = true;
    time_t t = time(0);
    tm* now = localtime(&t);
    completionDate = to_string(now->tm_year + 1900) + "-" + to_string(now->tm_mon +1) + "-" + to_string(now->tm_mday); 
    //date is set when user reports completion
    //"year-month-day"
}

void triWorkout::setPerformedDistance(double performedDistance) {
    if (distanceChanged == true) {
        invalid = true;
    }
    this->performedDistance = performedDistance;
    distanceChanged = true;
}

bool triWorkout::isComplete() const {
    if (timeChanged && distanceChanged) {
        return true;
    }
    else {
        return false;
    }
}

string triWorkout::getType() const {
    return "triWorkout";
}

workout* triWorkout::clone() const {
    return new triWorkout(*this);
}

workout* triWorkout::operator+=(const int num) {
    timeGoal += num;
    distanceGoal += num;
    return this;
}

workout* triWorkout::operator-=(const int num) {
    return operator+=(-num);
}