#include <iostream>
#include "clsDate.h"

using namespace std;

int main()
{
    cout << "OOP Projects : class Date!" << endl;

    clsDate Date;
    Date.Print();

    Date.AddOneYear();
    Date.Print();

    Date.LimitOneDay();
    Date.Print();

    Date.LimitOneMonth();
    Date.Print();

    Date.LimitMultiMonths(3);
    Date.Print();

    Date.AddMultiDay(14);
    Date.Print();

    clsDate Date2(202,2023);
    Date2.Print();

    return 0;
}
