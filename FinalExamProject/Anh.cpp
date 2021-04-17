﻿#include "function13.h"

bool checkSchedule(Students aStudent, Courses courseNew)
{
    Courses* ptem = aStudent.courseStudent;
    while (ptem != nullptr)
    {
        if (ptem->sem == courseNew.sem)
        {
            for (int j = 0; j < 2; j++)
                if ((ptem->schedule[j].day == courseNew.schedule[j].day) && (ptem->schedule[j].time == courseNew.schedule[j].time))
                    return false;
        }
        ptem->next;
    }
    return true;
};

void enrollACourse(Students& aStudent, Courses courseNew, fstream& f)
{
    int k = courseNew.sem;
    int count = -1;
    f.open(Schoolyear + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(k) + ".csv", ios::in);
    string ignore_line;
    if (!f.is_open())
        throw "error";
    while (!f.eof())
    {
        getline(f, ignore_line);
        count++;
    }
    f.close();
    f.open(Schoolyear + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(k) + ".csv", ios::out | ios::in);

    if ((checkSchedule(aStudent, courseNew) == true) && courseNew.countStudent < courseNew.maxStudent)
        if (count < 5)
        {
            f << courseNew.courseID << "," << courseNew.courseName << ",0,0,0,0" << endl;
            f.close();
            f.open(Schoolyear + "/Semester/Semester" + to_string(k) + "/" + courseNew.courseID + "Scoreboard.csv", ios::in);
            int count1 = -1;
            if (!f.is_open())
                throw "error";
            while (!f.eof())
            {
                getline(f, ignore_line);
                count1++;
            }
            f.close();
            f.open(Schoolyear + "/Semester/Semester" + to_string(k) + "/" + courseNew.courseID + "Scoreboard.csv", ios::out | ios::in);
            f << ++count1 << "," << aStudent.ID << "," << aStudent.firstName << "," << aStudent.lastName << ",0,0,0,0" << endl;
            f.close();

            // chèn vào list course student
            Courses*& pt = aStudent.courseStudent;
            if (pt == nullptr)
                //pt = &courseNew; 
                aStudent->courseStudent = courseNew;
            else
            {
                while (pt->next != nullptr)
                    pt = pt->next;
                pt->next = &courseNew;
            }

            // chèn student vào course
            if (courseNew.countStudent == 0)
            {
                courseNew.studentID = new BasicStudents;
                courseNew.studentID->firstName = aStudent.firstName;
                courseNew.studentID->lastName = aStudent.lastName;
                courseNew.studentID->ID = aStudent.ID;
                courseNew.studentID->next = nullptr;
            }
            else
            {
                courseNew.studentID->next = new BasicStudents;
                courseNew.studentID->next->firstName = aStudent.firstName;
                courseNew.studentID->next->lastName = aStudent.lastName;
                courseNew.studentID->next->ID = aStudent.ID;
                courseNew.studentID->next = courseNew.studentID;
            }
            courseNew.countStudent++;
        }
}
void viewEnrolledCourses(Students aStudent, fstream& f)
{
    string courseID;
    string courseName;
    string midscore;
    string finalscore;
    string bonus;
    string overall;
    // in course sem 1
    cout << "Courses semester 1: " << endl;
    f.open("input.csv");
    if (!f.is_open())
        throw "error";
    while (!f.eof())
    {
        getline(f, courseID, ',');
        cout << "Course ID: " << courseID << " ";
        getline(f, courseName, ',');
        cout << "Course Name: " << courseName << " ";
        getline(f, midscore, ',');
        cout << "Midterm Score: " << midscore << " ";
        getline(f, finalscore, ',');
        cout << "Final Score: " << finalscore << " ";
        getline(f, bonus, ',');
        cout << "Bonus: " << bonus << " ";
        getline(f, overall);
        cout << "GPA: " << overall << " ";
        cout << endl;
    }
    f.close();

    // in course sem 2
    cout << "Courses semester 2: " << endl;
    f.open("input.csv");
    if (!f.is_open())
        throw "error";
    while (!f.eof())
    {
        getline(f, courseID, ',');
        cout << "Course ID: " << courseID << " ";
        getline(f, courseName, ',');
        cout << "Course Name: " << courseName << " ";
        getline(f, midscore, ',');
        cout << "Midterm Score: " << midscore << " ";
        getline(f, finalscore, ',');
        cout << "Final Score: " << finalscore << " ";
        getline(f, bonus, ',');
        cout << "Bonus: " << bonus << " ";
        getline(f, overall);
        cout << "GPA: " << overall << " ";
        cout << endl;
    }
    f.close();

    // in course sem 3
    cout << "Courses semester 3: " << endl;
    f.open("input.csv");
    if (!f.is_open())
        throw "error";
    while (!f.eof())
    {
        getline(f, courseID, ',');
        cout << "Course ID: " << courseID << " ";
        getline(f, courseName, ',');
        cout << "Course Name: " << courseName << " ";
        getline(f, midscore, ',');
        cout << "Midterm Score: " << midscore << " ";
        getline(f, finalscore, ',');
        cout << "Final Score: " << finalscore << " ";
        getline(f, bonus, ',');
        cout << "Bonus: " << bonus << " ";
        getline(f, overall);
        cout << "GPA: " << overall << " ";
        cout << endl;
    }
    f.close();
}
void updateCourse(Students aStudent, Courses courseDelete, fstream& f)
{
    string file = "./" + Schoolyear + "/Classes/" + aStudent.className + "/" + aStudent.ID + "/Course Sem" + to_string(courseDelete.sem) + ".csv";
    remove(file.c_str());
    f.open(file);
    Courses* ptem = aStudent.courseStudent;
    while (ptem != nullptr)
    {
        f << ptem->courseID << "," << ptem->courseName << "," << ptem->mark->Midterm << "," << ptem->mark->Final << "," << ptem->mark->Bonus << "," << ptem->mark->GPA << endl;
        ptem = ptem->next;
    }
    f.close();
}

void removeACourse(Students aStudent, Courses courseDelete, fstream& f)
{
    // xoá trong student // list
    Courses* ptem;
    ptem = aStudent.courseStudent;
    Courses* pdelete;
    string s1 = aStudent.courseStudent->courseID, s2 = courseDelete.courseID;
    if (s1 == s2)
    {
        pdelete = ptem;
        aStudent.courseStudent = aStudent.courseStudent->next;
        delete ptem;
    }
    else
    {
        while (ptem != nullptr || ptem->courseID != courseDelete.courseID)
            ptem = ptem->next;
        if (ptem != nullptr)
        {
            pdelete = ptem;
            ptem = ptem->next;
            delete pdelete;
        };
    };

    // xoá trong Course
    /*
    BasicStudents* pt = courseDelete.studentID;
    BasicStudents* pdele;
    if (pt == nullptr)
        return;
    if (pt->ID == aStudent.ID)
    {
        pdele = pt;
        courseDelete.studentID = courseDelete.studentID->next;
        delete pdele;
    }
    else
    {
        while (pt != nullptr && pt->ID != aStudent.ID)
            pt = pt->next;
        if (pt != nullptr)
        {
            pdele = pt;
            pt = pt->next;
            delete pdele;
        };
    };
    */
    // gọi hàm doc lai file
    updateCourse(aStudent, courseDelete, f);
};



