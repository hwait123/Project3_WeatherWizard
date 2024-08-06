#include <iostream>
#include <string>
#include <iomanip>

#include "City.h"

string FindCity (string input);
bool IsValidCity(string city);
bool IsValidDate(City city, string date);
bool IsValidRange(string startDate, string endDate);

int main()
{
    string cityNum;
    string cityName;
    string startDate;
    string endDate;

    cout << "Welcome to the Weather Wizard!" << endl;
    cout << "If you are researching weather patterns in the beautiful state of Florida, Weather Wizard is here to help!" << endl << endl;

    //ASCII logo here, if possible

    while(true)
    {
        cout << "Weather Wizard is programmed to provide weather information for the following cities:" << endl;
        cout << "1. Gainesville" << endl;
        cout << "2. Jacksonville" << endl;
        cout << "3. Miami" << endl;
        cout << "4. Orlando" << endl;
        cout << "5. Tampa" << endl; 
        cout << endl;

        cout << "Please enter the number corresponding with the city you wish to research. For example, please enter 1 for Gainesville." << endl;
        cout << "If you wish to exit, enter 6." << endl;
        
        cin >> cityNum;

        //exit
        if (cityNum == "6")
            break;
        
        cityName = FindCity(cityNum);

        while (!IsValidCity(cityName))
        {
            cout << "Sorry! We cannot find that city. Please enter a number from the menu above." << endl;
            cin >> cityNum;
            cityName = FindCity(cityNum);
        }

        City newCity(cityName);
        newCity.ReadAllFiles();

        cout << endl << "Exellent choice! Now, enter your search start date, formatted YYYY-MM-DD." << endl;
        cin >> startDate;

        //chceck for input validity
        while(!IsValidDate(newCity, startDate))
        {
            cout << "Sorry! We cannot find that date. Please enter another start date." << endl;
            cin >> startDate;
        }

        cout << endl<< "Enter your search end date, formatted YYYY-MM-DD." << endl;
        cin >> endDate;

        //validate departure date input
        while(!IsValidDate(newCity, endDate) || !IsValidRange(startDate, endDate))
        {
            if (!IsValidDate(newCity, endDate) )
                cout << "Sorry! We cannot find that date. Please enter another end date." << endl;
            else if (!IsValidRange(startDate, endDate))
                cout << "Sorry! That date does not occur after your start date. Please enter another end date." << endl;

            cin >> endDate;
        }

        //create new map object to store date range
        map<string, Date*> newMap;
        newCity.assembleMapBetweenDates(newMap, startDate, endDate);

        cout << endl << endl << "Making magic happen..." << endl << endl;
        
        cout << fixed << setprecision(2);
        //results
        cout << endl << "For dates " << startDate << " through " << endDate << ":" << endl << endl;

        Date* avgData = newCity.getAverageWeatherData(newMap);
        cout << "Average Temperature: " << avgData->air_temp << " degrees celsius" << endl;
        cout << "Average Wind Speed: " << avgData->wind_speed << " meters per second" << endl;
        cout << "Average Precipitation: " << avgData->precipitation <<  " millimeters per hour\n" << endl;
        delete avgData;

        cout << "(Calculated with std::sort)" << endl;
        cout << "Highest temperature, calculated in " << newCity.findHighestTemperature(newMap, "std_sort").second.count() << " microseconds: " << newCity.findHighestTemperature(newMap, "std_sort").first->air_temp << " degrees celsius" << endl;
        cout << "Lowest temperature, calculated in " << newCity.findLowestTemperature(newMap, "std_sort").second.count() << " microseconds: " << newCity.findLowestTemperature(newMap, "std_sort").first->air_temp << " degrees celsius" << endl;
        cout << "Fastest wind speed, calculated in " << newCity.findMaxWindSpeed(newMap, "std_sort").second.count() << " microseconds: " << newCity.findMaxWindSpeed(newMap, "std_sort").first->wind_speed << " meters per second" << endl;
        cout << "Highest precipitation, calculated in " << newCity.findMaxPrecipitation(newMap, "std_sort").second.count() << " microseconds: " << newCity.findMaxPrecipitation(newMap, "std_sort").first->precipitation << " millimeters per hour" << endl;

        //*******************************************************************************
        //repeated with second sort
        cout << endl << "(Calculated with merge sort)" << endl;
        cout << "Highest temperature, calculated in " << newCity.findHighestTemperature(newMap, "merge_sort").second.count() << " microseconds: " << newCity.findHighestTemperature(newMap, "merge_sort").first->air_temp << " degrees celsius" << endl;
        cout << "Lowest temperature, calculated in " << newCity.findLowestTemperature(newMap, "merge_sort").second.count() << " microseconds: " << newCity.findLowestTemperature(newMap, "merge_sort").first->air_temp << " degrees celsius" << endl;
        cout << "Fastest wind speed, calculated in " << newCity.findMaxWindSpeed(newMap, "merge_sort").second.count() << " microseconds: " << newCity.findMaxWindSpeed(newMap, "merge_sort").first->wind_speed << " meters per second" << endl;
        cout << "Highest precipitation, calculated in " << newCity.findMaxPrecipitation(newMap, "merge_sort").second.count() << " microseconds: " << newCity.findMaxPrecipitation(newMap, "merge_sort").first->precipitation << " millimeters per hour"<< endl;
        cout << endl << endl;
    }

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

bool IsValidRange(string startDate, string endDate)
{
    //I think this will work, but need to test;
    if (startDate > endDate)
        return false;
    return true;
}