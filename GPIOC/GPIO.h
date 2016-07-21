#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

#include <string>
using namespace std;
/*
Cette classe représente un GPIO Pin d'un numéro donné
*/

class GPIO{
    public:
        GPIO(string gpioNumber);
        void gpio_init();
        int gpio_export();
        int gpio_unexport();
        int gpio_setdir(string dir);
        int gpio_setval(string val);
        int gpio_getval(string& val);
        string gpio_getNum();

    private:
        string gpio_Number;
};

#endif // GPIO_H_INCLUDED
