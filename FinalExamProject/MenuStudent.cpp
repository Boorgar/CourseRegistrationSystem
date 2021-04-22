#include "MenuStudent.h"
#include "UI.h"
#include "InputLogin.h"

void MenuStudent(char username[], char password[], int sizeUser, int sizePass) {
	system("cls");
	logo_moodle();
	Nocursortype();

	keyboardShortcutMenu();

	drawBorderMenuStudent();

	txtColor(15);
	gotoxy(74, 18); cout << "H E L L O  S T U D E N T";

	txtColor(15);
	gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
	gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
	gotoxy(64, 24); cout << "          E D I T   C O U R S E S          ";
	gotoxy(64, 26); cout << "          V I E W   C O U R S E S          ";
	gotoxy(64, 28); cout << "            S C O R E B O A R D            ";
	gotoxy(64, 30); cout << "               L O G   O U T               ";

	MenuStudentSettings(username, password, sizeUser, sizePass);
}

void MenuStudentSettings(char username[], char password[], int sizeUser, int sizePass) {
	int dem = 0;
	string user = convertToString(username, sizeUser);
	string pass = convertToString(password, sizePass);

	while (true)
	{
		char choice = _getch();
		txtColor(15);
		gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
		gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
		gotoxy(64, 24); cout << "          E D I T   C O U R S E S          ";
		gotoxy(64, 26); cout << "          V I E W   C O U R S E S          ";
		gotoxy(64, 28); cout << "            S C O R E B O A R D            ";
		gotoxy(64, 30); cout << "               L O G   O U T               ";

		if (choice == 80)
		{
			dem++;
			if (dem > 6)
				dem = 1;
		}

		if (choice == 72)
		{
			dem--;
			if (dem < 1)
				dem = 6;
		}

		if (choice == 27) { // ESC
			system("cls");
			exit(0);
		}

		if (dem == 1)
		{
			txtColor(240);
			gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
			if (choice == 13)
			{
				MenuStudentProfileInfo(username, password);
				keyboardShortcutMenu();
			}
		}
		if (dem == 2)
		{
			txtColor(240);
			gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
			if (choice == 13)
			{
				MenuChangePasswordStudent(user, pass);
				keyboardShortcutMenu();
			}

		}
		if (dem == 3)
		{
			txtColor(240);
			gotoxy(64, 24); cout << "          E D I T   C O U R S E S          ";
			if (choice == 13)
			{

			}
		}
		if (dem == 4)
		{
			txtColor(240);
			gotoxy(64, 26); cout << "          V I E W   C O U R S E S          ";
			if (choice == 13)
			{

			}
		}
		if (dem == 5)
		{
			txtColor(240);
			gotoxy(64, 28); cout << "            S C O R E B O A R D            ";
			if (choice == 13)
			{

			}
		}
		if (dem == 6)
		{
			txtColor(240);
			gotoxy(64, 30); cout << "               L O G   O U T               ";
			if (choice == 13)
			{
				txtColor(0);
				Login(username, password, sizeUser, sizePass);
			}
		}
	}
}

void MenuStudentProfileInfo(string username, string password) {
	keyboardShortcut();
	fillBlackMenu();

	txtColor(15);
	gotoxy(70, 15);	cout << " _____            __ _ _      ";
	gotoxy(70, 16);	cout << "|  __ \\          / _(_) |     ";
	gotoxy(70, 17);	cout << "| |__) | __ ___ | |_ _| | ___ ";
	gotoxy(70, 18);	cout << "|  ___/ '__/ _ \\|  _| | |/ _ \\";
	gotoxy(70, 19);	cout << "| |   | | | (_) | | | | |  __/";
	gotoxy(70, 20);	cout << "|_|   |_|  \\___/|_| |_|_|\\___|";

	txtColor(15);
	ifstream in;
	string s;

	in.open("Student Profiles/" + username);

	string ignore;
	string studentID;
	string lastName;
	string firstName;
	string gender;
	string dob;
	string socialID;

	while (!in.eof()) {
		getline(in, ignore);
		getline(in, studentID);
		getline(in, lastName);
		getline(in, firstName);
		getline(in, gender);
		getline(in, dob);
		getline(in, socialID);
	}
	in.close();

	gotoxy(70, 24);	cout << "Name: " << lastName << " " << firstName;
	gotoxy(70, 26);	cout << "Student ID: " << studentID;
	gotoxy(70, 28);	cout << "Gender: " << gender;
	gotoxy(70, 30);	cout << "Date Of Birth: " << dob;
	gotoxy(70, 32);	cout << "Social ID: " << socialID;



	while (true) {
		char choice = _getch();

		if (choice == 13 || choice == 27) {
			fillBlackMenu();
			drawBorderMenuStudent();


			txtColor(15);
			gotoxy(74, 18); cout << "H E L L O  S T U D E N T";

			txtColor(240);
			gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";

			txtColor(15);
			gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
			gotoxy(64, 24); cout << "          E D I T   C O U R S E S          ";
			gotoxy(64, 26); cout << "          V I E W   C O U R S E S          ";
			gotoxy(64, 28); cout << "            S C O R E B O A R D            ";
			gotoxy(64, 30); cout << "               L O G   O U T               ";
			return;
		}

	}


}

void MenuChangePasswordStudent(string username, string& password) {
	keyboardShortcut();
	fillBlackMenu();
	UnNocursortype();
	txtColor(15);

	string oldPassword;
	string newPassword;
	string newPasswordAgain;
	bool check;

	int temp = 20;
	do {
		gotoxy(70, temp);
		cout << "Old password: ";
		cin >> oldPassword;

		for (int i = 0; i < oldPassword.size(); ++i) {
			if (oldPassword.size() > password.size())
				check = false;
			else if (oldPassword.size() < password.size())
				check = false;
			else if (oldPassword[i] != password[i])
				check = false;
			else
				check = true;
		}
		temp++;
	} while (check == false);

	gotoxy(70, temp);
	cout << "New password: ";
	cin >> newPassword;
	temp++;

	do {
		gotoxy(70, temp);
		cout << "Please input your new password again: ";
		cin >> newPasswordAgain;
		temp++;
	} while (newPassword.compare(newPasswordAgain) != 0);



	ifstream in;
	ofstream out;

	in.open("Student Accounts/" + username);

	string nameFile;
	string passFile;
	while (!in.eof()) {
		getline(in, nameFile, ',');
		getline(in, passFile);
	}

	in.close();

	string fileName = "Student Accounts/" + username;
	remove(fileName.c_str());

	out.open("Student Accounts/" + username);
	out << username << endl << newPassword;
	out.close();

	password = newPassword;

	Nocursortype();
	fillBlackMenu();
	drawBorderMenuStudent();

	txtColor(15);
	gotoxy(74, 18); cout << "H E L L O  S T U D E N T";
	gotoxy(64, 20); cout << "   P R O F I L E   I N F O R M A T I O N   ";
	txtColor(240);
	gotoxy(64, 22); cout << "       C H A N G E   P A S S W O R D       ";
	txtColor(15);
	gotoxy(64, 24); cout << "          E D I T   C O U R S E S          ";
	gotoxy(64, 26); cout << "          V I E W   C O U R S E S          ";
	gotoxy(64, 28); cout << "            S C O R E B O A R D            ";
	gotoxy(64, 30); cout << "               L O G   O U T               ";
}