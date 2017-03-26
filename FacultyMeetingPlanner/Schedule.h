#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>


using namespace std;


class TeacherList {						//  Try direct inheritance ?????????????????????
	unordered_map<string, int> list;
public:
	TeacherList();
	TeacherList(unordered_map<string, int> l);
	~TeacherList();
	unordered_map<string, int> getTeachers();
	int size();
	int hasConflict(TeacherList l);
	int numberOfConflicts();
	void addTeacher(string t);
	void erase();
	void print();
};

class Student {
	string name;
	TeacherList teacherList;
public:
	Student();
	~Student();
	Student(string n, TeacherList t);
	string getName();
	TeacherList getTeacherList();
	void setName(string n);
	void setTeachers(TeacherList t);
	int hasConflict(Student s);
	void addTeacher(string t);
	int numberOfTeachers();
	void erase();
	void print();
};



bool greaterThan(Student a, Student b);
bool byMostPopularTeacher(Student a, Student b);
bool bySumStudentTeachersStudents(Student a, Student b);
typedef bool(*functionName)(Student a, Student b);




class StudentList {
	vector<Student> list;
	unordered_map<string, int> tlist;  // teacher map with number of students by teacher
public:
	StudentList();
	StudentList(vector<Student> l);
	~StudentList();
	vector<Student> getStudentList();
	TeacherList getTeacherList();
	void addStudent(Student s);
	int size();
	void swap(int a, int b);
	string sortList(int s, string ord);
	void print();
	void printTeacherList();
	void load(string fileName);
	void erase();
};


class TimeSlot {
	int slotNumber;
	int maxSlotSize;
	int conflicts;
	StudentList studentList;
	TeacherList teacherList;
public:
	TimeSlot();
	TimeSlot(int n, int s);
	~TimeSlot();
    bool addStudent(Student s, int maxConflicts = 0);
    int getConflicts();
	void print();
//	int numberOfConflicts();
};

class Schedule {
	vector<TimeSlot> slots;
    
	int conflicts;
    int maxTimeSlots;
    int maxSlotSize;
    int slotCounter; // counts number of slots on schedule
	
public:
	Schedule(int t, int s ); // constructor with limit on number of slots
	~Schedule();
    int getConflicts();
    int getCounter();
	int getMaxTimeSlots();
	int getMaxSlotSize();
    void addSlot();
    void addStudent(Student s, int maxConflicts = 0);
    void erase();
    void help();
    void load(StudentList studentList);
    void menu();
    void print();
    void setMaxTimeSlots(int t);
	void setMaxSlotSize(int s);

};



