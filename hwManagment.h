#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Capstone
{
public:
	
	// Default constructor
	Capstone(); 

	// Managment system options
	void search();
	void searchByDueDate();
	void searchByCourse();

	void add();
	void update();
	void markComplete();

	// Display HW tasks
	void printInfo();
	void printALL();

	// Managment System
	void startProject();
	void displayMenu();
	int getSelection(int selection);
	void managmentSystem(int selection);

	//Seralization
	void writeToFile();
	void readToFile();

private:
	
	// Variales for menu
	int selection = 0;
	
	// HW List Properties
	int taskNum;
	string name;
	string course;
	int days;
	int eta;
	bool cmpl;

	//seralization
	string fileName;

	// HW list 
	vector <Capstone> hwTasks;
	int taskAt;

};
