//
//  main.cpp
//  HW01
//
//  Created by Bobby Macdonald on 4/8/18.
//  Copyright © 2018 Bobby Macdonald. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>

//headers that allow access to stacks and other libraries


using namespace std;

void in2pre(string in);
void pre2in(string pre);


int main() {
    cout << "Enter an equation to convert: ";
    string e;
    cin >> e;
    in2pre(e);
    
    cout << "Enter an equation in prefix notation: ";
    string p;
    cin.ignore();
    getline(cin, p);
    pre2in(p);
    return 0;
}

//infix to prefix function
void in2pre(string in){
    
    stack <char> eq;
    stack <char> o; //stack eq will store the eventual prefix notated equation, stack o will store operators and parantheses
    
    reverse(in.begin(), in.end()); //reversing the equation so we can put it into the stack
    
    for (int i = 0; i < in.length(); i++){  //this for loop will be large and will take care of most of the function
        
        if (in[i] >= '0' && in[i] <= '9'){  //input the number into the stack
            eq.push(' ');
            eq.push(in[i]);
            while ((in[i+1] >= '0' && in[i+1] <= '9') && (i+1 < in.length())){  //while loop takes care of multi digit number
                
                eq.push(in[i+1]);
                i++;
            }
            
        }
        
        //this else-if statement takes care of ordering the operations in the stack and putting them in  a separate stack
        else if (in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/' || in[i] == '^'){
            if (o.empty()){
                o.push(in[i]);
                
            }
            else if ((o.top() == '+' || o.top() == '-') && (in[i] == '*' || in[i] == '/')){
                o.push(in[i]);
                
            }
            else if ((o.top() == '*' || o.top() == '/') && (in[i] == '+' || in[i] == '-')){
                eq.push(o.top());
                o.pop();
                o.push(in[i]);
                
            }
            else if ((o.top() == '*' || o.top() == '/') && (in[i] == '*' || in[i] == '/')){
                o.push(in[i]);
                
            }
            else if ((o.top() == '+' || o.top() == '-') && (in[i] == '+' || in[i] == '-')){
                o.push(in[i]);
                
            }
            else if ((o.top() == '*' || o.top() == '/' || o.top() == '+' || o.top() == '-') && in[i] == '^'){
                o.push(in[i]);
                
            }
            else if ((in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/') && o.top() == '^'){
                eq.push(o.top());
                o.pop();
                o.push(in[i]);
                
            }
            else if (o.top() == ')'){
                o.push(in[i]);
            }
        }
        
        //when there are parentheses, those will also be put in the stack
        else if (in[i] == ')'){
            o.push(in[i]);
        }
        
        //here, the closed parentheses will tell the function to put what was inside it into the stack
        else if (in[i] == '('){
            if (o.top() != ')'){
                eq.push(o.top());
                o.pop();
            }
            if (o.top() == ')'){
                o.pop();
            }
        }
    }
    
    //putting the rest of the operations into the final stack, checking that the stack is not empty
    while (!o.empty()){
        if(o.top() != ')'){
            eq.push(o.top());
        }
        o.pop();
    }

    //printing the equation in prefix
    cout << "The equation in prefix notation is: ";
    while (!eq.empty()){
        cout << eq.top();
        eq.pop();
    }
    cout << endl;
}


//prefix to infix function

//hoping that whoever is peer reviewing this can help me with my problem here. In theory this code should run but I keep getting bad access errors after it compiles and partially runs. I thought it was that I might be accessing an empty stack, but I check it at every point so that may not be it. Anyways...

void pre2in(string pre){
    stack <char> eq;
    string in = ""; //final notation to be stored here
    
    reverse(pre.begin(), pre.end()); //reversing the equation so we can put it into the stack
    
    for (int i = 0; i < pre.length(); i++){
        if (pre[i] >= '0' && pre[i] <= '9'){    //inserting the numbers/operands into the stack
            eq.push(pre[i]);
            
            //takes care of multi digit numbers
            while ((pre[i+1] >= '0' && pre[i+1] <= '9') && (i+1 < pre.length())){
                eq.push(pre[i+1]);
                i++;
            }
        }
        
        //also putting spaces in the stack so we know where to put the operations between numbers
        else if (pre[i] == ' '){
            eq.push(pre[i]);
        }
        
        //case where an operation is located
        else if (pre[i] == '+' || pre[i] == '-' || pre[i] == '*' || pre[i] == '/' || pre[i] == '^'){
            string p1, p2;
            
            p1 = eq.top();  //putting the first number into a temporary string
            
            eq.pop();
            
            //for multi digit number
            while (eq.top() != ' '){
                if (!eq.empty()){
                    p1 += eq.top();
                    eq.pop();
                }
                
            }
            
            p2 = eq.top();  //putting the second number into a temporary string
            
            if (!eq.empty()){
                eq.pop();
            }
            
            //for multi digit number
            while (eq.top() != ' '){
                if (!eq.empty()){
                    p2 += eq.top();
                    eq.pop();
                }
            }
            
            if (!eq.empty()){
                eq.pop();   //popping the spaces if there are any
            }
            
            
            in += "(" + p1 + pre[i] + p2 + ")"; //adding the operations into the string
            
        }
    }
    cout << "This equation in infix is " << in << endl;
}












