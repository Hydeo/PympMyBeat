#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "GPIO.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    string state;
    int i = 0;
    GPIO gpio18("18");
    cout << gpio18.gpio_getNum();
    gpio18.gpio_export();
    gpio18.gpio_setdir("out");

    while(i < 50 )
    {
        usleep(50000);
        gpio18.gpio_getval(state);
        cout << "State is : " + state<<endl;

        if(state == "0")
        {
            gpio18.gpio_setval("1");
        }
        else
        {
            gpio18.gpio_setval("0");
        }
        i++;
    }

    gpio18.gpio_unexport();

    cout << "Fin du programme ...";
    return 0;
}
