#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include "sessionLog.h"
#include "workout.h"
#include "fitSet.h"
#include "triWorkout.h"
#include "hiit.h"

void combine() {
    cout << "Let's read the sessions from file session1 and session2, then combine then to file example.txt" << endl;
    ifstream session1("session1.txt");
    ifstream session2("session2.txt");
    sessionLog a;
    sessionLog b;
    session1 >> a;
    session2 >> b;
    sessionLog c = (a + b);
    ofstream outfile("example.txt");
    outfile << c << endl;
    cout << endl;
}

void increase() {
    cout << "Now we'll read a session from file session3, increase the metrics of each workout by 1, and write the updated session to the console." << endl;
    ifstream session3("session3.txt");
    sessionLog a;
    session3 >> a;
    sessionLog b;
    b = a + 1;
    cout << b;
    cout << endl;
}

void comparison() {
    cout << "Now let's read from 2 files and use the < and > operator overload to determine which session is bigger (greater number of workouts)." << endl;
    ifstream session1("session1.txt");
    ifstream session2("session2.txt");
    sessionLog a;
    sessionLog b;
    session1 >> a;
    session2 >> b;
    cout << "a has less workouts than b, so a<b should output true." << endl;
    cout << (a.operator<(b) ? "true" : "false") << endl; 
    cout << "b>a should also be true." << endl;
    cout << (b.operator>(a) ? "true" : "false") << endl; 
    cout << endl;
}

void intermission() {
    cout << "The previous tests have implemeted the overloaded >>, <<, sessionLog + sessionLog, sessionLog + int, and < comparison." << endl;
    cout << "That leaves sessionLog - int, sessionLog += workout, sessionLog -= exerciseNum, sessionLog == sessionLog, and != to be shown" << endl;
    cout << "Many of these are rather simple to show, so I'll do some fast depictions of them, any output will be to the console." << endl;
    cout << endl;
}

void decrease() {
    cout << "sessionLog - int. sessionLog taken from session3.txt and target values are decremented by 1." << endl;
    ifstream session3("session3.txt");
    sessionLog a;
    session3 >> a;
    sessionLog b;
    b = a - 1;
    cout << b;
    cout << endl;
}

void addAndRemove() {
    cout << "sessionLog += workout and sessionLog -= exerciseNum. These are just different ways to use add and remove workout." << endl;
    sessionLog a;
    fitSet* f = new fitSet("crunches", "core", 0, 20);
    triWorkout* t = new triWorkout("running", 16.0, 2.0);
    a += f;
    a += t;
    cout << a << endl;
    a -= 1;
    cout << "First exercise removed using -=." << endl;
    cout << a << endl;
}

void equalAndNot() {
    cout << "sessionLog == sessionLog, and sessionLog != sessionLog." << endl;
    sessionLog a;
    fitSet* f = new fitSet("crunches", "core", 0, 20);
    triWorkout* t = new triWorkout("running", 16.0, 2.0);
    hiit* h = new hiit("burpees", 15, 60, 60);
    a.addWorkout(f);
    a.addWorkout(t);
    a.addWorkout(h);
    sessionLog newer(a); 
    cout << "I used a copy constructor to make sure the two sessionLogs are the same. Are they?" << endl;
    cout << ((newer == a) ? "true" : "false") << endl;
    fitSet* diff = new fitSet("situps", "core", 10, 30);
    newer += diff;
    cout << "After adding a workout to only one, are they now different?" << endl;
    cout << ((newer != a) ? "true" : "false") << endl;
}

int main() {
    combine();
    increase();
    comparison();
    intermission();
    decrease();
    addAndRemove();
    equalAndNot();
    return 0;
}

