//
//  main.cpp
//  HW04
//
//  Created by Bobby Macdonald on 5/3/18.
//  Copyright © 2018 Bobby Macdonald. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <queue>
#include <algorithm>    //to get swap function
#include "bintree.h"

using namespace std;
using namespace main_savitch_10;

class Student{
public:
    Student();
    Student(int p);
    int priority;
    int getWait() {return wait;}
    int getMin() {return min;}
    void setWait(int wait) {this->wait = wait;}
private:
    int wait;
    int min;
};

bool operator <(const Student& a, const Student& b) {
    return a.priority < b.priority;
}

void OfficeHours(double& totMin, double& totWait, double& totStud, double& totOvr);

template <class Item>
void change(binary_tree_node<Item>* &root, binary_tree_node<Item>* &child);

template <class Item>
binary_tree_node<Item>* heap(binary_tree_node<Item>* root_ptr);

int main() {
    priority_queue<Student> test;
    //here is a tester program to show that the priority queue works
    for (int i: {3, 7, 25, 20, 13, 16, 6}){
        test.push(Student(i));  //values put into the queue at random, not in order
    }
    while (!test.empty()){
        Student a = test.top(); //objects are popped from the queue and priorities are output
        test.pop();
        cout << a.priority << " ";  //the output is in order
    }
    
    
    cout << endl;
    
    
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
    
    
    cout << "--------------------------------------" << endl;
    cout << "Trees:" << endl;
    
    binary_tree_node<int> *heap_root = new binary_tree_node<int> (10);
    heap_root->set_left(new binary_tree_node<int> (4));
    heap_root->set_right(new binary_tree_node<int> (18));
    heap_root->left()->set_left(new binary_tree_node<int> (2));
    heap_root->right()->set_left(new binary_tree_node<int> (13));
    heap_root->left()->set_right(new binary_tree_node<int> (7));
    heap_root->right()->set_right(new binary_tree_node<int> (25));
    heap_root->left()->left()->set_left(new binary_tree_node<int> (1));
    heap_root->left()->right()->set_left(new binary_tree_node<int> (5));
    heap_root->left()->left()->set_right(new binary_tree_node<int> (3));
    heap_root->left()->right()->set_right(new binary_tree_node<int> (9));
    heap_root->right()->left()->set_left(new binary_tree_node<int> (11));
    heap_root->right()->right()->set_left(new binary_tree_node<int> (20));
    heap_root->right()->left()->set_right(new binary_tree_node<int> (15));
    heap_root->right()->right()->set_right(new binary_tree_node<int> (30));
    
    
    print(heap_root, 0);
    
    heap(heap_root);
    
    print(heap_root, 0);
    
    return 0;
}

Student::Student(){
    min = rand() % 20;
    priority = rand() % 3;  //There will be 3 levels of priority to the students needs, the third level
}

Student::Student(int p){    //constructor with
    priority = p;
}


void OfficeHours(double& totMin, double& totWait, double& totStud, double& totOvr){
    
    //create a queue of objects of type Student
    priority_queue <Student *> office;
    
    
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
                current = office.top();
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



template <class Item>
void change(binary_tree_node<Item>* &root, binary_tree_node<Item>* &child){
    Item temp = child->data();
    child->set_data(root->data());
    root->set_data(temp);
}

template <class Item>
binary_tree_node<Item>* heap(binary_tree_node<Item> *root_ptr){  //will make a minimum heap
    
    binary_tree_node<Item> *temp = root_ptr;
    
    if (temp->left() != NULL){

        if (temp->data() > temp->left()->data()){
            binary_tree_node<Item>* other = temp->left();
            temp->left()->set_data(root_ptr->data());
            root_ptr->set_data(other->data());
        }
        
        heap(temp->left());
    }
    
    if (temp->right() != NULL){
        if (temp->data() > temp->right()->data()){
            binary_tree_node<Item>* another = temp->right();
            temp->right()->set_data(root_ptr->data());
            root_ptr->set_data(another->data());
        }
        heap(temp->right());
    }
    
    
    return root_ptr;
}








