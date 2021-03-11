// C++ Converter from (.csv to .sql) data only - Schultz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// This project reads in values stored from a .csv file and converts them into a .txt file
// for input into an already established/published database. 
// It will prompt the user to enter the name of the document/ path of the original .csv file
// and will output a .txt file that can be used to upload to a database later. 

// Follow instructions in notes


// *************************************************************************************************
//
// Pre PROGRAM NOTE:
//
// *************************************************************************************************

// Once you have insured that your spreadsheet/excell document has all the same columns as the desired table
// Reguardless of the order the columns are in as long as the content is the same. 
// We can begin.
// Make sure that the file is in (.csv) or Comma Seperated Values. you may have to SaveAs via excell to make this happen

// SUPER IMPORTANT can't skip !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// OK so now that it is in a .csv file 
// we can run this program which will prompt  you for the filepath.
// you can get that info from the folder it is saved in. 
// it will also ask you for the name of the file you want this particular spreadsheet to be saved into.
// for access later by the queiry/import function of the database.
// it will then convert the .csv info into logical valid INSERT INTO queiry statements that we can 'IMPORT" 


// *************************************************************************************************
//
//                                  Post program instructions
//
// *************************************************************************************************

// Once we have the (.txt) file it can be selected/imported just like a (.sql) file.
// Just go to import and on the sql script wizard go to select file
//      then browse to the file NOTE***** the folder selection option won't identify the .txt
//      as a valid source and therefore can't be used this way. 
//      So you have to select browse for single file. -    
//      change the default .sql file type ( bottom right corner above OPEN and CANCEL.)
//      change it to include ALL FILES select the INDIVIDUAL ( .txt) file you want to use
//      then click open. it will load it into the database. 
//
//      This will have to be repeated as we are only converting one ( .csv) file to ( .txt) 
//      formatted filE at a time. and will have to run this program multiple times (once per .csv file) 
//      
//      HOWEVER using this method we can convert the contents of ANY ( .csv) file into the proper format
//      into any table as long as the relationships are in order. 


// AUTHORS NOTE POST POST. TESTING NOW TO SEE IF IT ACTUALLY WORKS ON APUBISHED DATABASE.
// 


// Author: John Schultz
// 03/06/2021  
// Name : ".CSV to .txt converter in C++" by schultz. 
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// we will use parallel arrays to read in from the file and back out.
// our arrays will be dynamically allocated so we don't have to know the size from the beginning.
// we do this  by counting the number of items in the first line that way we know how many columns
// then save the first line partitioning into the columns info.
// we will use this info to insure that the proper info is placed in the correct element number for our formatting
// cool stuff man.
//


string whatFile(string);
int readInData(string fileName);

string Titles = "";	// global variables are bad I know i just wanted it to work. get off me :D

int main()//int argc, char*argv[])
{

	string fileName = "";

	fileName = whatFile(fileName);
	readInData(fileName);

}

// output formatting file
// takes in the arrays of titles and information to put into the new .txt file
//
void writeToFile(string columnNames[], string data[])
{
         
    cout << "Test 1" << endl;

}



// This function prompts and reads in a file name from the end user. 
//
string whatFile(string fileName)
{
	// requests the filename from the user 
	//
	cout << "What is the name of the file we will use?" << endl;
	cin >> fileName;

	// If the filename entered is empty reprompt user. 
	while (fileName.empty())
	{
		cout << endl;
		cout << "Please enter a valid File Name. " << endl;
		cin >> fileName;
		
	}
	return fileName;

}

// This function reads in the data from the file after testing the file to insure that it opens
// If not it re-prompts the user for a valid name
// Then once it opens successfully this function reads the file item by item and determins 
// if it is a valid data type in the proper range i.e numbers from 0-99 only. 
// Then this function calls one of 2 functions either to write the data based on its value
// to either the Queue or Stack. 
// 
int readInData(string fileName)
{
	int iteration = 0;
	int colsCount = 0;
	int rowCount = 0;
	string TABLE;

	vector<string> row;					// read the data into a string vector
	string line, word, temp;

	cout << "How many columns are there in this file?" << endl;
	cin >> colsCount;
	colsCount--;						//decrement by -1 to account for element 0 = 1.
	
	cout << "How many rows are there in this file? include the header row" << endl;
	cin >> rowCount;
	cin.ignore();
	cout << "What is the name of the TABLE you wish to enter this info in EXACTLY how you it is in the database.\n This will also be the name of the end file ex: TABLE.txt " << endl;
	getline(cin, TABLE) ;

	//string* columnNames;				//allocates space for  col names in dynamically array. 
	//columnNames = new string[colsCount];

	ifstream readCSV;					// Establish the input stream
	readCSV.open(fileName, ios::in);	// Opens the file
	int counter = 0;
		
	while (readCSV >> temp)				// this function reads in all data of file into word
										// it ignores the title line and continues till the end.
	{
		row.clear();
		
		getline(readCSV, line);
		
		while (getline(readCSV, word, ','))
		{
			counter++;
			row.push_back(word);

			if (counter % colsCount == 0 && counter != 0 ) 
			{
				getline(readCSV, word, '\n');
				row.push_back(word);
			}
		}

	}

	// Now we read into a seperate array the header/temp
	vector<string>columnNames;

	string parsed;
	stringstream temp_stringstream(temp);
	
	for (int i = 0; i < colsCount; i++)	// get all but the last item then
	{
	//	columnNames.clear();
		if (getline(temp_stringstream, parsed, ','))
		{
			columnNames.push_back(parsed);
		}
	}

	getline(temp_stringstream, parsed, '\n');		// get the last item.
	columnNames.push_back(parsed);
	//for (int i = 0; i <= colsCount; i++)	//	 prints headers formatted. uncomment for troubleshooting
	//{
	//	cout << columnNames[i] << " ";
	//}
	//cout << endl << endl ;
	//
	//counter = 0;							// we reset this counter 
	//for (int i = 0; i < row.size(); i++)	// prints first row formatted to fit headers	// uncomment for troubleshooting
	//{	
	//	if (counter == (colsCount+1))		// after we print size col +1 things print a endl.)
	//	{
	//		cout << endl;
	//		counter = 0;
	//		cout << row.at(i) << " ";
	//	}
	//	else
	//	{
	//		cout << row.at(i) << " ";
	//	}
	//	counter++;
	//}
	//
	//cout << endl;
	
	readCSV.close();

	string valuesToInsert;
	string headerValues;

	//NEED STRING CREATORS USING OUR VECTORS FROM ABOVE. 
	//(formatted, headers) values('formatted , elements,');
	//cout<< "INSERT into " << TABLE <<"( "<< headerValues
	//	<<") values (" << valuesToInsert << " )";
		

	for (int i = 0; i <= colsCount; i++)
	{	
		string tempS = columnNames.at(i);

		transform(tempS.begin(), tempS.end(), tempS.begin(), ::tolower);
		
		if (tempS == "null")					// this line accounts for the values being null which don't take any ' ' values. 
		{
			headerValues.append("null,");
		}
		else
		{
			
			headerValues.append(columnNames.at(i));
			headerValues.append(", ");
		}
		
	}

	headerValues.pop_back();	// erases the last ',' for proper formatting
	headerValues.pop_back();	// erases the last ',' for proper formatting

	// output stream into a txt file **************************************
	//
	string outPutFileName = TABLE + ".txt";
	ofstream(output);
	output.open(outPutFileName);

	cout << "*** " << headerValues << " ***\n\n\n";
	counter = 0;
	for (int i = 0; i < row.size(); i++)
	{
		string tempS = row.at(i);
		transform(tempS.begin(), tempS.end(), tempS.begin(), ::tolower);

		if (counter == colsCount + 1)
		{
			valuesToInsert.pop_back();	// erases the last ',' for proper formatting

			output << "INSERT into " << TABLE << " ( " << headerValues
				<< ") values (" << valuesToInsert << " )\n";


			valuesToInsert = "";						// Once we have inserted the proper info into our file we clear the string for the next row. 


	//		valuesToInsert.append("\n");				//// uncomment for troubleshooting it prints to screen in the format required. 
	//		cout << valuesToInsert << endl;
			counter = 0;
		}
		if (tempS == "null")				// this line accounts for the values being null which don't take any ' ' values. 
		{
			valuesToInsert.append("null,");
			counter++;
		}
		else
		{
			valuesToInsert.append("'");
			valuesToInsert.append(row.at(i));
			valuesToInsert.append("',");
		//	cout << valuesToInsert << endl;
			counter++;
		}

	}

	valuesToInsert.pop_back();	// erases the last ',' for proper formatting and inserts the last row into the file. . 
	output << "INSERT into " << TABLE << " ( " << headerValues
		<< ") values (" << valuesToInsert << " )\n";
	
	output.close();
	return 0;
}
