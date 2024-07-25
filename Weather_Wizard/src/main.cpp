#include <iostream>
#include <string>

#include "City.h"

bool IsValidDate(City city, string date);
bool IsValidRange(string arrivalDate, string departureDate);

int main()
{
    string cityInput;
    string arrivalInput;
    string departureInput;

    City ReadAllFiles("Gainesville");

    cout << "Welcome to the Weather Wizard!" << endl;

//ASCII logo here, if possible

    cout << "Please enter the name of the city you are visiting." << endl;
    cin >> cityInput;

    //
    //need code to validate city input here
    //

    City newCity(cityInput);
    newCity.ReadAllFiles();

    cout << "Exellent choice! Now, enter your intended arrival date, formatted YYYY-MM-DD." << endl;
    cin >> arrivalInput;

    //chceck for input validity
    while(!IsValidDate(newCity, arrivalInput))
    {
        cout << "Sorry! We cannot find that date. Please enter another arrival date." << endl;
        cin >> arrivalInput;
    }

    cout << "Enter your intended departure date, formatted YYYY-MM-DD." << endl;
    cin >> departureInput;

    //validate departure date input
    while(!IsValidDate(newCity, departureInput) || !IsValidRange(arrivalInput, departureInput))
    {
        if (!IsValidDate(newCity, departureInput) )
            cout << "Sorry! We cannot find that date. Please enter another departure date." << endl;
        else if (!IsValidRange(arrivalInput, departureInput))
            cout << "Sorry! That date does not occur after your arrival date. Please enter another departure date." << endl;

        cin >> departureInput;
    }

    Date* resPtr = newCity.GetDate(arrivalInput);

    cout << resPtr->air_temp << endl;
    cout << resPtr->wind_speed << endl;
    cout << resPtr->precipitation << endl;

    return 0;
}

bool IsValidDate(City city, string date)
{
    //check if date as inputted exists
    if (city.GetDate(date) == nullptr)
        return false;
    return true;
}

bool IsValidRange(string arrivalDate, string departureDate)
{
    //I think this will work, but need to test;

    if (arrivalDate > departureDate)
        return false;
    return true;
}