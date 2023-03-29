#ifndef WORKOUT_H
#define WORKOUT_H

#include <string>

using namespace std;

/* Interface invariants:
 * name, invalid, percentOfGoal, Score, completionDate are read only.
 * Invalid is used in subtypes to declare if client input variables have been set more than once.
 * isComplete() returns if all user inputs have been set at least once (respective to subclass).
 * getType() returns the name of the subclass.
 * clone() returns bitwise copy of subtype.
 * += and -= adjust goal metrics of subtype.
 */

class workout {
    protected: //subclasses can set and get these as they wish
        string name = "";
        bool invalid = false;
        string completionDate = "";
    public:
        workout();
        virtual ~workout() = default;
        string getName() const;
        bool getInvalid() const;
        string getCompletionDate() const;
        virtual double percentOfGoal() const =0;
        virtual double score() const =0;
        virtual bool isComplete() const =0;
        virtual string getType() const =0;
        virtual workout* clone() const =0;
        virtual workout* operator+=(const int) =0;
        virtual workout* operator-=(const int) =0;
};

#endif

