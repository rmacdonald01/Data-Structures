//
//  main.cpp
//  HW05
//
//  Created by Bobby Macdonald on 5/10/18.
//  Copyright © 2018 Bobby Macdonald. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <map>
#include <string>
#include <fstream>

using namespace std;

string name[35] = {"Emily", "Steven", "Erik", "Navid", "Andrew", "Ben", "Samantha", "Josh", "Kirtan", "KJ", "Emma", "Alex", "AJ", "Jacob", "Jack", "Kate", "Andres", "Caitlin", "Thomas", "Nick", "Ethan", "Brian", "Ryan", "Owen", "Olivia", "Chris", "Sean", "Paul", "Brandon", "Charlie", "Cooper", "Will", "Max", "Pablo", "May"};

string topic[6] = {"Linked-Lists", "Queues", "Stacks", "Trees", "Inheritance/Polymorphism", "Recursion"};

//making a class called student so that I can encapsulate the different data needed into one object. This makes it easier to keep track of and calculate the values of the variables
class Student{
public:
    Student();
    void setTop(string t) {topic = t;}
    string getTopic() {return topic;}
    int getWait() {return wait;}
    int getMin() {return min;}
    void setWait(int wait) {this->wait = wait;}
private:
    string topic;
    int wait;
    int min;
};

multimap<string , Student* > stud;
multimap<string , Student* >::const_iterator i;


ofstream outfile;


//function to simulate office hours
void OfficeHours(double& totMin, double& totWait, double& totStud, double& totOvr);

//main function
int main() {
    
    srand(time(NULL)); //makes it so that new random values are selected each time
    
    //declaring variables
    double totMin = 0, totWait = 0, totStud = 0, totOvr = 0;
    double avgMin, avgWait, avgOvr;
    
    for (int j = 0; j < 100; j++){
        OfficeHours(totMin, totWait, totStud, totOvr);
    }
    
    //calculating averages
    avgMin = totMin/totStud;
    avgWait = totWait/totStud;
    avgOvr = totOvr/100;
    
    
    cout << "The average time spent helping a student is " << avgMin << " mins." << endl;
    cout << "The average time a student spent waiting is " << avgWait << " mins." << endl;
    cout << "The average time spent past an hour is " << avgOvr << " mins." << endl;
    
    cout << endl;
    for (i = stud.begin(); i != stud.end(); ++i){
        cout << i->first << ":  " << i->second->getTopic() << endl;
    }
    
    outfile.open("/Users/bobbymacdonald/Desktop/1/SCU/Sophomore/Quarter 3/CS61/Homework/HW05/HW05/HW05/students");
    
    if (outfile.is_open()){
        outfile << "Student" << '\t' << "Topic" << endl;
        outfile << endl;
        for (i = stud.begin(); i != stud.end(); ++i){
            outfile << i->first << '\t' << i->second->getTopic() << endl;
        }
    }
    
    outfile.close();
    
    return 0;
}

//constructor sets a random time out of 20 minutes as the students help time
Student::Student(){
    min = rand() % 20;
}

void OfficeHours(double& totMin, double& totWait, double& totStud, double& totOvr){
    
    //create a queue of objects of type Student
    queue <Student *> office;
    
    
    //initializing variables that will be key to solving the problem
    
    int globalTimer = 0;    //the clock that will stop after an 'hour'
    
    int arrivalRate = rand() % 10;  //random rate of students arriving at the office
    
    int arrivalTimer = 0;   //will count minutes up until when the student arrives at office
    
    int currWait = 0;       //adds up all the helping minutes of the preceeding students, helps calculate wait time for each student
    
    bool helping = false;   //a boolean that checks if a student is currently being helped
    
    int helpTimer = 0;      //keeps track of time a student is being helped
    
    Student * current = nullptr;    //current will be filled by top of queue
    
    int overflow = 0;   //keeps track of minutes past an hour that the professor helps students
    
    int totalWait = 0;  //total students wait times
    
    int totalMin = 0;   //total minutes students are helped
    
    int studN = 0;      //total number of students
    
    
    while (globalTimer <= 60 || !office.empty()){
        
        //if-else statement dealing with arrival of students, will stop running after an hour
        if (globalTimer <= 60){
            if (arrivalRate == arrivalTimer){
                Student * s = new Student();
                if (current == nullptr){
                    s->setWait(0);
                } else {
                    //the wait time will be all the help times inside the queue minus however long is left for the current student being helped
                    s->setWait(currWait + current->getMin() - helpTimer);
                }
                //pushing a student object into the queue
                office.push(s);
                
                //calculating the different variables
                currWait += s->getMin();
                totalWait += s->getWait();
                totalMin += s->getMin();
                arrivalTimer = 0;
                arrivalRate = rand() % 10;
                studN++;
                
                int n = rand() % 35;
                int t = rand() % 6;
                
                s->setTop(topic[t]);
                
                stud.insert(make_pair(name[n], s));
            }
            
            else {
                //if it is not time for a student to arrive
                arrivalTimer++;
            }
        }
        
        //if-else statement dealing with the help time of students
        if (helping){
            if (helpTimer == current->getMin()){
                //helpTimer = 0;
                helping = false;
            } else {
                helpTimer++;
            }
            
        }
        
        else{
            helpTimer = 0;
            //making sure the office is not empty
            if (!office.empty()){
                current = office.front();
                office.pop();
                helping = true;
                currWait -= current->getWait();
            } else {
                //helping = false;
                current = nullptr;
            }
        }
        
        if (globalTimer > 60){
            overflow++;
        }
        
        globalTimer++;
        
    }
    
    //adding the totals from the function to the totals of the parameters, which will then be accessible outside the function to calculate averages
    totMin += totalMin;
    totWait += totalWait;
    totStud += studN;
    totOvr += overflow;
}
