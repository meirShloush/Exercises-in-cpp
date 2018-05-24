#include "stdafx.h"

#include<iostream>
#include<math.h>

using namespace std;

struct line
{
	size_t line_number;
	size_t number_of_stations;
	size_t duration_of_travel;
};

struct buses
{
	line **linesArr;
	size_t length;
};

/*return locauion of line number if found, else return -1*/
size_t search(buses *busesArr, size_t line_number)
{
	size_t i = 0;

	for (i = 0; (i < busesArr->length) && (line_number > busesArr->linesArr[i]->line_number); i++);

	if (i == busesArr->length)
	{
		return -1;
	}

	return i;
}

/* increase the newBuses in 1, and puts the new line in place in numerical order */
void addLine(buses *busesArr, size_t line_number, size_t number_of_stations, size_t duration_of_travel)
{
	line **newBuses = new line*[(busesArr->length) + 1];

	line *newLine = new line;
	newLine->line_number = line_number;
	newLine->number_of_stations = number_of_stations;
	newLine->duration_of_travel = duration_of_travel;

	size_t location = search(busesArr, line_number);
	if (location == -1)
	{
		location = busesArr->length;
	}

	memcpy(newBuses, busesArr->linesArr, location * sizeof(line *));
	newBuses[location] = newLine;
	memcpy(&newBuses[location + 1], &busesArr->linesArr[location], (busesArr->length - location) * sizeof(line *));

	delete busesArr->linesArr;

	busesArr->linesArr = newBuses;
	busesArr->length += 1;
}

int deleteLine(buses *busesArr, size_t line_number)
{
	line **newBuses = new line*[(busesArr->length) - 1];

	size_t location = search(busesArr, line_number);
	if (-1 == location)
	{
		return -1;
	}

	delete busesArr->linesArr[location];

	memcpy(newBuses, busesArr->linesArr, location * sizeof(line *));
	memcpy(&newBuses[location], &busesArr->linesArr[location + 1], (busesArr->length - location) * sizeof(line *));

	delete busesArr->linesArr;

	busesArr->linesArr = newBuses;
	busesArr->length -= 1;

	return 1;
}

void print(const buses busesArr)
{
	for (size_t i = 0; i < busesArr.length; i++)
	{
		cout << "line number: " << busesArr.linesArr[i]->line_number
			<< ", number of stations: " << busesArr.linesArr[i]->number_of_stations
			<< ", duration of travel: " << busesArr.linesArr[i]->duration_of_travel << endl;
	}
	cout << endl;
}

/* return average duration of travel */
double averageTravel(const buses busesArr)
{
	double sum = 0;

	for (size_t i = 0; i < busesArr.length; i++)
	{
		sum += busesArr.linesArr[i]->duration_of_travel;
	}

	return sum / busesArr.length;
}

/* return average number of stations */
int averageStops(const buses busesArr)
{
	double sum = 0;
	for (size_t i = 0; i < busesArr.length; i++)
	{
		sum += busesArr.linesArr[i]->number_of_stations;
	}
	return round(sum / busesArr.length);
}

/* return the shortest travel */
size_t shortest(const buses busesArr)
{
	if (busesArr.length == 0)
	{
		return -1;
	}
	size_t min = busesArr.linesArr[0]->duration_of_travel;

	for (size_t i = 1; i < busesArr.length; i++)
	{
		if (busesArr.linesArr[i]->duration_of_travel < min)
		{
			min = busesArr.linesArr[i]->duration_of_travel;
		}
	}
	return min;
}


int main()
{
	buses busesArr;
	line **linesArr = new line*[1];
	busesArr.linesArr = linesArr;
	busesArr.length = 0;

	addLine(&busesArr, 2, 12, 24);
	addLine(&busesArr, 4, 14, 28);
	addLine(&busesArr, 10, 20, 40);
	addLine(&busesArr, 6, 16, 32);
	addLine(&busesArr, 8, 18, 36);
	addLine(&busesArr, 12, 24, 48);
	addLine(&busesArr, 3, 13, 26);
	addLine(&busesArr, 1, 11, 22);

	print(busesArr);

	cout << "averageTravel: " << averageTravel(busesArr) << endl
		<< "averageStops: " << averageStops(busesArr) << endl
		<< "shortest: " << shortest(busesArr) << endl << endl;

	deleteLine(&busesArr, 8);
	deleteLine(&busesArr, 1);
	deleteLine(&busesArr, 30);
	deleteLine(&busesArr, 12);

	print(busesArr);

	cout << "averageTravel: " << averageTravel(busesArr) << endl
		<< "averageStops: " << averageStops(busesArr) << endl
		<< "shortest: " << shortest(busesArr) << endl << endl;

	return 0;
}
