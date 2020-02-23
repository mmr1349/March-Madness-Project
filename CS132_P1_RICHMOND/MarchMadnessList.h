#ifndef _MARCH_MADNESS_LIST_H
#define _MARCH_MADNESS_LIST_H
#include <list>
#include <iostream>
#include <fstream>
#include "TeamData.h"

/////////////////////////////////////////////////////////////////////////////////////////
//Programmer:	John Marcus Richmond
//Instructor:	Professor Streller
//Course:		CS 132
//Date:			4/1/19
//Class Name:	marchMadnessList
//Class File:	MarchMadnessList.h
//Structure:	Reads data in from a .tsv file and then stores each teams data in the 
//				TeamData struct and all of the different teams in a STL list. Contains
//				several functions to modify the list and then export that list to a .tsv
//				file that can then be re-read by the program and modified more.
//Purpose:		The purpose of the this class is to store and sort all the inforomation
//				to make a march madness list.
//Other Classes Used:	list, iostream
//Structs Used:			TeamData
//Data Memebers:		STL list<TeamData> teamList   This is the list that holds all 
//						information of the teams utilizing the TeamData struct. It is a STL
//						list and is sorted, modified, etc using the STL list functions.
//Member Functions:		marchMadnessList() default constructor
//						marchMadnessList(const marchMadnessList&) copy constructor
//						int listSize() returns the size of the teamList
//						void sortList(bool) sorts the list and updates the previous 
//						position if stated by the bool
//						void printTeams(int howMany) print as many teams as specified by 
//						the argument how many to the console.
//						void editTeam(char[25]) edit the team whose name is supplied by 
//						the user.
//						void removeTeam(char[25]) remove a team from the STL teamList 
//						specififed by name.
//						void addTeam(const TeamData& newEntry) add a new team struct to 
//						the list.
//						void outputData(ofstream& output) output our STL list data into 
//						the output stream specified.
//						TeamData* searchList(char[25]) search the STL teamList for team
//						with the name specified.
//						~marchMadnessList() destructor for the class
/////////////////////////////////////////////////////////////////////////////////////////
class marchMadnessList {
private:
	list<TeamData> teamList; //STL list of the teams
public:
	marchMadnessList(); //default constructor
	marchMadnessList(const marchMadnessList&); //copy constructor for the class
	int listSize(); //returns the size of the list
	void sortList(bool); //sorts the list and updates the previous position if stated
	void printTeams(int howMany); //print a certain amount of teams
	void editTeam(char[25]); //edit a team specified by name
	void removeTeam(char[25]); //remove a team specififed by name
	void addTeam(const TeamData& newEntry); //add a new team struct
	void outputData(ofstream& output); //output our STL list data into an output stream
	TeamData* searchList(char[25]); //search the list for name
	~marchMadnessList(); //destructor for the class
};

#endif
