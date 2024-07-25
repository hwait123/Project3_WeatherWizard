#include <iostream>
#include <string>

#include "City.h"

int main()
{
    string cityInput;
    string dateInput;
    //City gainesville("Gainesville");
    //gainesville.ReadFromCSVFile("Weather_Wizard/Project3_Data/Gainesville/Gainesville_2017.csv");

    City ReadAllFiles("Gainesville");

    cout << "Welcome to Weather Wizard!" << endl;
    cout << "Please enter the name of the city you are visiting." << endl;
    cin >> cityInput;

    City newCity(cityInput);
    newCity.ReadAllFiles();

    cout << "Please eneter a date, formatted YYYY-MM-DD, to begin your search." << endl;
    cin >> dateInput;

    Date* resPtr = newCity.FindDate(dateInput);

    cout << resPtr->air_temp << endl;
    cout << resPtr->wind_speed << endl;
    cout << resPtr->precipitation << endl;

    return 0;
}