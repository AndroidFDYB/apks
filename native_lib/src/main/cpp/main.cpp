#include "iostream"
#include "native_add.h"
using namespace std;
int main(int argc,const char** argv) {
//    printf();
    int a = 10;
    int b = 20;
    int sum = add(a,b);
    cout << "sum : " << sum << endl;
    return 0;
}