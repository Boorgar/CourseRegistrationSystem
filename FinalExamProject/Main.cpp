#include "AutoGenerate.h"
#include "create.h"
#include "Functions.h"
#include "InputLogin.h"
#include "loadClass_Students.h"
#include "MenuStaff.h"
#include "MenuStudent.h"
#include "Struct.h"
#include "UI.h"

string Schoolyear = "";
date dateStart;
date dateEnd;
string Sem = "";
Semesters SEMESTER[3];
Courses* COURSE = nullptr;
Classes* CLASS = nullptr;

int main() {
	resizeConsole(1300,700);
	txtColor(0);

	autoGenerateStaffProfiles("staff.txt");

	try
	{
		loadYearAndSem();
		if (Schoolyear != "")
			loadClassFromFile(CLASS);
		if (Sem != "")
			loadCoursesFromFile(COURSE);
	}
	catch (const std::exception& ex)
	{
		txtColor(15);
		cout << ex.what();
		_getch();
	}

	//loadYearAndSem();
	//loadCoursesFromFile(COURSE);

	char username[23];
	char password[23];
	int sizeUser = 0;
	int sizePass = 0;

	Login(username, password, sizeUser, sizePass);
	deleteCourses();
	deleteClasses();

	return 0;
}