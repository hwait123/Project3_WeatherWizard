#pragma once

#include <unordered_map>
#include <string>
#include <fstream>

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

	//hashmap
	unordered_map<string, Date*> dates;

public:

	//constructor
	City(string& cityName);

	//file management
	void ReadFromCSVFile(string& filepath);
	void Deserialize(istringstream& stream);
	void AddDate(string date, string air_temp, string wind_speed, string precipitation);

	//for testing
	void PrintMap();
};