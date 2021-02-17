#include <iostream>
#include "Vector.h"

int main(){
    vector<int> myvector;
    myvector.push_back(1);
    myvector.push_back(2);
    myvector.push_back(3);
    myvector.push_back(4);
    myvector.push_back(5);
    myvector.push_back(6);
    // vector becomes 1, 2, 3, 4, 5, 6 

    // printing the vector 
    for (auto it = myvector.begin(); it != myvector.end(); ++it)
        std::cout << ' ' << *it;
}
