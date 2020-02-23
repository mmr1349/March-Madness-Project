#ifndef _MARCH_MADNESS_LIST_CPP
#define _MARCH_MADNESS_LIST_CPP
#include "MarchMadnessList.h"



/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	marchMadnessList()
//Purpose:			Default constructor for the MarchMadness class
//Parameters:		None
//Return Value:		None
//Data Members Accessed:	None
//Data Memebers Modified:	None
//Non-Local Variables Used:	None
//Functions Called:	None
/////////////////////////////////////////////////////////////////////////////////////////
marchMadnessList::marchMadnessList() {
	//We don't need to do anything so don't
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	marchMadnessList(const marchMadnessList)
//Purpose:			Copy constructor for the MarchMadness class
//Parameters:		const marchMadnessList& other    the list we are copying from
//Return Value:		None
//Data Members Accessed:	STL list<TeamData> teamList, STL list<TeamData> other
//Data Memebers Modified:	STL list<TeamData> teamList
//Non-Local Variables Used:	other
//Functions Called:	None
/////////////////////////////////////////////////////////////////////////////////////////
marchMadnessList::marchMadnessList(const marchMadnessList& other) {
	this->teamList = other.teamList; //The only data member we have is the list copy it over
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	addTeam(const TeamData& newEntry)
//Purpose:			Adds a new Team to the STL teamList
//Parameters:		const TeamData& newEntry   the new team we are adding
//Return Value:		void
//Data Members Accessed:	STL list<TeamData> teamList
//Data Memebers Modified:	STL list<TeamData> teamList
//Non-Local Variables Used:	newEntry
//Functions Called:	STL list.push_front()
/////////////////////////////////////////////////////////////////////////////////////////
void marchMadnessList::addTeam(const TeamData& newEntry) {
	if (newEntry.points > 0) { //if it doesn't have any points don't even add it
		this->teamList.push_front(newEntry); //Add it to the STL teamList
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	removeTeam(char[25] name)
//Purpose:			Searches for and if it finds it removes a team from the STL teamList
//Parameters:		char name[25]   the name of the team we are searching for
//Return Value:		void
//Data Members Accessed:	STL list<TeamData> teamList
//Data Memebers Modified:	STL list<TeamData> teamList
//Non-Local Variables Used:	None
//Functions Called:	STL list.remove(), marchMadnessList sortList()
/////////////////////////////////////////////////////////////////////////////////////////
void marchMadnessList::removeTeam(char name[25]) {
	TeamData* toRemove = this->searchList(name); //Find the specific item the user wants to remove
	if (toRemove) { //if we found it
		this->teamList.remove(*toRemove); //remove it
		cout << "Removed " << name << endl; //Tell the user it was removed
	} else { //If we didn't find that team
		cout << "Team doesn't exist\n"; //Tell the user that team doesn't exist
	}
	this->sortList(true); //Sort the list updating the standings
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	editTeam(char[25] name)
//Purpose:			Searches for and if it finds it allows the user to modiefy the data 
//					of the team found in the STL teamList
//Parameters:		char name[25]   the name of the team we are searching for
//Return Value:		void
//Data Members Accessed:	STL list<TeamData> teamList
//Data Memebers Modified:	STL list<TeamData> teamList
//Non-Local Variables Used:	None
//Functions Called:	iostream.getLine(), marchMadnessList sortList()
/////////////////////////////////////////////////////////////////////////////////////////
void marchMadnessList::editTeam(char name[25]) {
	TeamData* toEdit = this->searchList(name); //Search the list for the team
	if (toEdit) { //If we find that team
		cout << "New Name: "; //Ask the user for a new name
		cin.getline(toEdit->name, 25); //Change the teams name to the new one
		cout << "New Wins: "; //Ask the user for the new wins
		cin >> toEdit->wins; //Change the teams wins to the user input
		cout << "New Losses: "; //Ask the user for new losses
		cin >> toEdit->losses; //Change the teams losses to the inputed losses
		cout << "New Points: "; //Ask user for new points
		cin >> toEdit->points; //Input into the teams points
		cout << endl; //Make a new line for astethetic sake
		this->sortList(true); //Sort the list updating the standings
	} else { //else we didn't find the team
		cout << "Team " << name << " Doesn't exist.\n"; //Tell the user no such team exists
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	searchList(char[25] name)
//Purpose:			Searches the STL list teamList for the team with name name
//Parameters:		char name[25]   the name of the team we are searching for
//Return Value:		TeamData*   a pointer to the team we are searching for
//Data Members Accessed:	STL list<TeamData> teamList
//Data Memebers Modified:	None
//Non-Local Variables Used:	None
//Functions Called: STL list.begin(), STL list.end()
/////////////////////////////////////////////////////////////////////////////////////////
TeamData* marchMadnessList::searchList(char name[25]) {
	//Iterate over the list using an iterator
	for (list<TeamData>::iterator i = this->teamList.begin(); i != this->teamList.end(); ++i) {
		if (!strcmp(i->name, name)) {//If the strcmp return 0 they are a match
			TeamData* team = &(*i); //Make a temporary pointer to that team from the iterator
			return team; //return that pointer
		}
	}
	return NULL; //If we get here just send back a NULL pointer
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	sorthList(bool updatePrevPos)
//Purpose:			Sorts the STL list teamList using the STL list.sort() function
//					updates the previous standings of the teams if specified by the bool
//					argument.
//Parameters:		bool updatePrevPos    should we update the teams previous positions
//					or not?
//Return Value:		void
//Data Members Accessed:	STL list<TeamData> teamList
//Data Memebers Modified:	STL list<TeamData> teamList
//Non-Local Variables Used:	None
//Functions Called: STL list.sort(), STL list.begin(), STL list.end(), STL list.erase()
/////////////////////////////////////////////////////////////////////////////////////////
void marchMadnessList::sortList(bool updatePrevPos) {
	this->teamList.sort(); //sort the list the stl list sort
	int i = 1; //int i counter used for position in the list
	list<TeamData>::iterator t = this->teamList.begin(); //Create the iterator
	while (t != this->teamList.end()) { //Loop until we reach the end of the file
		if (t->points > 0) { //if the team has points
			if (updatePrevPos) { //if our update previous position bool is true update our previous position
				t->lastPosition.position = t->position; //Make the previous equal to our current position
			}
			t->position = i; //Set its position to i
			i++; //increment counter i
			++t; //increment iterator t
		} else { //if they don't have points
			t = this->teamList.erase(t); //Erase them from the list
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	printTeams(int howMany)
//Purpose:			Prints the data stored in the STL list teamList to the console.
//					only prints as many teams as specified by the parameter.
//Parameters:		int howMany   how many items to print
//Return Value:		void
//Data Members Accessed:	STL list<TeamData> teamList
//Data Memebers Modified:	None
//Non-Local Variables Used:	None
//Functions Called: STL list.begin(), STL list.end()
/////////////////////////////////////////////////////////////////////////////////////////
void marchMadnessList::printTeams(int howMany) {
	int j = 0; //counter used to control how many items we display at a time
	//Output a little header so you know hat each column means
	cout << left << setw(5) << "Rank" << setw(20) << "School" << setw(8) 
		<< "Points" << setw(8) << "Record" << setw(8) << "Previous\n\n";
	//Use a for loop iterartor to loop over the list
	for (list<TeamData>::iterator i = this->teamList.begin(); i != this->teamList.end(); ++i, j++) {
		if (j < howMany) { //if we haven't outputted more than we should
			cout << *i << endl; //output the current item
		} else { //if we've reached the limit
			return; //Exit the function
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	outputData(ofstream& output)
//Purpose:			Outputs all the data sored in the TeamData structs inside out STL list
//					teamList into a .tsv that can be re-read and used by our program.
//Parameters:		ofstream& output    the output stream we want to output into
//Return Value:		void
//Data Members Accessed:	STL list<TeamData> teamList
//Data Memebers Modified:	None
//Non-Local Variables Used:	None
//Functions Called: STL list.begin(), STL list.end() ofstream.close()
/////////////////////////////////////////////////////////////////////////////////////////
void marchMadnessList::outputData(ofstream& output) {
	//loop over our list using a for loop iterator
	for (list<TeamData>::iterator i = this->teamList.begin(); i != this->teamList.end(); ++i) {
		//ourput the item we are on into the output stream provided
		output << i->position << '\t' << i->name << '\t' << i->wins << '-' << i->losses << 
			'\t' << i->points << '\t' << i->lastPosition << '\t';
	}
	output.close(); //close the stream at the end
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	listSize()
//Purpose:			returns the size of our STL list teamList
//Parameters:		none
//Return Value:		void
//Data Members Accessed:	STL list<TeamData> teamList
//Data Memebers Modified:	None
//Non-Local Variables Used:	None
//Functions Called: STL list.sze()
/////////////////////////////////////////////////////////////////////////////////////////
int marchMadnessList::listSize() {
	return this->teamList.size(); //return the team list size
}


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	~marchMadnessList()
//Purpose:			Default destructor for the class. Just deletes the STL list teamList
//Parameters:		none
//Return Value:		none
//Data Members Accessed:	STL list<TeamData> teamList
//Data Memebers Modified:	STL list<TeamData> teamList
//Non-Local Variables Used:	None
//Functions Called: STL list.clear()
/////////////////////////////////////////////////////////////////////////////////////////
marchMadnessList::~marchMadnessList() {
	this->teamList.clear(); //Erase the entire list
}

#endif