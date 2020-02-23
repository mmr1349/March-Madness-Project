#ifndef _TEAM_DATA
#define _TEAM_DATA
#include <iostream>
#include <iomanip>
#include "LastPosition.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////
//Programmer:	John Marcus Richmond
//Instructor:	Professor Streller
//Course:		CS 132
//Date:			4/1/19
//Struct Name:	LastPosition
//Struct File:	LastPosition.h
//Structure:	Struct with a couple 
//Purpose:		Struct to store the all the pertinant information about a basketball team
//Other Classes Used:	iostream, iomanip
//Structs Used:			LastPosition
//Data Elements:		char name[25]    C-string that holds the name of the team
//						int wins   Number of wins the team has
//						int losses  Number of losses the team has
//						int position   Teams curent position
//						int points    The number of points the team has
//						LastPosition lastPosition   The teams position last week
//Elements Functions:	friend istream& operator >> (istream& input, LastPosition& data)
//						friend ostream& operator << (ostream& output, const LastPosition& data)
//						int operator < (const TeamData& right)
//						bool operator == (const TeamData& right)
/////////////////////////////////////////////////////////////////////////////////////////
struct TeamData {
	char name[25];
	int wins, losses, position, points;
	LastPosition lastPosition;


	/////////////////////////////////////////////////////////////////////////////////////////
	//Function Name:	operator >>()
	//Purpose:			Overloads the stream extraction operator so we can extract all the
	//					teams information from a properly formatted .tsv file.
	//Parameters:		istream& input    The input stream we are extracting from
	//					TeamData& data   The TeamData we are extracting into
	//Return Value:		istream&
	//Data Elements Accessed:	data.name, data.wins, data.losses, data.position, data.points
	//							data.lastPosition
	//Data Elements Modified:	data.name, data.wins, data.losses, data.position, data.points
	//							data.lastPosition
	//Non-Local Variables Used:	istream& input, TeamData& data
	//Functions Called:	istream.get()
	/////////////////////////////////////////////////////////////////////////////////////////
	friend istream& operator >> (istream& input, TeamData& data) {
		input >> data.position >> ws; //Clear white space
		input.get(data.name, 24, '\t'); //Get the name only 24 characters or until we find a tab
		input >> data.wins; //Get the amount of wins
		input.get(); //Remove the dash from the data
		input >> data.losses; //Get the losses
		input >> data.points; //Get the points
		input >> data.lastPosition; //Get there last position
		return input; //Return the input stream
	}


	/////////////////////////////////////////////////////////////////////////////////////////
	//Function Name:	operator >>()
	//Purpose:			Overloads the stream insertion operator so we can insert all the
	//					teams information into an output stream.
	//Parameters:		ostream& output    The output stream we are inserting into
	//					TeamData& data   The TeamData we are using to insert into the output
	//									 stream
	//Return Value:		ostream&
	//Data Elements Accessed:	data.name, data.wins, data.losses, data.position, data.points
	//							data.lastPosition
	//Data Elements Modified:	None
	//Non-Local Variables Used:	ostream& output, TeamData& data
	//Functions Called:	None
	/////////////////////////////////////////////////////////////////////////////////////////
	friend ostream& operator << (ostream& output, TeamData& data) {
		output << left;
		output << setw(5) << data.position
			<< setw(20) << data.name
			<< setw(8) << data.points
			<< data.wins << '-' 
			<< data.losses << '\t'
			<< right << setw(6) << data.lastPosition << endl;
		return output;
	}


	/////////////////////////////////////////////////////////////////////////////////////////
	//Function Name:	operator < ()
	//Purpose:			Overloads the less than operator we use so we can sort a list of
	//					TeamData.
	//Parameters:		const TeamData& right    The TeamData on the right of the <
	//Return Value:		int
	//Data Elements Accessed:	points
	//Data Elements Modified:	None
	//Non-Local Variables Used:	TeamData& right
	//Functions Called:	None
	/////////////////////////////////////////////////////////////////////////////////////////
	int operator < (const TeamData& right) {
		if (this->points > right.points) { //if the this's points are greater
			return 1; //return 1
		}
		return 0; //otherwise return 0
	}


	/////////////////////////////////////////////////////////////////////////////////////////
	//Function Name:	operator == ()
	//Purpose:			Overloads the comparison operator so we can compare two teams based
	//					on there name.
	//Parameters:		const TeamData& right    The TeamData on the right of the ==
	//Return Value:		bool
	//Data Elements Accessed:	name
	//Data Elements Modified:	None
	//Non-Local Variables Used:	TeamData& right
	//Functions Called:	strcmp()
	/////////////////////////////////////////////////////////////////////////////////////////
	bool operator == (const TeamData& right) {
		return !strcmp(this->name, right.name); //returns the opposite of the strcmp for the
												//name on the left an right since if they are equal
												// it will return 0 opposite of that will be 1 so true
	}
};

#endif
