#include "EnrollCourse.h"


// Aux Functions
time_t timeToUnixTime(date end)
{
	int hour, min, sec;
	hour = min = sec = 0;
	//Assume session starts from 00:00:00
	time_t a = time(0);
	tm* timeinfo = localtime(&a);

	timeinfo->tm_year = end.year - 1900;
	timeinfo->tm_mon = end.month - 1;        //months since January - [0,11]
	timeinfo->tm_mday = end.day;            //day of the month - [1,31]
	timeinfo->tm_hour = hour;            //hours since midnight - [0,23]
	timeinfo->tm_min = min;                //minutes after the hour - [0,59]
	timeinfo->tm_sec = sec;                //seconds after the minute - [0,59]

	a = mktime(timeinfo);

	return a;
}
bool isCourseRegistrationSessionActive(date registerStartDay, date registerEndDay)
{
	time_t now = time(0);
	if (timeToUnixTime(registerStartDay) <= now && now <= timeToUnixTime(registerEndDay))
		return true;
	return false;
}
bool checkSchedule(Students aStudent, Courses courseNew)
{
	BasicCourses* ptem = aStudent.courseStudent;
	while (ptem != nullptr)
	{
		for (int i = 0; i < 2; i++)
			for(int j = 0; j < 2; j++)
				if (ptem->schedule[j].day == courseNew.schedule[i].day && ptem->schedule[j].time == courseNew.schedule[i].time)
					return false;
		ptem = ptem->next;
	}
	return true;
};
bool checkIsEnrolled(Students aStudent, Courses courseNew)
{
	BasicCourses* pCur = aStudent.courseStudent;
	if (!pCur)
		return true;
	while (pCur)
	{
		if (pCur->courseID == courseNew.courseID)
			return false;
		pCur = pCur->next;
	}
	return true;
}

// Student Enroll Course
void enrollACourse(Students& aStudent, Courses& courseNew)
{
	int k = courseNew.sem;
	int count = -1;
	ifstream infile;
	infile.open(Schoolyear + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course " + Sem + ".csv");
	string ignore_line;

	// Check file exist?
	if (!infile.is_open())
		throw std::runtime_error("Oh shit, we messed up. There's no Course Sem file...");
	// Count how many course already enrolled in file
	while (infile.peek() != EOF)
	{
		getline(infile, ignore_line);
		count++;
	}
	infile.close();

	ofstream outfile;

	if (checkSchedule(aStudent, courseNew))
		if (checkIsEnrolled(aStudent, courseNew))
			if (isCourseRegistrationSessionActive(dateStart, dateEnd))
				if (courseNew.countStudent < courseNew.maxStudent)
					if (count < 5)
					{
						// Insert into student's list of enrolled courses
						BasicCourses* pt = new BasicCourses;
						pt->next = aStudent.courseStudent;
						aStudent.courseStudent = pt;

						pt->courseID = courseNew.courseID;
						pt->courseName = courseNew.courseName;
						for (int i = 0; i < 2; i++)
						{
							pt->schedule[i].day = courseNew.schedule[i].day;
							pt->schedule[i].time = courseNew.schedule[i].time;
						}

						// Insert Student into Course's students list
						BasicStudents* ps = new BasicStudents;
						ps->next = courseNew.studentID;
						courseNew.studentID = ps;

						ps->firstName = aStudent.firstName;
						ps->lastName = aStudent.lastName;
						ps->ID = aStudent.ID;

						// Open Student's course list, add new course to .csv file
						string dir = Schoolyear + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course " + Sem + ".csv";
						outfile.open(dir, ios::out | ios::app);
						outfile << courseNew.courseID << "," << courseNew.courseName << "," << courseNew.teacherName << "," << courseNew.numCredits << ',' << courseNew.countStudent << ',' << ++courseNew.maxStudent << ',' << courseNew.schedule[0].day << "," << courseNew.schedule[0].time << "," << courseNew.schedule[1].day << "," << courseNew.schedule[1].time << endl;
						if (!outfile.is_open())
							throw std::runtime_error("Can't load Semester's Scoreboard");
						outfile.close();

						// Add Student's name to Course Scoreboard.csv
						dir = Schoolyear + "/Semesters/" + Sem + "/" + courseNew.courseID + "/Scoreboard.csv";
						outfile.open(dir, ios::out | ios::app);
						if (!outfile.is_open())
							throw std::runtime_error("Can't load Semester's Scoreboard");
						outfile << ++courseNew.countStudent << "," << aStudent.ID << "," << aStudent.firstName << "," << aStudent.lastName << ",-1,-1,-1,-1" << endl;
						outfile.close();
						// default course's scoreboard:
						// Ex: 31,101,Anpan,Suhkoi,-1,-1,-1,-1

					}
					else
						throw std::runtime_error("Maximum number of courses reached!");
				else
					throw std::runtime_error("Course Full. Better luck next time :D");
			else
				throw std::runtime_error("Course Registration Session no longer active");
		else
			throw std::runtime_error("You already enrolled in this course");
	else
		throw std::runtime_error("New course's schedule conflict with already enrolled ones");
}
void viewEnrolledCourses(Students* aStudent)
{
	string line, temp;
	int a = 20;
	ifstream file;
	file.open(Schoolyear + "/Classes/" + aStudent->className + "/" + aStudent->ID + "/Course " + Sem + ".csv");
	if (!file.is_open())
		throw std::runtime_error("Can't open Student Course List");

	// Print field Names
	txtColor(15);
	gotoxy(30, 20); cout << "CourseID";
	gotoxy(41, 20);	cout << "Course Name";
	gotoxy(54, 20);	cout << "Teacher Name";
	gotoxy(68, 20);	cout << "Credits";
	gotoxy(77, 20);	cout << "Number of students";
	gotoxy(97, 20); cout << "Session 1";
	gotoxy(108, 20); cout << "Session 2";

	while (file.peek() != EOF)
	{
		a++;
		getline(file, temp, ',');	// Course ID
		gotoxy(30, a);	cout << temp;

		getline(file, temp, ',');	// Course Name
		gotoxy(41, a);	cout << temp;

		getline(file, temp, ',');	// Teacher
		gotoxy(54, a);	 cout << temp;

		getline(file, temp, ',');	// Credits
		gotoxy(68, a);	cout << temp;

		getline(file, temp, ',');	// NumStudents
		gotoxy(77, a);	cout << temp;

		getline(file, temp, ',');	// MaxStudents
		cout << "/" << temp;

		getline(file, temp, ',');	// Weekday 1
		gotoxy(97, a);

		cout << " ";
		getline(file, temp, ',');	// Period 1
		

		getline(file, temp, ',');	// Weekday 2
		gotoxy(108, a);
		
		cout << " ";
		getline(file, temp);		// Period 2
	

	}
		_getch();
		file.close();
}


// Edit Course
void removeACourse(Students* aStudent, Courses* courseDelete)
{
	// How does it work:
	/*
		- Remove BasicStudent node inside Courses
		- Remove BasicCourse node inside Students
		- Pass two linked list to updateCourseB4D
	*/
	// check if course list empty
	if (aStudent->courseStudent == nullptr)
		throw std::runtime_error("You haven't enroll any course yet!");

	ifstream file;
	string ignore_line;

	// Delete student linked list in course
	BasicStudents* pCurStudent = courseDelete->studentID;
	BasicStudents* pDelStudent = nullptr;

	if (courseDelete->studentID->ID == aStudent->ID)
	{
		pDelStudent = courseDelete->studentID;
		courseDelete->studentID = pCurStudent->next;
		delete pDelStudent;
	}
	else
	{
		while (pCurStudent != nullptr && pCurStudent->ID != aStudent->ID)
		{
			pDelStudent = pCurStudent;
			pCurStudent = pCurStudent->next;
		}
		if (pCurStudent == nullptr)
			return;
		pDelStudent->next = pCurStudent->next;
		delete pCurStudent;

	}

	//Delete course in students
	BasicCourses* pCurCourse = aStudent->courseStudent;
	BasicCourses* pDelCourse = nullptr;
	if (aStudent->courseStudent->courseID == courseDelete->courseID)
	{
		pDelCourse = aStudent->courseStudent;
		aStudent->courseStudent = pCurCourse->next;
		delete pDelCourse;
	}
	else
	{
		while (pCurCourse != nullptr && pCurCourse->courseID != courseDelete->courseID)
		{
			pDelCourse = pCurCourse;
			pCurCourse = pCurCourse->next;
		}
		if (pCurCourse == nullptr)
			return;
		pDelCourse->next = pCurCourse->next;
		delete pCurCourse;

	}

	updateCourseB4D(aStudent, courseDelete);
};
void updateCourseB4D(Students* aStudent, Courses* courseDelete)
{
	// How does it work:
	/*
		- Delete Student's "Course Sem X.csv"
		- Create new "Course Sem X.csv";
		- Ouput Enrolled Courses linked list into new "Course Sem X.csv"
		- Repeat same steps for Course's "Scoreboard.csv"
	*/

	ofstream file;

	string dir = "./" + Schoolyear + "/Classes/" + aStudent->className + "/" + aStudent->ID + "/Course " + Sem + ".csv";
	//Example dir: ./2020-2021/Classes/19apcs1/100/Course Sem 1.csv

	remove(dir.c_str());
	file.open(dir);

	BasicCourses* pCurrentCourse = aStudent->courseStudent;
	while (pCurrentCourse != nullptr)
	{
		file << pCurrentCourse->courseID << "," << pCurrentCourse->courseName << "," << courseDelete->schedule[0].day << "," << courseDelete->schedule[0].time << "," << courseDelete->schedule[1].day << "," << courseDelete->schedule[1].time << endl;
		pCurrentCourse = pCurrentCourse->next;
	}
	file.close();

	// Update file in course folder
	dir = "./" + Schoolyear + "/Semester/" + Sem + "/" + courseDelete->courseID + "/Scoreboard.csv";

	remove(dir.c_str());
	file.open(dir);

	BasicStudents* pCurrentStudent = courseDelete->studentID;
	int count = 1;
	while (pCurrentStudent != nullptr)
	{
		file << count++ << "," << pCurrentStudent->ID << "," << pCurrentStudent->firstName << "," << pCurrentStudent->lastName << ",0,0,0,0" << endl;
		pCurrentStudent = pCurrentStudent->next;
	}
	file.close();
}


// View Menu
void viewAllStudentInCourse(Courses* course)
{
	int count = 1;
	BasicStudents* pCur = course->studentID;
	if (pCur == nullptr)
		throw std::runtime_error("There no students enrolled in this course yet!");
	while (pCur != nullptr)
	{
		cout << count++ << ' ' << "ID: " << pCur->ID << '\t' << "Name: " << pCur->firstName << " " << pCur->lastName;
		pCur = pCur->next;
	}
	Nocursortype();
}
void viewAllStudentInClass(Classes* Class)
{
	txtColor(15);
	int count = 1;
	Students* pCur = Class->student;
	cout << "\tID\tName\n";
	while (pCur != nullptr)
	{
		cout << count++ << '\t' << pCur->ID << '\t' << pCur->firstName << " " << pCur->lastName << endl;
		pCur = pCur->next;
	}
	Nocursortype();
}
void viewAllCourse()
{
	if (COURSE)
	{
		txtColor(15);
		int temp = 17;
		gotoxy(50, temp);	cout << "Course's ID";
		gotoxy(70, temp);	cout << "Course's Name";
		temp++;
		Courses* curCourse = COURSE;
		while (curCourse != nullptr)
		{
			gotoxy(50, temp);	cout << curCourse->courseID;
			gotoxy(70, temp);	cout << curCourse->courseName;
			temp++;
			curCourse = curCourse->next;
		}
		Nocursortype();
	}
	else
		throw std::runtime_error("There are no courses yet!");
	Nocursortype();
}
void viewAllClass()
{
	int temp = 20;
	int c = 1;
	if (CLASS)
	{
		Classes* curClass = CLASS;
		gotoxy(30, temp++); cout << "No\tClass Name\n";
		while (curClass != nullptr)
		{
			gotoxy(30, temp++); cout << c++ << "\t\t" << curClass->className << endl;
			curClass = curClass->next;
		}
	}
	else
		throw std::runtime_error("There are no classes yet!");
	Nocursortype();
}