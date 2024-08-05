#pragma once

#include <unordered_map>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace std::chrono;

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
    pair <Date*, duration<double, micro>> findHighestTemperature(map<string, Date *> &dates_);
    pair <Date*, duration<double, micro>> findLowestTemperature(map<string, Date *> &dates_);
	pair <Date*, duration<double, micro>> findMaxWindSpeed(map<string, Date*>& dates_);
	pair <Date*, duration<double, micro>> findMaxPrecipitation(map<string, Date*>& dates_);
	Date* GetResultStdSort(pair <string, string> sortBasedOn, vector<Date*>& allAverages);
	vector<Date*> slice(vector<Date*> dates, int start, int end);
	vector<Date*> merge(vector<Date*> left, vector<Date*> right, string sortBasedOn);
	vector<Date*> mergeSort(vector<Date*> dates, string sortBasedOn);
	
	//behaviors
	void assembleMapBetweenDates(map<string, Date*>& newMap, const string& startDate, const string& endDate);
	int dateToInt(const string& date);
	void LoadAveragesVec(vector<Date*>& allAverages, map<string, Date*>& dates_);
	void LoadAveragesVec(vector<Date*>& allAverages, map<string, Date*>& dates_);

    //search

	//for testing
	void PrintMap();
};