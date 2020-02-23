#ifndef _LAST_POSITION_H_
#define _LAST_POSITION_H_
#include <iostream>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////
//Programmer:	John Marcus Richmond
//Instructor:	Professor Streller
//Course:		CS 132
//Date:			4/1/19
//Struct Name:	LastPosition
//Struct File:	LastPosition.h
//Structure:	Just a int to store the position and a const char to store a -
//				with a couple overloaded operators to make the struct usable.
//Purpose:		Struct to store the some teams position last week. If they weren't
//				in march madness last week the Struct will return a - instead of a
//				number since they had no position last week.
//Other Classes Used:	iostream
//Structs Used:			None
//Data Elements:		int position  The teams position last week. 0 if they weren't
//						in the tournament last week.
//						const char dash   A const char that holds the dash character
//						we display this if the position is 0 meaning they weren't
//						a part of march madness last week
//Element Functions:	friend istream& operator >> (istream& input, LastPosition& data)
//						friend ostream& operator << (ostream& output, const LastPosition& data)
/////////////////////////////////////////////////////////////////////////////////////////
struct LastPosition {
	int position = 0; //The position of the team last week
	const char dash = '-'; //Dash character const used if the last position didn't exist


	/////////////////////////////////////////////////////////////////////////////////////////
	//Function Name:	operator >>()
	//Purpose:			Overloads the stream extraction operator so we can extract the 
	//					teams position last week.
	//Parameters:		istream& input    The input stream we are extracting from
	//					LastPosition & data   The LastPosition we are placeing the data into
	//Return Value:		istream&
	//Data Elements Accessed:	data.position
	//Data Elements Modified:	data.position
	//Non-Local Variables Used:	istream& input, LastPosition& data
	//Functions Called:	istream.peek(), istream.get()
	/////////////////////////////////////////////////////////////////////////////////////////
	friend istream& operator >> (istream& input, LastPosition& data) {
		input >> ws; //Clear white space
		if (input.peek() == '-') { //If we peek a dash
			data.position = 0; //Set our position to 0
			input.get(); //Get rid of the dash from the stream
		} else { //If its anything else
			input >> data.position; //its not a dash its an int put that into our position
		}
		return input; //return the input stream
	}


	/////////////////////////////////////////////////////////////////////////////////////////
	//Function Name:	operator <<()
	//Purpose:			Overloads the stream insertion operator so we can output the 
	//					teams position last week.
	//Parameters:		istream& output   The output stream we are inserting into
	//					const LastPosition & data   The LastPosition outputting from
	//Return Value:		ostream&
	//Data Elements Accessed:	data.position
	//Data Elements Modified:	data.position
	//Non-Local Variables Used:	istream& input, const LastPosition& data
	//Functions Called:	None
	/////////////////////////////////////////////////////////////////////////////////////////
	friend ostream& operator << (ostream& output, const LastPosition& data) {
		if (data.position > 0) { //if the position is greater than 0
			output << data.position; //Output the position
		} else { //Otherwise it doesn't have a position
			output << data.dash; //Output a dash
		}
		return output; //return the output stream
	}
};

#endif
