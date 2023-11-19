#include <iostream>
#include "./include/myMath.hpp"

using namespace std;

int main(){
    cout << myMathNameSpace::myMath::staticSum(1,2) << endl;
    myMathNameSpace::myMath mMath;
    cout << mMath.mySum(1,2) << endl;
}