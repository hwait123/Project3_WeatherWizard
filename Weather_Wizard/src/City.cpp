#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "City.h"

using namespace std;
using namespace std::chrono;

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
	Date* newDate = new Date(date + "-" +  time, stof(air_temp), stof(wind_speed), stof(precipitation));
	dates[date].push_back(newDate);
}

Date* City::averageData(const vector<Date*>& date_) {
	float sumTemp = 0.0f;
	float sumWindSpeed = 0.0f;
	float sumPrecipitation = 0.0f;
	int totalHours = date_.size();
	//For every element in our 'date' vector (every hour) add it's value to the average
	for (const auto& data : date_) { 
        sumTemp += data->air_temp;
        sumWindSpeed += data->wind_speed;
        sumPrecipitation += data->precipitation;
    }
	//Returns the first hour's name, but an averaged float for all other data
    Date* newPtr = new Date(date_[0]->date, sumTemp / totalHours, sumWindSpeed / totalHours, sumPrecipitation / totalHours);
	return newPtr;
}

pair <Date*, duration<double, micro>> City::findHighestTemperature(map<string, Date*>& dates_) {
    auto start = high_resolution_clock::now();

    if (dates_.empty()) {
        throw invalid_argument("The map is empty.");
    }

    vector<Date*> allAverages;
    
    LoadAveragesVec(allAverages, dates_);

    Date* highestTempDate = GetResultStdSort(make_pair("air_temp", "high"), allAverages);

    auto end = high_resolution_clock::now();
    duration<double, micro> elapsed = end - start;
    //cout << "Time taken to run the function: " << elapsed.count() << " seconds" << endl;

    return make_pair(highestTempDate, elapsed);
}

pair <Date*, duration<double, micro>> City::findLowestTemperature(map<string, Date*>& dates_) {
    auto start = high_resolution_clock::now();

    if (dates_.empty()) {
        throw invalid_argument("The map is empty.");
    }

    vector<Date*> allAverages;
    
    LoadAveragesVec(allAverages, dates_);

    Date* lowestTempDate = GetResultStdSort(make_pair("air_temp", "low"), allAverages);
    
    auto end = high_resolution_clock::now();
    duration<double, micro> elapsed = end - start;
    //cout << "Time taken to run the function: " << elapsed.count() << " seconds" << endl;

    return make_pair(lowestTempDate, elapsed);
}

pair <Date*, duration<double, micro>> City::findMaxWindSpeed(map<string, Date*>& dates_) {
    auto start = high_resolution_clock::now();

    if (dates_.empty()) {
        throw invalid_argument("The map is empty.");
    }

    vector<Date*> allAverages;
    
    LoadAveragesVec(allAverages, dates_);

    Date* maxWindSpeedDate = GetResultStdSort(make_pair("wind_speed", "high"), allAverages);
    

    auto end = high_resolution_clock::now();
    duration<double, micro> elapsed = end - start;
    //out << "Time taken to run the function: " << elapsed.count() << " seconds" << endl;

    return make_pair(maxWindSpeedDate, elapsed);
}

pair <Date*, duration<double, micro>> City::findMaxPrecipitation(map<string, Date*>& dates_) {
    auto start = high_resolution_clock::now();

    if (dates_.empty()) {
        throw invalid_argument("The map is empty.");
    }

    vector<Date*> allAverages;
    
    LoadAveragesVec(allAverages, dates_);

    Date* maxPrecipitationDate = GetResultStdSort(make_pair("precipitation", "high"), allAverages);

    auto end = high_resolution_clock::now();
    duration<double, micro> elapsed = end - start;
    //cout << "Time taken to run the function: " << elapsed.count() << " seconds" << endl;

    return make_pair(maxPrecipitationDate, elapsed);
}

int City::dateToInt(const string& date) {
    return stoi(date.substr(0, 4)) * 10000 + stoi(date.substr(5, 2)) * 100 + stoi(date.substr(8, 2));
}

/*map<string, vector<Date*>> City::assembleMapBetweenDates(map<string, vector<Date*>>& dates, const string& startDate, const string& endDate) {
/*map<string, vector<Date*>> City::assembleMapBetweenDates(map<string, vector<Date*>>& dates, const string& startDate, const string& endDate) {
    int start = dateToInt(startDate);
    int end = dateToInt(endDate);

    if (start > end) {
        throw invalid_argument("Start date must be earlier than or equal to end date.");
    }

    map<string, vector<Date*>> newMap;
    for (auto& entry : dates) {
        int currentDate = dateToInt(entry.first);
        if (currentDate >= start && currentDate <= end) {
            newMap[entry.first] = entry.second;
        }
    }

    return newMap; 
    
}*/

//adjusted function to accept an empty map as input and load map with values within range,
//because main.cpp will not have access to the object's map
void City::assembleMapBetweenDates(map<string, Date*>& newMap, const string& startDate, const string& endDate) {
    int start = dateToInt(startDate);
    int end = dateToInt(endDate);

    if (start > end) {
        throw invalid_argument("Start date must be earlier than or equal to end date.");
    }

    for (auto& entry : dates) {
        int currentDate = dateToInt(entry.first);
        if (currentDate >= start && currentDate <= end) {
            newMap[entry.first] = averageData(entry.second);
        }
    }

}

/********** Can't do insertion sort, so will have to change *********************/
void insertionSort(vector<Date*>& dates) {
    for (size_t i = 1; i < dates.size(); ++i) {
        Date* key = dates[i];
        int j = i - 1;
        while (j >= 0 && dates[j]->air_temp > key->air_temp) {
            dates[j + 1] = dates[j];
            --j;
        }
        dates[j + 1] = key;
    }
}
/********************************************************************************/

void City::LoadAveragesVec(vector<Date*>& allAverages, map<string, Date*>& dates_)
{
    for (auto& entry : dates_) 
        allAverages.push_back(entry.second);

    if (allAverages.empty()) {
        throw runtime_error("No valid Date objects found.");
    }
}

Date* City::GetResultStdSort(pair <string, string> sortBasedOn, vector<Date*>& allAverages)
{
    //sort in decending order
    if (sortBasedOn.first == "precipitation")
    {
        sort(allAverages.begin(), allAverages.end(), [](Date* a, Date* b) {
            return a->precipitation > b->precipitation;
        });
    }
    else if (sortBasedOn.first == "air_temp")
    {
        sort(allAverages.begin(), allAverages.end(), [](Date* a, Date* b) {
            return a->air_temp > b->air_temp;
        });
    }
    else if (sortBasedOn.first == "wind_speed")
    {
        sort(allAverages.begin(), allAverages.end(), [](Date* a, Date* b) {
            return a->wind_speed > b->wind_speed;
        });
    }

    //if looking for high value, return front of vector
    if (sortBasedOn.second == "high")
        return allAverages.front();
    //if looking for low value, return end of vector
    if (sortBasedOn.second == "low")
        return allAverages[allAverages.size() - 1];
}


vector<Date*> City::mergeSort(vector<Date*> dates, string sortBasedOn) {
    
    //if vector holds only one date, no need to sort
    if (dates.size() <= 1)
        return dates;
    int mid = dates.size() / 2;
    vector<Date*> left = mergeSort(slice(dates, 0, (mid - 1)), sortBasedOn);
    vector<Date*> right = mergeSort(slice(dates, mid, (dates.size() - 1)), sortBasedOn);
    return merge(left, right, sortBasedOn);

}

vector<Date*> City::slice(vector<Date*> dates, int start, int end) {

    vector<Date*> slicedVec;

    for(int i = start; i <= end; i++)
        slicedVec.push_back(dates[i]);

    return slicedVec;
}

vector<Date*> City::merge(vector<Date*> left, vector<Date*> right, string sortBasedOn){
    
    vector<Date*> res;
    
    while (left.size() != 0 && right.size() != 0){
        if (sortBasedOn == "air_temp"){
            if (left[0]->air_temp <= right[0]->air_temp){
                res.push_back(left[0]);
                left = slice(left, 1, left.size() - 1);
            }
            else { 
                res.push_back(right[0]);
                right = slice(right, 1, right.size() - 1);
            }
            
        }
    }

    for (int i = 0; i < left.size(); i++)
        res.push_back(left[i]);
    for (int j = 0; j < right.size(); j++)
        res.push_back(right[j]);

    return res;
}