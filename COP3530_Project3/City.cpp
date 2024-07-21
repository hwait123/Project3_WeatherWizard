#include <sstream>
#include <filesystem>
#include <iostream>
#include <system_error>

#include "City.h"

using namespace std;

City::City(string& cityName)
{
	this->cityName = cityName;
}

//read csv files annd create city objects
//hannah burgett borrowed some code from her COP3503 lab7
void City::ReadFromCSVFile(string& filepath)
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

	//get date from line
	getline(stream, token, ',');

	//check if date is in correct format
	//reformat if needed
	if (string[4] != '-')
	{
		istringstream stream2(token);

		string token2;
		string day;
		string month;
		string year;

		getline(stream2, token2, '/');
		string day = token2;

		getline(stream2, token2, '/');
		string month = token2;

		getline(stream2, token2, '/');
		string year = token2;

		if (day.size() == 1)
			day = "0" + day;

		if (month.size() == 1)
			month = "0" + month;

		string date = year + "-" + month + "-" + day + "T00:00Z";
	}
	else
		string date = token;

	//get air_temp from line
	getline(stream, token, ',');
	string air_temp = token;

	//get wind_speed from line
	getline(stream, token, ',');
	string wind_speed = token;

	//get precipitation from line
	getline(stream, token, ',');
	string precipitation = token;
}

void City::AddDate(string date, string air_temp, string wind_speed, string precipitation)
{
	//check if date already exists
	if (dates.find(date) == dates.end())
	{
		//create new date object
		//and append to dates hashmap
		Date* newDate = Date(date, stof(air_temp), stof(wind_speed), stof(precipitation));
		dates[date] = newDate;
	}
}
