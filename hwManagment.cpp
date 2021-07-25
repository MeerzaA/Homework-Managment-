#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

#include "hwManagment.h"

Capstone::Capstone()
{
	taskNum = 0;
	taskAt = 1;
	name = " ";
	course = " ";
	days = 0;
	cmpl = false;
	eta = 0;
	fileName = " ";

	vector <Capstone> hwTasks;
}

void Capstone::add()
{	
	taskNum++;
	
	cout << " ENTER TASK INFORMATION BELOW (*With No Spaces*) \n" << endl;

	cout << " What is the name of the assignment: ";
	cin >> name;
	cout << endl;
	
	cout << " What is the name of the course: ";
	cin >> course;
	cout << endl;

	cout << " How many days is the assignment due: ";
	cin >> days;
	cout << endl;

	cout << " How many hours will this take to complete: ";
	cin >> eta;
	cout << endl;

	cmpl = false;

	hwTasks.push_back(Capstone(*this));
}

void Capstone::update()
{
	Capstone update;
	printALL();

	cout << " SELECT A TASK TO UPDATE";
	int markTask;
	cout << "\n Selection: ";
	cin >> markTask;

	for (Capstone x : hwTasks)
	{
		if (x.taskNum == markTask)
		{
			update.taskNum = x.taskNum;
			update.name = x.name;
			update.course = x.course;
			update.days = x.days;
			update.eta = x.eta;
			update.cmpl = x.cmpl;

			cout << "\n What would you like to update.\n" << endl;
			cout << " (1) NAME \n";
			cout << " (2) COURSE \n";
			cout << " (3) Days \n";
			cout << " (4) ETA \n";
			cout << " (5) COMPLETE \n";

			selection = getSelection(selection);

			switch (selection)
			{
			case 1:
				cout << " New Name: ";
				cin >> update.name;
				break;
			case 2:
				cout << " New Course Name: ";
				cin >> update.course;
				break;
			case 3:
				cout << " New Day Amount: ";
				cin >> update.days;
				break;
			case 4:
				if (update.cmpl != true) 
				{
					update.cmpl = true;
				}
				else 
				{
					update.cmpl = false;
				}
				cout << " Completion Status Has Been Changed";
				break;
			case 5:
				cout << " New ETA: ";
				cin >> update.eta;
				break;
			default:
				cout << "Wrong Option Try Again";
				break;
			}

		}
	}

	cout << "\n Here Is Your Updated Task" << endl;
	update.printInfo();

	markTask--;
	hwTasks.erase(hwTasks.begin() + markTask);
	hwTasks.insert(hwTasks.begin() + markTask, 1, update);

}

void Capstone::markComplete()
{
	Capstone cap;
	vector <Capstone> y;
	
	for (Capstone x : hwTasks)
	{
		if (x.cmpl != true)
		{
			x.printInfo();
			y.push_back(x);
		}
	}

	cout << " SELECT A TASK TO MARK COMPLETE ";
	int markTask;
	cout << "\n Selection: ";
	cin >> markTask;

	for (Capstone x : y)
	{	
		if (x.taskNum == markTask)
		{
			cap.taskNum = x.taskNum;
			cap.name = x.name;
			cap.course = x.course;
			cap.days = x.days;
			cap.eta = x.eta;
			cap.cmpl = true;

			markTask--;
			hwTasks.erase(hwTasks.begin() + markTask);
			hwTasks.insert(hwTasks.begin() + markTask, 1, cap);
		}
	}

	if (cap.taskNum < 1) 
	{
		cout << "\n No Matching Elements Found" << endl;
	}
}

void Capstone::search()
{	
	cout << " Please enter a number to make a selection.\n" << endl;
	cout << " (1) SEARCH BY DUEDATE \n";
	cout << " (2) SEARCH BY COURSE \n";
	cout << " (3) DISPLAY ALL INCOMPLETE ASSIGNMENTS \n";
	
	selection = getSelection(selection);
	
	switch (selection)
	{
	case 1:
		searchByDueDate();
		break;
	case 2:
		searchByCourse();
		break;
	case 3:
		
		for (Capstone x : hwTasks)
		{
			if (x.cmpl == false)
			{
				x.printInfo();
			}
		}
	
		break;
	default:
	
		break;
	}
	
	
}

void Capstone::searchByDueDate() 
{
	int dueIn;
	cout << " IN HOW MANY DAYS IS THE ASSIGNMENT DUE: ";
	cin >> dueIn;

	for (Capstone x : hwTasks)
	{
		if (x.days <= dueIn )
		{
			x.printInfo();
		}
	}
}


void Capstone::searchByCourse() 
{
	string crsNam;

	cout << "\n ENTER THE EXACT COURSE NAME\n" << endl;
	cout << " Course Include: ";
	for (Capstone x : hwTasks)
	{
		cout << x.course + " ";
	}

	cout << "\n Course Name: ";
	cin >> crsNam;

	for (Capstone x : hwTasks)
	{
		if (x.course == crsNam)
		{
			x.printInfo();
		}
	}
}

void Capstone::writeToFile() 
{
	ofstream myfile;
	
	cout << " What Do You Want To Name The File: " << endl;
	cout << " Do not exclude .dat extension" << endl;
	cout << " Name: ";
	cin >> fileName;
	fileName = fileName + ".dat";

	myfile.open(fileName, ios::out | ios::binary);
	
	for (Capstone x : hwTasks)
	{
		myfile.write((char*)&x, sizeof(hwTasks));
	}

	myfile.close();
}

void Capstone::readToFile() 
{
	ifstream myfile;

	cout << " What Is The Name Of The File You Want To Open: " << endl;
	cout << " Do not exclude .dat extension" << endl;
	cout << " Name: ";
	cin >> fileName;
	fileName = fileName + ".dat";

	myfile.open(fileName, ios::out | ios::binary);

	vector <Capstone> readin;

	for (Capstone x : readin)
	{
		myfile.read((char*)&x, sizeof(hwTasks));
	}

	myfile.close();

}

void Capstone::printALL() 
{	
	if (taskAt < hwTasks.back().taskNum) 
	{
		hwTasks[taskAt - 1].printInfo();
		taskAt++;
	}
	else 
	{
		return hwTasks.back().printInfo();
	}

	return printALL(); // tail recursion
}

void Capstone::printInfo()
{
	cout << endl;
	cout << " TASK NUMBER " << taskNum <<endl;
	cout << " -------------------------" << endl;
	cout << " Name: " << name << endl;
	cout << " Course: " << course << endl;
	cout << " Days: " << days << endl;
	cout << " Estimated Time of Completeion: " << eta << "\hrs" << endl;
	printf(" Is the task Complete: %s\n", cmpl ? "Yes" : "No");
	cout << endl;
}

int Capstone::getSelection(int selection)
{
	cout << "\n Selection: ";
	cin >> selection;
	return selection;
}


void Capstone::displayMenu()
{
	cout << "\n Homework Managment System " << endl;
	cout << " --------------------------- ";
	cout << "\n Please enter a number to make a selection.\n" << endl;
	cout << " (1) ADD \n";
	cout << " (2) UPDATE \n";
	cout << " (3) SEARCH \n";
	cout << " (4) MARK COMPLETE \n";
	cout << " (5) PRINT ALL TASKS \n";
	cout << " (6) WRITE TO FILE \n";
	cout << " (7) READ FROM FILE \n";
	cout << " (*) PRESS ANY OTHER KEY TO EXIT \n";
}

void Capstone::startProject()
{
	do
	{
		displayMenu();
		selection = getSelection(selection);
		cout << endl;
		managmentSystem(selection);

	} while (selection <= 7 && selection >= 1);

	cout << "\n You have closed the progam \n" << endl;
}


void Capstone::managmentSystem(int selection)
{
	switch (selection)
	{
	case 1:
		add();
		break;
	case 2:
		update();
		break;
	case 3:
		search();
		break;
	case 4:
		markComplete();
		break;
	case 5:
		printALL();
		break;
	case 6:
		writeToFile();
		break;
	case 7:
		readToFile();
		break;
	default:
		break;
	}
}
