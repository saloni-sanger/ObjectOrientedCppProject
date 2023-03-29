#include <string>
#include "sessionLog.h"
#include "workout.h"
#include "fitSet.h"
#include "triWorkout.h"
#include "hiit.h"
using namespace std;

sessionLog::sessionLog() {}

sessionLog::~sessionLog() {
    for(int i=0; i<numWorkouts; i++) {
        delete log[i];
    }
    delete log;
}

void sessionLog::addWorkout(workout* entry) {
    if(workoutCompleted == false) {
        numWorkouts++; 
        workout** temp = new workout*[numWorkouts];
        for (int i=0; i< numWorkouts-1; i++) {
            temp[i] = log[i];
        }

        delete[] log; //frees array, not objects

        temp[numWorkouts-1] = entry;

        log = temp; 
    }
    return;
}

void sessionLog::removeWorkout(unsigned int exerciseNum) {
    if (workoutCompleted == false) {
        if (numWorkouts == 1) {
            workout** temp = nullptr;

            for(int i=0; i<numWorkouts; i++) {
                delete log[i];
            }
            delete log;

            log = temp;
            numWorkouts--;
            return;
        }
        exerciseNum--; 
        workout** temp = new workout*[numWorkouts-1];
        for (unsigned int i =0; i<exerciseNum; i++) {
            temp[i] = log[i]; 
        }
        for (int i =exerciseNum+1; i<numWorkouts; i++) {
            temp[i-1] = log[i];
        }
        delete[] log;
        log = temp; 
        numWorkouts--;
    }
    return;    
} 

void sessionLog::justDoIt(int exerciseNum, int completedWeight, int completedReps) {
    if (workoutCompleted == false) {
        if(enforceSameDate(exerciseNum)) {
            exerciseNum--; 
            workout* w = log[exerciseNum];
            fitSet* f = (fitSet*) w;
            f->setPerformedWeight(completedWeight); 
            f->setPerformedReps(completedReps);

            workoutCompleted = checkCompletion();
        }
    }
    return;
}

void sessionLog::justDoIt(int exerciseNum, double completedTime, double completedDistance) {
    if (workoutCompleted == false) {
        if(enforceSameDate(exerciseNum)) {
            exerciseNum--; 
            workout* w = log[exerciseNum];
            triWorkout* t = (triWorkout*) w;
            t->setPerformedTime(completedTime); 
            t->setPerformedDistance(completedDistance);

            workoutCompleted = checkCompletion();
        }
    }
    return;
}

void sessionLog::justDoIt(int exerciseNum, double completedReps, double completedRest, double completedTime) {
    if (workoutCompleted == false) {
        if(enforceSameDate(exerciseNum)) {
            exerciseNum--; 
            workout* w = log[exerciseNum];
            hiit* h = (hiit*) w;
            h->setPerformedTime(completedTime);
            h->setPerformedRest(completedRest);
            h->setPerformedReps(completedReps);
            workoutCompleted = checkCompletion();
        }
    }
    return;
}

bool sessionLog::enforceSameDate(int exerciseNum) {
    exerciseNum--;
    if (exerciseNum == 0) {
        return true;
    } else {
        string date_stupid = log[exerciseNum]->getCompletionDate();
        time_t t = time(0);
        tm* now = localtime(&t);
        string today = to_string(now->tm_year + 1900) + "-" + to_string(now->tm_mon +1) + "-" + to_string(now->tm_mday); 
        //today holds current date in format "year-month-day"
        if (log[exerciseNum-1]->getCompletionDate() == today) {
            return true;
        } else {
            return false;
        }
    }
}

bool sessionLog::checkCompletion() {
    int completed = 0;
    for(int i=0; i<numWorkouts; i++) {
        if (log[i]->isComplete()) {
            completed++;
        }
    }
    if (completed == numWorkouts) { 
        return true;
    } else {
        return false;
    }
}

void sessionLog::buildSession(vector<workout*> entries, unsigned int numEntries) {
    if(workoutCompleted == false) { 
        for(unsigned int i=0; i< numEntries; i++) { 
            addWorkout(entries[i]); 
        }
    }
    return;
}

void sessionLog::buildSession(sessionLog& source) {
    if(workoutCompleted == false) { 
        for(int i=0; i<numWorkouts; i++) {
            delete log[i];
        }
        delete[] log;

        numWorkouts = source.numWorkouts;
        log = new workout*[numWorkouts];

        for (int i =0; i<numWorkouts; i++) {
            workout* w = source.log[i];

            if(w->getType() == "fitSet") {
                fitSet* f = (fitSet*) w; //f is the fitSet in source.log[i]
                fitSet* input = new fitSet(f->getName(), f->getClassification(), f->getWeight(), f->getTargetReps());
                log[i] = input;
            } else if(w->getType() == "triWorkout") {
                triWorkout* t = (triWorkout*) w;
                triWorkout* input = new triWorkout(t->getName(), t->getTimeGoal(), t->getDistanceGoal());
                log[i] = input;
            } else if(w->getType() == "hiit") {
                hiit* h = (hiit*) w;
                hiit* input = new hiit(h->getName(), h->getRepGoal(), h->getTimeGoal(), h->getRestGoal());
                log[i] = input;
            }
        }
    }
    return;
}

string sessionLog::shareSession() {
    string returnValue = "";
    for (int i =0; i<numWorkouts; i++) {
        workout* w = log[i];

        if(w->getType() == "fitSet") {
            fitSet* f = (fitSet*) w; //f is the fitSet in log[i]
            returnValue += f->getName();
            returnValue += "\tGoal Weight: ";
            returnValue += to_string(f->getWeight());
            returnValue += "\tGoal Reps: ";
            returnValue += to_string(f->getTargetReps());
            if (f->isComplete())
            {
                returnValue += "\tPerformed Weight: ";
                returnValue += to_string(f->getPerformedWeight());
                returnValue += "\tPerformed Reps: ";
                returnValue += to_string(f->getPerformedReps());
            }
        } else if(w->getType() == "triWorkout") {
            triWorkout* t = (triWorkout*) w;
            returnValue += t->getName();
            returnValue += "\tGoal Time: ";
            returnValue += to_string(t->getTimeGoal());
            returnValue += "\tGoal Distance: ";
            returnValue += to_string(t->getDistanceGoal());
            if (t->isComplete())
            {
                returnValue += "\tPerformed Time: ";
                returnValue += to_string(t->getPerformedTime());
                returnValue += "\tPerformed Distance: ";
                returnValue += to_string(t->getPerformedDistance());
            }
        } else if(w->getType() == "hiit") {
            hiit* h = (hiit*) w;
            returnValue += h->getName();
            returnValue += "\tGoal Reps: ";
            returnValue += to_string(h->getRepGoal());
            returnValue += "\tGoal Time: ";
            returnValue += to_string(h->getTimeGoal());
            returnValue += "\tGoal Rest: ";
            returnValue += to_string(h->getRestGoal());
            if (h->isComplete())
            {
                returnValue += "\tPerformed Reps: ";
                returnValue += to_string(h->getPerformedReps());
                returnValue += "\tPerformed Time: ";
                returnValue += to_string(h->getPerformedTime());
                returnValue += "\tPerformed Rest: ";
                returnValue += to_string(h->getPerformedRest());

            }
        }
        returnValue += "\n";
    }
    return returnValue;
}

sessionLog::sessionLog(const sessionLog& source) {
    for (int i=0; i<source.numWorkouts; i++) {
        addWorkout(source.log[i]->clone()); 
    }
    workoutCompleted = source.workoutCompleted;
}

sessionLog& sessionLog::operator=(const sessionLog& source) {
    if(this != &source) { 
        for(int i=0; i<numWorkouts; i++) {
            delete log[i];
        }
        delete log;
        numWorkouts = source.numWorkouts;
        workout** temp = new workout*[numWorkouts];
        for (int i=0; i< numWorkouts; i++) {
            temp[i] = source.log[i]->clone(); 
        }
        log = temp;
    }
    return *this;
}

sessionLog sessionLog::operator+(const sessionLog& source) const {
    sessionLog returnValue(*this);
    if(workoutCompleted == false && source.workoutCompleted == false) {
        for (int i=0; i< source.numWorkouts; i++) {
            returnValue.addWorkout(source.log[i]->clone()); 
        }
    }
    return returnValue;
}

sessionLog sessionLog::operator+(int value) const {
    sessionLog returnValue(*this);
    if (workoutCompleted == false) {
        for (int i=0; i<numWorkouts; i++) {
            returnValue.log[i]->operator+=(value); 
        }
    }
    return returnValue;
}

sessionLog sessionLog::operator-(int value) const {
    sessionLog returnValue(*this);
    if (workoutCompleted == false) {
        for (int i=0; i<numWorkouts; i++) {
            returnValue.log[i]->operator-=(value); 
        }
    }
    return returnValue;
}

sessionLog& sessionLog::operator+=(workout* entry) {
    if (workoutCompleted == false) {
        addWorkout(entry);
    }
    return *this;
}

sessionLog& sessionLog::operator-=(int exerciseNum) {
    if (workoutCompleted == false) {
        removeWorkout(exerciseNum);
    }
    return *this;
}

bool sessionLog::operator==(const sessionLog& source) const { 
    if (workoutCompleted != source.workoutCompleted || numWorkouts != source.numWorkouts) { //check numWorkouts and workoutCompleted
        return false;
    }

    for (int i=0; i<numWorkouts; i++) { //check types of each workout
        workout* a = log[i];
        workout* b = source.log[i];
        if(a->getType() == "fitSet" && b->getType() != "fitSet") {
            return false;
        } else if(a->getType() == "hiit" && b->getType() != "hiit") {
            return false;
        } else if(a->getType() == "triWorkout" && b->getType() != "triWorkout") {
            return false;
        }
    }

    for(int i=0; i<numWorkouts; i++) { //check values of each workout, everything must be the same except completionDate
                                        //and invalid status
        workout* c = log[i];
        workout* d = source.log[i];
        if(c->getType() == "fitSet") { //can assume the types are equal now
            fitSet* a = (fitSet*) c;
            fitSet* b = (fitSet*) d;
            if(a->getName() != b->getName() || a->getClassification() != b->getClassification()
              || a->getWeight() != b->getWeight() || a->getTargetReps() != b->getTargetReps()
              || a->getPerformedReps() != b->getPerformedReps() || a->getPerformedWeight() != b->getPerformedWeight()) {
                return false;
            }
        } else if(c->getType() == "hiit") {
            hiit* a = (hiit*) c;
            hiit* b = (hiit*) d;
            if(a->getName() != b->getName() || a->getRepGoal() != b->getRepGoal()
              || a->getTimeGoal() != b->getTimeGoal() || a->getRestGoal() != b->getRestGoal()
              || a->getPerformedTime() != b->getPerformedTime() || a->getPerformedReps() != b->getPerformedReps()
              || a->getPerformedRest() != b->getPerformedRest()) {
                return false;
            }
        } else if(c->getType() == "triWorkout") {
            triWorkout* a = (triWorkout*) c;
            triWorkout* b = (triWorkout*) d;
            if(a->getName() != b->getName() || a->getTimeGoal() != b->getTimeGoal()
              || a->getDistanceGoal() != b->getDistanceGoal() || a->getPerformedTime() != b->getPerformedTime()
              || a->getPerformedDistance() != b->getPerformedDistance()) {
                return false;
            }
        }
    }

    return true;
}

bool sessionLog::operator!=(const sessionLog& source) const {
    return !operator==(source);
}

bool sessionLog::operator<(const sessionLog& source) const { //returns if this has less workouts than source
    if (numWorkouts < source.numWorkouts) {
        return true;
    } else {
        return false;
    }
}

bool sessionLog::operator>(const sessionLog& source) const {
    if(numWorkouts > source.numWorkouts) {
        return true;
    } else {
        return false;
    }
}

ostream& operator<<(ostream& out, const sessionLog& source) {
    out << source.numWorkouts << "\n";
    for (int i=0; i<source.numWorkouts; i++) {
        workout* w = source.log[i];
        if (w->getType() == "fitSet") {
            fitSet* f = (fitSet*) w;
            out << "FitSet " << f->getName() << " " << f->getClassification() << " " << f->getWeight() << " " << f->getTargetReps() << "\n";
        } else if (w->getType() == "hiit") {
            hiit* h = (hiit*) w;
            out << "HIIT " << h->getName() << " " << h->getRepGoal() << " " << h->getTimeGoal() << " " << h->getRestGoal() << "\n";
        } else if (w->getType() == "triWorkout") {
            triWorkout* t = (triWorkout*) w;
            out << "TriWorkout " << t->getName() << " " << t->getTimeGoal() << " " << t->getDistanceGoal() << "\n";
        } 
    }
    return out;
}

istream& operator>>(istream& in, sessionLog& source) {
    for(int i=0; i<source.numWorkouts; i++) {
        delete source.log[i];
    }
    delete source.log;

    int numEntries = -1;
    in >> numEntries;
    string type = "";
    for (int i=0; i<numEntries; i++) {
        type = "";
        in >> type;
        if (type == "FitSet") {
            string name = "";
            string category = "";
            int weight = -1;
            int reps = -1;
            in >> name;
            in >> category;
            in >> weight;
            in >> reps;
            fitSet* f = new fitSet(name, category, weight, reps);
            source.addWorkout(f);
        } else if (type == "HIIT") {
            string name = "";
            double reps = -1.0;
            double time = -1.0;
            double rest = -1.0;
            in >> name;
            in >> reps;
            in >> time;
            in >> rest;
            hiit* h = new hiit(name, reps, time, rest);
            source.addWorkout(h);
        } else if (type == "TriWorkout") {
            string name = "";
            double time = -1.0;
            double distance = -1.0;
            in >> name;
            in >> time;
            in >> distance;
            triWorkout* t = new triWorkout(name, time, distance);
            source.addWorkout(t); 
        }
    }

    return in;
}

