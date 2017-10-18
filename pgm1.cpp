/*
Author: Giang Ly
Student ID: C427R468
Program Number: 1

Description of Problem:
You are the owner of a new store and need to keep track of
your inventory. Since you are a seasoned C++ programmer, 
you are going to write a C++ program to perform this function.
*/



#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <limits.h>

using namespace std;

//Define structure with array
struct inventory
{
	float totalcostofitem;
	int partnumber;
	string description;
	int quantity;
	float itemprice;
	float totalpriceofitem;
} parts[100];


//Prototypes for functions
void print_menu();
int get_user_command();
void list_parts();
void load_file();
void add_part();
void total_costs();
void modify_parts();

//Main programs
int main()
{
    //Display the menu.
	load_file();
	int Choice;
    //Loop until user input is valid.
	do
	{
		print_menu();
		Choice = get_user_command();
		switch (Choice)
		{
		case 1:list_parts();
			break;
		case 2:add_part();
			break;
		case 3:modify_parts();
			break;
		case 4:total_costs();
			break;
		case 5:cout << "Exiting..." << endl;
			break;
		default:cout << "Not a valid choice" << endl;
		}
	} while (Choice != 5);
	return 0;
}

//This is the menu that is displayed for user to select a choice from.
void print_menu()
{

	cout << "1. Display Parts" << endl;
	cout << "2. Add a new Part" << endl;
	cout << "3. Modify a Part" << endl;
	cout << "4. Display Total Cost" << endl;
	cout << "5. exit" << endl;
}

//Get user input.
int get_user_command()
{
	int command;
	cout << "Enter Choice: ";
	cin >> command;
	return command;
}

//Displays the inventory list.
void list_parts()
{
	int counter = 1;
    //Determines if there are entries present in inventory.txt
	if (parts[counter].partnumber == 0)
	{
		cout << "There are no entries" << endl;
	}
	else
	{
        /*Loop until the part number is 0 while displaying the 
        information. 0 Means there are no more parts to list*/
		do
		{
			cout << parts[counter].partnumber <<
				parts[counter].description <<
                " " << parts[counter].quantity << " " << "$" <<
                parts[counter].itemprice << " " << "$" <<
                parts[counter].totalpriceofitem << endl;
			counter++;
		} while (parts[counter].partnumber != 0);
	}
}

//Load Inventory.txt at the beginning of the program.
void load_file()
{
    //Attempt to open Inventory.txt
	ifstream infile;
	infile.open("Inventory.txt");
	int counter = 1;

    //Check if file exists, if not then create the text file.
	if (infile.fail())
	{
		cout << "File not found" << endl;
		ofstream ofile;
		ofile.open("Inventory.txt");
		ofile.close();
		cout << "File Created Ready for entries." << endl;
	}
	else
	{
        //Loop if text file exists and store data to structure array.
		do
		{
			infile >> parts[counter].partnumber >> 
			    parts[counter].quantity >> parts[counter].itemprice;
			getline(infile, parts[counter].description);
			parts[counter].totalpriceofitem = 
                parts[counter].quantity * parts[counter].itemprice;
			counter++;
		} while (!infile.eof());
	}
	infile.close();
}

//Add a new part to a new text file or existing one.
void add_part()
{
	int counter = 1;
    //Loop until array is at an empty spot.
	while (parts[counter].partnumber != 0)
	{
		counter++;
	}
    //Get information on new part.
	parts[counter].partnumber = counter;
	cout << "Enter item: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, parts[counter].description);
	cout << "Enter Quantity: ";
	cin >> parts[counter].quantity;
	cout << "Enter Cost: ";
	cin >> parts[counter].itemprice;
	parts[counter].totalpriceofitem = 
        parts[counter].quantity * parts[counter].itemprice;

    //Write New part to file.
	ofstream ofile;
	ofile.open("Inventory.txt", ios::app);
	ofile << endl << parts[counter].partnumber << " " <<
        parts[counter].quantity << " " <<
		parts[counter].itemprice << " " << parts[counter].description;
	ofile.close();
    cout << "Successfully Added Part." << endl;
}
//Calculate the total cost of inventory.
void total_costs()
{
	int counter = 1;
	float totalcost = 0;
	/*Take the sumation of each total prices of the items to get 
    Total price of inventory.*/
	while (parts[counter].partnumber != 0)
	{
		totalcost = totalcost + parts[counter].totalpriceofitem;
		counter++;
	}
	cout << "Total cost of inventory: $" << totalcost << endl;
}

//Modify existing part.
void modify_parts()
{
	int counter;
	//Gets user selection for part number to modify.
	cout << "Enter part to modify: ";
	cin >> counter;
	cout << endl << parts[counter].partnumber << " " << 
        parts[counter].description << " " << parts[counter].quantity
		<< " " << "$" << parts[counter].itemprice << " " << "$" << 
        parts[counter].totalpriceofitem << endl;
	//User input new part information.
	cout << "Enter item: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, parts[counter].description);
	cout << "Enter Quantity: ";
	cin >> parts[counter].quantity;
	cout << "Enter Cost: ";
	cin >> parts[counter].itemprice;
	parts[counter].totalpriceofitem = 
        parts[counter].quantity * parts[counter].itemprice;

	counter = 1;
	//Write information back to Inventory.txt
	ofstream ofile;
	ofile.open("Inventory.txt", ios::trunc);
    //Loop until all parts are written to the file.
	while (parts[counter].partnumber != 0)
	{
		ofile << parts[counter].partnumber << " " << 
            parts[counter].quantity << " " <<
			parts[counter].itemprice << " " << 
            parts[counter].description << endl;
		counter++;
	}
	ofile.close();
    cout << "Successfully Modified Part." << endl;
}
