#pragma once

#include <unordered_map>
#include <map>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Date
{
	//variables
	string date;
	float air_temp;
	float wind_speed;
	float precipitation;

	//constructor
	Date(string date, float air_temp, float wind_speed, float precipitation)
	{
		this->date = date;
		this->air_temp = air_temp;
		this->wind_speed = wind_speed;
		this->precipitation = precipitation;
	}

};

class City
{

	//to keep track of the city name
	string cityName;

	//might go back to an unorder_map depending on time
	//a regular map keeps dates in order for ease of searching date ranges
	map<string, vector<Date*>> dates;

public:

	//constructor
	City(string cityName);

	//getters
	vector<Date*> GetDate(string date);

	//file management
	void ReadAllFiles();
	void ReadFromCSVFile(string filepath);
	void Deserialize(istringstream& stream);
	void AddDate(string date, string time, string air_temp, string wind_speed, string precipitation);
	
	//calculations
	Date* averageData(const vector<Date*>& date_);
    Date* findHighestTemperature(map<string, vector<Date *>> &dates_);
    Date* findLowestTemperature(map<string, vector<Date *>> &dates_);
	Date* findMaxWindSpeed(map<string, vector<Date*>>& dates_);
	Date* findMaxPrecipitation(map<string, vector<Date*>>& dates_);
	
	//behaviors
	map<string, vector<Date*>> assembleMapBetweenDates(map<string, vector<Date*>>& dates, const string& startDate, const string& endDate);
	int dateToInt(const string& date);
	void LoadAveragesVec(vector<Date*>& allAverages, map<string, vector<Date*>>& dates_);

    //search

	//for testing
	void PrintMap();
};