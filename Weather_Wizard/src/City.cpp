#include <sstream>
#include <iostream>
#include <iterator>

#include "City.h"

using namespace std;

City::City(string cityName)
{
	this->cityName = cityName;
}

vector<Date*> City::GetDate(string date)
{
	//locate date and return ptr if found. return null else
	if (dates.find(date) == dates.end())
		return {};

	return dates[date];
}

void City::ReadAllFiles()
{
	//read all files for a given city. this will be adjusted when we add more files
	for (int i = 0; i < 12; i++)
		ReadFromCSVFile("Weather_Wizard/Project3_Data/" + cityName + "/" + cityName + "_" + to_string(2010 + i) + ".csv");

}

//read csv files annd create city objects
//hannah burgett borrowed some code from her COP3503 lab7
void City::ReadFromCSVFile(string filepath)
{
	//open file
	ifstream inFile(filepath);

	if (inFile.is_open())
	{
		//dispose of header row
		string lineFromFile;
		getline(inFile, lineFromFile);

		while (getline(inFile, lineFromFile))
		{
			if (lineFromFile != "")
			{
				//read line and deserialize
				istringstream stream(lineFromFile);
				Deserialize(stream);
			}
		}

		inFile.close();
	}

	else
		cout << "File cannot be opened." << endl;
}

//deserialize stream objects and create cities and days
//hannah burgett is once again resuing code from her previously-mentioned lab
void City::Deserialize(istringstream& stream)
{
	string token;
	string date;
	string time;

	//get date from line
	getline(stream, token, ',');

	istringstream stream2(token);
	string token2;

	//check if date is in correct format
	//reformat if needed
	if (token[4] != '-')
	{
		getline(stream2, token2, '/');
		string month = token2;

		getline(stream2, token2, '/');
		string day = token2;

		getline(stream2, token2, '/');
		string year = token2;

		//add 0s for uniformality, if needed
		if (day.size() == 1)
			day = "0" + day;
		if (month.size() == 1)
			month = "0" + month;

		//reformat to "YYYY-MM-DD-00:00"
		//date = year + "-" + month + "-" + day + "-00:00";
		date = year + "-" + month + "-" + day;
		time = "00:00";

	}
	else
	{
		//reformat to "YYYY-MM-DD-TT:TT"
		getline(stream2, token2, 'T');
		date = token2;

		getline(stream2, token2, 'Z');
		time = token2;

	}
	//get air_temp from line
	getline(stream, token, ',');
	string air_temp = token;

	//get wind_speed from line
	getline(stream, token, ',');
	string wind_speed = token;

	//get precipitation from line
	getline(stream, token, ',');
	string precipitation = token;

	//create date object and append to hashmap
	AddDate(date, time, air_temp, wind_speed, precipitation);

}

void City::AddDate(string date, string time, string air_temp, string wind_speed, string precipitation)
{
	//check if date already exists
	/*if (dates.find(date) == dates.end())
	{
		//create new date object
		//and append to dates hashmap
		Date* newDate = new Date(date, stof(air_temp), stof(wind_speed), stof(precipitation));
		dates[date] = newDate;
	}*/
	Date* newDate = new Date(date + "-" +  time, stof(air_temp), stof(wind_speed), stof(precipitation));
	dates[date].push_back(newDate);
}

//for testing
/*void City::PrintMap()
{
	auto iter = dates.begin();

	for (; iter != dates.end(); ++iter)
		cout << iter->second->date << " " << iter->second->air_temp << " " << iter->second->wind_speed << " " << iter->second->precipitation << endl;
}*/

void City::PrintMap()
{
	auto iter = dates.begin();
	for (; iter != dates.end(); ++iter)
	{
		for (int i = 0; i < iter->second.size(); i++)
			cout << iter->second[i]->date << " " << iter->second[i]->air_temp << " " << iter->second[i]->wind_speed << " " << iter->second[i]->precipitation << endl;
	}
}

Date City::averageData(const vector<Date*>& date_) {
	float averageTemp = 0.0f;
	float averageWindSpeed = 0.0f;
	float averagePrecipitation = 0.0f;
	int totalHours = date_.size();
	//For every element in our 'date' vector (every hour) add it's value to the average
	for (const auto& data : date_) { 
        averageTemp += data->air_temp;
        averageWindSpeed += data->wind_speed;
        averagePrecipitation += data->precipitation;
    }
	//Returns the first hour's name, but an averaged float for all other data
	return Date(date_[0]->date, averageTemp / totalHours, averageWindSpeed / totalHours, averagePrecipitation / totalHours); 
}