#include <iostream>
#include <string>

#include "City.h"

string FindCity (string input);
bool IsValidCity(string city);
bool IsValidDate(City city, string date);
bool IsValidRange(string arrivalDate, string departureDate);
void LoadAllCities();

int main()
{
    string cityNum;
    string cityName;
    string arrivalInput;
    string departureInput;

    City ReadAllFiles("Gainesville");

    cout << "Welcome to the Weather Wizard!" << endl;
    cout << "If you are planning a trip to the beautiful state of Florida, Weather Wizard is here to help!" << endl << endl;

    //ASCII logo here, if possible

    cout << "Weather Wizard is programmed to provide weather information for the following cities:" << endl;
    cout << "1. Gainesville" << endl;
    cout << "2. Jacksonville" << endl;
    cout << "3. Miami" << endl;
    cout << "4. Orlando" << endl;
    cout << "5. Tampa" << endl; 
    //cout << "6. Give me them all!" << endl;
    cout << endl;

    cout << "Please enter the number corresponding with the city you wish to research." << endl;
    cout << "For example, please enter 1 for Gainesville." << endl;
    
    cin >> cityNum;
    cityName = FindCity(cityNum);

    while (!IsValidCity(cityName))
    {
        cout << "Sorry! We cannot find that city. Please enter a number from the menu above." << endl;
        cin >> cityNum;
        cityName = FindCity(cityNum);
    }

    //might use this, commented out for now
    /*if (cityName == "All")
    {
        cout << "We're not sure why you want information on all cities... but your wish is Weather Wizard's command!" << endl;
        cout << "(Wait... this isn't Weather Genie!)" << endl << endl;
        LoadAllCities();

        cout << "Please enter a start date for your search, formatted YYYY-MM-DD." << endl;
    }

    else
    {
        City newCity(cityName);
        newCity.ReadAllFiles();
        cout << "Exellent choice! Now, enter your intended arrival date, formatted YYYY-MM-DD." << endl;
    }*/

    City newCity(cityName);
    newCity.ReadAllFiles();

    cout << endl << "Exellent choice! Now, enter your intended arrival date, formatted YYYY-MM-DD." << endl;
    cin >> arrivalInput;

    //chceck for input validity
    while(!IsValidDate(newCity, arrivalInput))
    {
        cout << "Sorry! We cannot find that date. Please enter another arrival date." << endl;
        cin >> arrivalInput;
    }

    cout << endl<< "Enter your intended departure date, formatted YYYY-MM-DD." << endl;
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

    cout << endl << endl << "Making magic happen..." << endl << endl;

    //results
    cout << endl << "For dates " << arrivalInput << " through " << departureInput << ":" << endl << endl;
    
    cout << "(Calculated with [insert sort here], which took [time spent here])" << endl;
    cout << "Highest temperature: " << endl;
    //print highest temperature on what day
    cout << "Lowest temperature: " << endl;
    //print lowest temperature on what day

    //Keep to fasted and highest precipitation, because slowest and lowest will probably be 0
    //might change mind here
    cout << "Fastest wind speed: " << endl;
    //print results
    cout << "Highest precipitation: " << endl;
    //print results

    //*******************************************************************************
    //repeated with second sort
    cout << endl << "(Calculated with [insert sort here], which took [time spent here])" << endl;
    cout << "Highest temperature: " << endl;
    //print highest temperature on what day
    cout << "Lowest temperature: " << endl;
    //print lowest temperature on what day

    //Keep to fasted and highest precipitation, because slowest and lowest will probably be 0
    //might change mind here
    cout << "Fastest wind speed: " << endl;
    //print results
    cout << "Highest precipitation: " << endl;
    //print results

    return 0;
}

string FindCity(string input)
{
    if (input == "1")
        return "Gainesville";
    if (input == "2")
        return "Jacksonville";
    if (input == "3")
        return "Miami"; 
    if (input == "4")
        return "Orlando";
    if (input == "5")
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
    if (city.GetDate(date).size() == 0)
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

void LoadAllCities()
{
    City Gainesville("Gainesville");
    Gainesville.ReadAllFiles();

    City Jacksonville("Jacksonville");
    Jacksonville.ReadAllFiles();

    City Miami("Miami");
    Miami.ReadAllFiles();

    City Orlando("Orlando");
    Orlando.ReadAllFiles();

    City Tampa("Tampa");
    Tampa.ReadAllFiles();
}