//
//  main.cpp
//  HW07
//
//  Created by Bobby Macdonald on 5/23/18.
//  Copyright © 2018 Bobby Macdonald. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

ifstream infile;
ofstream outfile;

template <class item>
void insertionsort(item a[], size_t n){     //insertion sort method
    for (int i = 1; i < n; i++)
    {
        int j = i;
        while (a[j] < a[j - 1]) //use new variable j so that we don't lose our place in the array
        {
            item temp = a[j];   //swap the values if the current is greater than the one in front of it
            a[j] = a[j-1];
            a[j-1] = temp;
            j--;
        }
    }
}



int main() {
    int a[10] = {4, 2, 10, 5, 8, 15, 12, 3, 9, 11};     //out of order to be sorted
    
    insertionsort(a, 10);
    
    for (int i = 0; i < 10; i++){
        cout << a[i] << "  ";
    }
    cout << endl;
    
    infile.open("/Users/bobbymacdonald/Desktop/1/SCU/Sophomore/Quarter 3/CS61/Homework/HW07/HW07/HW07/student.txt");
    
    string file[38];
    int i = 0;
    if (infile.is_open()){      //opening the file and storing it into array
        while (!infile.eof()){
            string name;
            getline(infile, name);
            file[i] = name;         //array to be sorted
            i++;
        }
    }
    
    infile.close();
    
    insertionsort(file, 38);    //sort the names
    
    outfile.open("/Users/bobbymacdonald/Desktop/1/SCU/Sophomore/Quarter 3/CS61/Homework/HW07/HW07/HW07/sortedstudent.txt");
    
    for (int i = 0; i < 38; i++){       //putting the names back into another file to show sorting
        outfile << file[i] << endl;
    }
    
    
    outfile.close();
    infile.close();     //closed both files
    
    
    return 0;
}
