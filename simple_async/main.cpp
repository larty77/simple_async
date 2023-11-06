#include <iostream>
#include "src/future.cpp"

using namespace std;

void multiply(int* val) {
    *val *= 2;
}

void print() {
    for (int i = 0; i < 10; i++) cout << i << endl;
}

long sum(int a, int b) {
    return a + b;
}

int main()
{
    int result_m = 10;
    auto task_m = future::async(multiply, &result_m);
    ++task_m; // ++task
    cout << result_m << endl; //20

    auto task_sum = future::async(sum, 15, 20);
    auto task_print = future::async(print);

    auto result_sum = ++task_sum;
    cout << result_sum << endl; //35

    ++task_print;

    //Output:
    /*
    20
    0
    1
    2
    3
    4
    5
    6
    7
    8
    9
    35
    */
}