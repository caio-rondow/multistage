#include <iostream>

using namespace std;


int main(){
    double a=-1;
    for(int i=0; i<1000; i++){
        double b;
        cin >> b; 
        a=max(a,b);
    }
    cout << a << "\n";

    return 0;
}