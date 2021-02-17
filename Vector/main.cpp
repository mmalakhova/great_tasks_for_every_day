#include <iostream>
#include "Vector.h"

int main(){
    vector<int> myvector;
    for (int j = 1; j <= 6; j++) {
        myvector.push_back(j);
    }

    for (auto it = myvector.begin(); it != myvector.end(); ++it)
        std::cout << ' ' << *it;

    for (auto& val : myvector) {
        std::cout << ' ' << val;
    }
}
