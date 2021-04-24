#include "loadClass_Students.h"

float convertToFloat(string score){
    int j=0;
    float ans=0;
    while (j<score.length() && score[j]!='.'){
        ans*=10;
        ans+= float(score[j]-'0');
        ++j;
    }
    j++;
    float tmp=0.1;
    while (j<score.length()){
        ans+=float(score[j]-'0')*tmp;
        tmp/=10;
        ++j;
    }
    return ans;
}

BasicCourses *loadCourse(string path, int sem, string StudentID){
    BasicCourses *course=0,*tmp=0;
    ifstream f;
    f.open(path);
    while (!f.eof()){
        string stmp;
        getline(f,stmp,',');
        if (stmp=="") continue;
        if (course){
            tmp->next=new BasicCourses;
            tmp=tmp->next;
        }
        else {
            course=new BasicCourses;
            tmp=course;
        }
        tmp->courseID=stmp;
        getline(f,tmp->courseName,',');

        f>>tmp->mark->Midterm >> tmp->mark->Final >> tmp->mark->Bonus >> tmp->mark->Total;
        f.ignore(100000,',');

        tmp->mark=new CourseScore;
        tmp->mark->next=0;

        string score="";
        getline(f,score,',');
        tmp->mark->Midterm=convertToFloat(score);

        getline(f,score,',');
        tmp->mark->Final=convertToFloat(score);

        getline(f,score,',');
        tmp->mark->Bonus=convertToFloat(score);

        getline(f,score,',');
        tmp->mark->Total=convertToFloat(score);

        tmp->mark->studentID=StudentID;
        

        getline(f,tmp->schedule[0].day,',');
        getline(f,tmp->schedule[0].time,',');
        getline(f,tmp->schedule[1].day,',');
        getline(f,tmp->schedule[1].time);
        tmp->sem=sem;
    }    
    f.close();
    return course;
}

Students *loadStudentInfo(string path){         //path: schoolyear/classes/classname/id/
    Students *stu=new Students;
    stu->courseStudent=0;
    // get student's basic info
    ifstream f;
    f.open(path+"\\Profile.txt");                 
    f >> stu->no;
    f.ignore(10000,'\n');
    getline(f,stu->ID);
    getline(f,stu->firstName);
    getline(f,stu->lastName);
    getline(f,stu->gender);
    string DOB;
    getline(f,DOB);
    stu->dateOfBirth=convertToDay(DOB);
    getline(f,stu->idSocial);
    f.close();

    //get course
    stu->courseStudent=loadCourse(path+"\\Course Sem 1.csv",1,stu->ID);
    
    BasicCourses *tmp=stu->courseStudent;
    for (int i=2;i<=3;++i){
        while (tmp && tmp->next) tmp=tmp->next;
        if (tmp) tmp->next=loadCourse(path+"\\Course Sem "+char (i+'0') +".csv",i,stu->ID);
        else{
            tmp=loadCourse(path+"\\Course Sem "+char (i+'0') +".csv",i,stu->ID);
        }
    }

    return stu;
}

Students *loadStudent(string path, string ClassName){ // path: schoolyear/Classes/ClassName/
    Students *stu=0;
    ifstream f;
    f.open(path+"allStudents.txt");
    if (!f.is_open()) return 0;
    Students *tmp=0;
    while (!f.eof()){
        string ID;
        getline(f,ID);
        string StudentPath=path+ID;
        if (stu){
            tmp->next=loadStudentInfo(StudentPath);
            tmp=tmp->next;
        }
        else{
            stu=loadStudentInfo(StudentPath);
            tmp=stu;
        }
        tmp->className=ClassName;
        tmp->next=0;
    }
    f.close();
    return stu;
}

Classes* loadClass(){
    Classes* Class=0;
    string path=Schoolyear+"\\Classes\\";
    string listClass=path+"Classes.txt";
    ifstream f;
    f.open(listClass);
    if (!f.is_open()) return 0;
    Classes *tmp=0;
    while (!f.eof()){
        string ClassName;
        getline(f,ClassName);
        if (ClassName=="") continue;
        if (Class){
           tmp->next=new Classes;
           tmp->next->prev=tmp;
           tmp=tmp->next;
        }
        else{
            Class=new Classes;
            tmp=Class;
            tmp->prev=0;
        }
        tmp->className=ClassName;
        tmp->next=0;
        tmp->student=loadStudent(path+ClassName+"\\",ClassName);
    }
    return Class;
}