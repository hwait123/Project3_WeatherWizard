#include <iostream>
#include <string>

#include "City.h"

string FindCity(int input);
bool IsValidCity(string city);
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

    ///////////////////////////////////////////////////////
    //
    // need code to validate city input here
    //
    ///////////////////////////////////////////////////////
    
    ///////////////////////////////////////////////////////
    //
    // also need to do one of two things:
    // either format maps to automatically average hourly data and store it
    // in "day" objects instead of hourly objects, or add a buffer between 
    // user input and map, so user input is not directly fed into map (since
    // we do not want the user to have to enter times as well as years, months, 
    // and days)
    //
    ///////////////////////////////////////////////////////

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

    ///////////////////////////////////////////////////////
    //
    // Run sorts on data, and format output, including time
    // spent on each sort, in a clean-looking table
    //
    ///////////////////////////////////////////////////////

    //temp code, for testing purposes*******************
    //Date* resPtr = newCity.GetDate(arrivalInput);

    //cout << resPtr->air_temp << endl;
    //cout << resPtr->wind_speed << endl;
    //cout << resPtr->precipitation << endl;
    //**************************************************

    return 0;
}

string FindCity(int input)
{
    if (input == 1)
        return "Gainesville";
    if (input == 2)
        return "Jacksonville";
    if (input == 3)
        return "Miami"; 
    if (input == 4)
        return "Orlando";
    if (input == 5)
        return "Tampa";

    return "";
}

bool IsValidCity(string city)
{
    if (city == "")
        return false;
    return true;
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