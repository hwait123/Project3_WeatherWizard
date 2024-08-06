#include <iostream>
#include <string>
#include <iomanip>

#include "City.h"

using namespace std;

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

    std::cout << "Welcome to the Weather Wizard!" << endl;
    std::cout << "If you are researching weather patterns in the beautiful state of Florida, Weather Wizard is here to help!" << endl << endl;

    string logo = R"(
 
     __    __    ___   ____  ______  __ __    ___  ____       __    __  ____  _____   ____  ____   ___   
    |  |__|  |  /  _] /    ||      ||  |  |  /  _]|    \     |  |__|  ||    ||     | /    ||    \ |   \  
    |  |  |  | /  [_ |  o  ||      ||  |  | /  [_ |  D  )    |  |  |  | |  | |__/  ||  o  ||  D  )|    \ 
    |  |  |  ||    _]|     ||_|  |_||  _  ||    _]|    /     |  |  |  | |  | |   __||     ||    / |  D  |
    |  `  '  ||   [_ |  _  |  |  |  |  |  ||   [_ |    \     |  `  '  | |  | |  /  ||  _  ||    \ |     |
     \      / |     ||  |  |  |  |  |  |  ||     ||  .  \     \      /  |  | |     ||  |  ||  .  \|     |
      \_/\_/  |_____||__|__|  |__|  |__|__||_____||__|\_|      \_/\_/  |____||_____||__|__||__|\_||_____|
                                                                                                    
    )";

    std::cout << logo << endl;
    std::cout << "(Logo created at https://patorjk.com/software/taag/)" << endl << endl << endl;    

    while(true)
    {
        std::cout << "Weather Wizard is programmed to provide weather information for the following cities:" << endl;
        std::cout << "1. Gainesville" << endl;
        std::cout << "2. Jacksonville" << endl;
        std::cout << "3. Miami" << endl;
        std::cout << "4. Orlando" << endl;
        std::cout << "5. Tampa" << endl; 
        std::cout << endl;

        std::cout << "Please enter the number corresponding with the city you wish to research. For example, please enter 1 for Gainesville." << endl;
        std::cout << "If you wish to exit, enter 6." << endl;
        
        std::cin >> cityNum;

        //exit
        if (cityNum == "6")
            break;
        
        cityName = FindCity(cityNum);

        while (!IsValidCity(cityName))
        {
            std::cout << "Sorry! We cannot find that city. Please enter a number from the menu above." << endl;
            std::cin >> cityNum;
            cityName = FindCity(cityNum);
        }

        City newCity(cityName);
        newCity.ReadAllFiles();

        std::cout << endl << "Exellent choice! Now, enter your search start date, formatted YYYY-MM-DD." << endl;
        std::cin >> startDate;

        //chceck for input validity
        while(!IsValidDate(newCity, startDate))
        {
            std::cout << "Sorry! We cannot find that date. Please enter another start date." << endl;
            std::cin >> startDate;
        }

        std::cout << endl<< "Enter your search end date, formatted YYYY-MM-DD." << endl;
        std::cin >> endDate;

        //validate departure date input
        while(!IsValidDate(newCity, endDate) || !IsValidRange(startDate, endDate))
        {
            if (!IsValidDate(newCity, endDate) )
                std::cout << "Sorry! We cannot find that date. Please enter another end date." << endl;
            else if (!IsValidRange(startDate, endDate))
                std::cout << "Sorry! That date does not occur after your start date. Please enter another end date." << endl;

            std::cin >> endDate;
        }

        //create new map object to store date range
        map<string, Date*> newMap;
        newCity.assembleMapBetweenDates(newMap, startDate, endDate);

        std::cout << endl << endl << "Making magic happen..." << endl << endl;
        
        std::cout << fixed << setprecision(2);
        //results
        std::cout << endl << "For dates " << startDate << " through " << endDate << ":" << endl << endl;

        Date* avgData = newCity.getAverageWeatherData(newMap);
        std::cout << "Average Temperature: " << avgData->air_temp << " degrees celsius" << endl;
        std::cout << "Average Wind Speed: " << avgData->wind_speed << " meters per second" << endl;
        std::cout << "Average Precipitation: " << avgData->precipitation <<  " millimeters per hour\n" << endl;
        delete avgData;

        std::cout << "(Calculated with std::sort)" << endl;
        std::cout << "Highest temperature, calculated in " << newCity.findHighestTemperature(newMap, "std_sort").second.count() << " microseconds: " << newCity.findHighestTemperature(newMap, "std_sort").first->air_temp << " degrees celsius" << endl;
        std::cout << "Lowest temperature, calculated in " << newCity.findLowestTemperature(newMap, "std_sort").second.count() << " microseconds: " << newCity.findLowestTemperature(newMap, "std_sort").first->air_temp << " degrees celsius" << endl;
        std::cout << "Fastest wind speed, calculated in " << newCity.findMaxWindSpeed(newMap, "std_sort").second.count() << " microseconds: " << newCity.findMaxWindSpeed(newMap, "std_sort").first->wind_speed << " meters per second" << endl;
        std::cout << "Highest precipitation, calculated in " << newCity.findMaxPrecipitation(newMap, "std_sort").second.count() << " microseconds: " << newCity.findMaxPrecipitation(newMap, "std_sort").first->precipitation << " millimeters per hour" << endl;

        //*******************************************************************************
        //repeated with second sort
        std::cout << endl << "(Calculated with merge sort)" << endl;
        std::cout << "Highest temperature, calculated in " << newCity.findHighestTemperature(newMap, "merge_sort").second.count() << " microseconds: " << newCity.findHighestTemperature(newMap, "merge_sort").first->air_temp << " degrees celsius" << endl;
        std::cout << "Lowest temperature, calculated in " << newCity.findLowestTemperature(newMap, "merge_sort").second.count() << " microseconds: " << newCity.findLowestTemperature(newMap, "merge_sort").first->air_temp << " degrees celsius" << endl;
        std::cout << "Fastest wind speed, calculated in " << newCity.findMaxWindSpeed(newMap, "merge_sort").second.count() << " microseconds: " << newCity.findMaxWindSpeed(newMap, "merge_sort").first->wind_speed << " meters per second" << endl;
        std::cout << "Highest precipitation, calculated in " << newCity.findMaxPrecipitation(newMap, "merge_sort").second.count() << " microseconds: " << newCity.findMaxPrecipitation(newMap, "merge_sort").first->precipitation << " millimeters per hour"<< endl;
        std::cout << endl << endl;
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
    //check if start date is before end date
    if (startDate > endDate)
        return false;
    return true;
}