/////////////////////////////////////////////////////////////////////////////////////////
//Programmer:	John Marcus Richmond
//Date:			4/1/19
//Program Name:	Project 2 Driver
//Program File:	cs132_P2_Driver.cpp
//Input Files:	A specially formatted .tsv file with data in this order int position,
//				string team name, int wins-int losses, int points, int position last week
//				or a -, and then the next team. All the commas mean a tab but that would
//				be slightly wierd to read and understand so i'm stating that here.
//Output Files:	Outputs a file in the same format as the input that can be read by this
//				program.
//Modules Used: fstream, iostream, TeamData, MarchMadnessList
//Purpose:		That creates a list of teams from a specially formatted .tsv file and
//				then stores that data inside an instance of the MarchMadnessList class.
//				You can then view and modify the list and then export it into another
//				similairly formatted .tsv file that then be read and used by this program.
/////////////////////////////////////////////////////////////////////////////////////////


#include <fstream>
#include <iostream>
#include "TeamData.h"
#include "MarchMadnessList.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////
//Function Name:	main
//Purpose:			Main function of the program were everything comes together.
//					Asks the user for the path to the input file, then it reads from
//					and tells the MarchMadnessList to construct a STL list from it.
//					Then gives a menu of options of what you would like to do to this list
//					ie add, remove, edit teams on the list. Then once you are done cahnging
//					the list it allows you to export it into a new file that can be opened
//					and used by this program.
//return value:		int
//Functions Called:	istream.open(),  MarchMadnessList.addTeam(), MarchMadnessList.sortList()
//					MarchMadnessList.printTeams(), cin.getLine(),
//					MarchMadnessList.editTeam(), MarchMadnessList.removeTeam()
//					istream.close(), MarchMadnessList.listSize(), ostream.open(), 
//					MarchMadnessList.outputData(), cin.clear(), cin.ignore()
/////////////////////////////////////////////////////////////////////////////////////////
int main() {
	//Variable Declerations
	int choice = 0; //User choice integer
	ifstream input; //Input stream we are reading data from
	char path[150]; //Path to input file c-string
	marchMadnessList list; //Our march madness list
	TeamData temp; //Temp team data we use to add 


	cout << "Enter path to input file: "; //Ask user for file path
	cin >> path; //Input file path
	input.open(path); //Try to open said path
	if (input) { //If we can open it continue with the program
		cout << "File Opened.\n\n"; //Tell the user we opened the file
		while (input >> temp) { //Input our data till the input stream breaks
			list.addTeam(temp); //Add temp to our list
		}
		list.sortList(false); //Sort the list not updating the previous position

		//Do while loop of our program keeps running till the user chooses to exit
		do {
			//Options menu
			cout << "Chose an Option\n"
				<< "1 To Print Top 25\n"
				<< "2 To Edit a Team\n"
				<< "3 To Remove a Team\n"
				<< "4 To Add a Team\n"
				<< "5 To Print Entire List\n"
				<< "6 To Save and Exit\n"
				<< "7 To exit without saving\n";
			cin >> choice; //Input user choice

			switch (choice) //Switch over the choice 
			{
			case 1: { //if 1 print the top 25 teams
				list.printTeams(25); //print teams
				break;
			} case 2: { //if 2 edit some team
				char toEdit[25]; //char to store the new teams name
				cout << "Enter Team Name Max 24 letters: "; //Ask the user to enter the schools name
				cin >> ws; //Remove white space
				cin.getline(toEdit, 25); //Get the schools name
				list.editTeam(toEdit); //Tell the list to edit that team
				break;
			} case 3: { //if 3 remove team
				char toRemove[25]; //team name c-string
				cout << "Enter Team Name Max 24 Letters: "; //Ask user for school name
				cin >> ws; //Clear the whitespace
				cin.getline(toRemove, 25); //Get the school name
				list.removeTeam(toRemove); //Remove that school from the list
				break;
			} case 4: { //if 4 add a new team
				TeamData newTeam; //TeamData variable to store the new team
				newTeam.lastPosition.position = 0;
				cout << "Enter Name: "; //Ask user for name
				cin >> ws; //Clear white space
				cin.getline(newTeam.name, 25); //Get the name and store it in our variable
				cout << "Enter Wins: "; //Ask user for wins
				cin >> newTeam.wins; //Input wins
				cout << "Enter Losses: "; //Ask user for losses
				cin >> newTeam.losses; //Input Losses
				cout << "Enter Points: "; //Ask user for points
				cin >> newTeam.points; //Input points
				list.addTeam(newTeam); //Add the team to our list``
				list.sortList(true); //Sort the list updating previous positions
				break;
			} case 5: { //if 5 print all the teams in the list
				list.printTeams(list.listSize()); //Print all the teams
				break;
			} case 6: { //if 6 save and exit
				input.close(); //Close the input stream
				ofstream output; //Output stream we are storing our data in
				char fileName[50]; //C-string holding our save files name
				cout << "Enter name of file no spaces ended with '.tsv': "; //Ask user for save file name
				cin >> fileName; //Input the source files name
				output.open(fileName); //Create said file if it doesn't already exist
				list.outputData(output); //Output the data into the output stream
				cout << "Data saved in file " << fileName 
					<< " you can reopen that file with this program.\n\n"; //Tell the user what happened
				break;
			} case 7: { //if 7 quit without saving
				cout << "Quitting and not saving.\n\n"; //Inform the user what is happening
				cout << "Press enter to continue...\n"; //Tell the user what to do
				cin.clear(); //Clear the input stream
				cin.ignore(200, '\n'); //Ignore the input stream
				cin.get(); //Keep the program from just exiting by waiting for some input
				input.close(); //Close the input stream
				break;
			}default: {//Otherwise tell the user they did something wrong
				cin.clear(); //Clear the input just in case
				cin.ignore(200, '\n'); //Ignore the next bit or until a new line
				cout << "Invalid Choice Try Again.\n"; //Tell the user they messed up
				break;
			}
			}

			if (!cin) { //if the input stream is broken
				cin.clear(); //Clear the input stream just in case
				cin.ignore(300, '\n'); //Ignore the stream just in case the user entered something wierd
			}
		} while (choice != 6 && choice != 7); //Do while loop condition. As long as the don't 
											  //enter a 6 or 7 it will continue.
	} else { //Else they entered the wrong file path quit
		cout << "Invalid Path Quitting\n\n"; //Tell the user what they did wrong
		cout << "Press enter to continue...\n"; //Tell the user what to do
		cin.clear(); //Clear the input stream
		cin.ignore(200, '\n'); //Ignore the input stream
		cin.get(); //Keep the program from just exiting by waiting for some input
	}

	return 0;
}