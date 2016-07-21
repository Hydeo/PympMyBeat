#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "GPIO.h"

using namespace std;

GPIO::GPIO(string gpioNumber)
{
    this->gpio_Number = gpioNumber;
}

//Exportation du GPIO
int GPIO::gpio_export()
{
    string export_file = "/sys/class/gpio/export";
    ofstream gpio_Export(export_file.c_str()); //convertion de la chaine en chemin linux valide
    if(gpio_Export < 0)
    {
        cout << "ERREUR : Exportation du GPIO impossible (ouverture du fichier)";
        return -1;
    }

    gpio_Export << this->gpio_Number;
    gpio_Export.close();
    return 0;

}

//Unexport du GPIO = remise a 0 de la configuration
int GPIO::gpio_unexport()
{
    string unexport_file = "/sys/class/gpio/unexport";
    ofstream gpio_Unexport(unexport_file.c_str());
    if(gpio_Unexport < 0)
    {
        cout << "ERREUR : Unexport du GPIO impossible (ouverture du fichier)";
        return -1;
    }

    gpio_Unexport << this->gpio_Number;
    gpio_Unexport.close();
    return 0;

}

//Set la direction du GPIO : IN / OUT
int GPIO::gpio_setdir(string dir)
{
    string setdir_file = "/sys/class/gpio/gpio" + this->gpio_Number +"/direction";
    ofstream gpio_setdir(setdir_file.c_str());
    if(gpio_setdir < 0)
    {
        cout << "ERREUR : Impossible d'atteindre la direction du GPIO "<<this->gpio_Number<<endl;
        return -1;
    }

    gpio_setdir << dir;
    gpio_setdir.close();
    return 0;
}

//Set valeur du GPIO : 1 / 0 == ON / OFF
int GPIO::gpio_setval(string val)
{
    string setval_file = "/sys/class/gpio/gpio" + this ->gpio_Number + "/value";
    ofstream gpio_setval(setval_file.c_str());
    if(gpio_setval < 0)
    {
        cout << "ERREUR : Impossible d'atteindre la valeur du GPIO (set) " << this->gpio_Number << endl;
        return -1;
    }

    gpio_setval << val;
    gpio_setval.close();
    return 0;
}


//Get la valeur du GPIO a l'instant de l'appel
int GPIO::gpio_getval(string& val)
{
    string getval_file = "/sys/class/gpio/gpio" + this->gpio_Number + "/value";
    ifstream gpio_getval(getval_file.c_str());
    if(gpio_getval < 0)
    {
        cout << "ERREUR : Impossible d'atteindre la valeur du GPIO (get) " << this->gpio_Number << endl;
        return -1;
    }

    gpio_getval >> val; // On récupère la valeur du GPIO

    if(val != "0")
    {
        val = "1";
    }
    else
    {
        val = "0";
    }

    gpio_getval.close();
    return 0;
}

//Récupération du numéro du GPIO
string GPIO::gpio_getNum()
{
    return this->gpio_Number;
}

void GPIO::gpio_init(){
    this->gpio_export();
    this->gpio_setdir("out");
}
