#pragma once

#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

struct Day
{
	//variables
	string date;
	float air_temp;
	float wind_speed;
	float precipitation;

	//constructor
	Day(string date, float air_temp, float wind_speed, float precipitation)
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
	unordered_map<Day*> days;

public:

	void Deserialize(fstream file);
};