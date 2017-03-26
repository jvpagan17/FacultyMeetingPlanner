#include "Schedule.h"



TeacherList::TeacherList() 
{
}

TeacherList::TeacherList(unordered_map<string, int> l):list(l) 
{
}

TeacherList::~TeacherList() 
{
}

unordered_map<string, int> TeacherList::getTeachers()
{
	return list; 
}

int TeacherList::size() 
{
	return int(list.size());
}
// Returns number of conflicts between two teacher lists.
//int TeacherList::hasConflict(TeacherList l) 
//{
//	int conflictCounter = 0;
//	for (auto t : l.getTeachers()) {
//		if (list[t.first]>0 && t.second>0) {
//			conflictCounter += list[t.first] + t.second - 1;
//		}
//	}
//	conflictCounter += numberOfConflicts() + l.numberOfConflicts();
//	return conflictCounter;
//}

// Returns number of conflicts between two teacher lists.
// Counts # of teachers in both lists.


int TeacherList::hasConflict(TeacherList l)
{
	int conflictCounter = 0;
	for (auto t : l.getTeachers()) {
		if (list[t.first]>0 && t.second>0) {
			conflictCounter += 1;
		}
	}
//	conflictCounter += numberOfConflicts() + l.numberOfConflicts();
	return conflictCounter;
}

int TeacherList::numberOfConflicts()
{
	int count = 0;
	for (auto n : list) {
		if (n.second>1) count += n.second - 1;
	}
	return count;
}

void TeacherList::addTeacher(string t) 
{
	list[t] += 1;
}

void TeacherList::erase()
{ 
	list.erase(list.begin(), list.end()); 
}

void TeacherList::print() 
{
	map<string, int> orderedList(list.begin(), list.end());
	for (auto s : orderedList) {
		if (s.second) {
			if (s.second > 1) cout << "*";
			cout << s.first << " ";
		}
	}
	cout << endl;
}



Student::Student() 
{
}

Student::~Student()
{
}

Student::Student(string n, TeacherList t) :name(n), teacherList(t.getTeachers())
{
}

string Student::getName()
{
	return name;
}

TeacherList Student::getTeacherList()
{
	return teacherList;
}

void Student::setName(string n)
{
	name = n;
}

void Student::setTeachers(TeacherList t)
{
	teacherList = t;
}

int Student::hasConflict(Student s) 
{
	return teacherList.hasConflict(s.teacherList); 
}

void Student::addTeacher(string t)
{
	teacherList.addTeacher(t);
}

int Student::numberOfTeachers() 
{ 
	return teacherList.size();
}

void Student::erase()
{
	name = ""; teacherList.erase();
}

void Student::print()
{
	cout << name << ": ";
	teacherList.print();
	//		cout << endl;
}



// Master Teacher List:
// List of all teachers with the total number of students of each teacher.
unordered_map<string, int> masterTeacherList;

// Sorts in non ascending order of number of teachers of each student
bool greaterThan(Student a, Student b) 
{
	return a.numberOfTeachers() > b.numberOfTeachers(); 
}
// Sorts in non ascending order of number of students of most popular teacher in student's list
bool byMostPopularTeacher(Student a, Student b)
{
	int aMostPopular=-1, bMostPopular=-1;		// number of students of most popular teacher of students a and b.
	for (auto n : a.getTeacherList().getTeachers()) { // n is a teacher in teacherList which is an unordered_map.
		if (masterTeacherList[n.first] > aMostPopular) // n.first is the teacher name used as index to get # students 
			aMostPopular = masterTeacherList[n.first];  // for that teacher in masterTeacharList
	}
	
	for (auto n : b.getTeacherList().getTeachers()) {
		if (masterTeacherList[n.first]> bMostPopular)
			bMostPopular = masterTeacherList[n.first];
	}

  //if (aMostPopular == bMostPopular) return a.numberOfTeachers() > b.numberOfTeachers();
	return aMostPopular > bMostPopular;
}

// Sorts by total number of students of teachers in student's list.
bool bySumStudentTeachersStudents(Student a, Student b)
{
	int aTotalTeachers = 0, bTotalTeachers = 0;		// sum of number of students of all teachers of students a and b.
	for (auto n : a.getTeacherList().getTeachers()) {
		aTotalTeachers += masterTeacherList[n.first];
	}

	for (auto n : b.getTeacherList().getTeachers()) {
		bTotalTeachers += masterTeacherList[n.first];
	}

	return aTotalTeachers > bTotalTeachers;
}




StudentList::StudentList() 
{
}

StudentList::StudentList(vector<Student> l) 
{
	list = l;

}
StudentList::~StudentList() 
{
}

vector<Student> StudentList::getStudentList() 
{ 
	return list;
}

TeacherList StudentList::getTeacherList()
{ 
	return tlist;
}

void StudentList::addStudent(Student s)
{
	list.push_back(s);
}

int StudentList::size()
{
	return int(list.size());
}

void StudentList::swap(int a, int b)
{
	Student temp = list[a]; list[a] = list[b]; list[b] = temp;
}

functionName sortFunctions[] = { greaterThan, byMostPopularTeacher, bySumStudentTeachersStudents };

string StudentList::sortList(int s, string order)
{
	erase();
	load("student.csv");
	order = "File";

	if (s > 1 && s < 5) {
		sort(list.begin(), list.end(), sortFunctions[s - 2]);  //sort by greaterThan, byMostPopularTeacher, or bySumStudentTeachersStudents
		order = (s == 2 ? "NumberOfTeachers/" : s == 3 ? "MostPopularTeacher/" : "SumStudentTeachersStudents/") + order;
	}
	if (s == 5) {
		sort(list.begin(), list.end(), sortFunctions[0]);
		sort(list.begin(), list.end(), sortFunctions[1]);
		order = "MostPopularTeacher/NumberOfTeachers/" + order;

	}
	if (s == 6) {
		sort(list.begin(), list.end(), sortFunctions[0]);
		sort(list.begin(), list.end(), sortFunctions[2]);
		order = "SumStudentTeachersStudents/NumberOfTeachers/" + order;
	}
	order = (order+"                                                    ").substr(0, 50);
	return order;
}




void StudentList::print() 
{
	int n = 0;
	for (auto s : list) {
		cout << ++n << ") " << s.getName() << ": ";
		s.getTeacherList().print();
	}
	cout << endl;
}

void StudentList::printTeacherList() 
{
	int n = 0;
	map<string, int> orderedTList(tlist.begin(), tlist.end());
	for (auto s : orderedTList) {
		cout << ++n << ") " << s.first << ": " << s.second << endl;
		;
	}
	cout << endl;
}

void StudentList::load(string fileName)
{
	ifstream fin(fileName);
	string line, name, titles;
	Student aStudent;
//	int n = 0;
	getline(fin, line);
	//cout << line << endl;
	while (getline(fin, line)) {
	//	n++;
		//		cout << n << ") " << line << endl;
		int i = 0;
		name = "";
		for (i = 0; line[i] != ','; ++i) name += line[i];
		aStudent.setName(name);
		//		cout << n << ") " << name << ": " << endl;
		string teacher = "";
		for (int j = i + 2; j < int(line.length()); ++j) {
			if (line[j] == ',' || line[j] == '\"') {
				aStudent.addTeacher(teacher);
				tlist[teacher] += 1;
		//		cout << teacher << " ";
				teacher = "";
			}
			else if (line[j] != ' ')
				teacher += line[j];
		}
		//		cout << endl;
		//		aStudent.print();
		//		cout << endl;
		addStudent(aStudent);
		aStudent.erase();
	}
	masterTeacherList = tlist;
}

void StudentList::erase() {
	list.erase(list.begin(),list.end());
	tlist.erase(tlist.begin(), tlist.end());
}




TimeSlot::TimeSlot() 
{
}

TimeSlot::TimeSlot(int n, int s) 
{
	slotNumber = n;
	maxSlotSize = s;
	conflicts = 0;
}

TimeSlot::~TimeSlot()
{
}

int TimeSlot::getConflicts() {
	return conflicts;
}

bool TimeSlot::addStudent(Student s, int maxConflicts) 
{
	if (studentList.size() < maxSlotSize &&
		teacherList.hasConflict(s.getTeacherList()) <= maxConflicts) { // add student if has no more than x (default=0) conflicts
		studentList.addStudent(s);
		for (auto n : s.getTeacherList().getTeachers()) {
			if (n.second > 0) { conflicts++; }
			teacherList.addTeacher(n.first);
			
		}
		return true;
	}
	else return false;
}

void TimeSlot::print() 
{
	cout << "Slot Number: " << slotNumber + 1;
	int n = teacherList.numberOfConflicts();
	if (n > 0) cout << "   " << n << " conflict(s)";
	cout << endl << "Teachers:" << endl;
	teacherList.print();
	cout << "Students:" << endl;
	for (auto s : studentList.getStudentList()) {
		s.print();
	}
	cout << endl;
}


	
	

Schedule::Schedule(int t, int s )  // constructor with limit on number of slots
{
	maxTimeSlots = t; 
	maxSlotSize = s;
	slotCounter = -1;
	conflicts = 0;
	addSlot(); 
}		

Schedule::~Schedule()
{
}

int Schedule::getCounter() 
{
	return slotCounter; 
}


int Schedule::getMaxTimeSlots()
{
	return maxTimeSlots;
}

int Schedule::getMaxSlotSize()
{
	return maxSlotSize;
}

int Schedule::getConflicts()
{
	return conflicts;
}


void Schedule::setMaxTimeSlots(int t)
{
	maxTimeSlots = t;
}

void Schedule::setMaxSlotSize(int s)
{
	maxSlotSize = s;
}


void Schedule::addSlot() 
{
	TimeSlot aTimeSlot(++slotCounter,maxSlotSize);
	slots.push_back(aTimeSlot);
}

// Add Student to the Schedule
// 
void Schedule::addStudent(Student s, int maxConflicts) 
{
	int i;
	// Try to add student to existing slot
	for (i = 0; i <= slotCounter; ++i) {
		if (slots[i].addStudent(s, maxConflicts)) {		// if student successfully added to a slot return
			conflicts += maxConflicts;		// calculates total conflicts between teachers on schedule
			return;
		}
	}
	if (i>slotCounter)	// if student not successfully added to existing slots, add new slot
	{
		if (slotCounter < maxTimeSlots - 1) {  // if max number of slots not reached, add slot
			addSlot();
			slots[slotCounter].addStudent(s);

		}
		else {			// max number of slots reached, cram student 			
			addStudent(s, maxConflicts + 1); // if student successfully added to a slot break
		}
	}
}

void Schedule::print() 
{
	for (auto s : slots) {
		s.print();
	}
}

void Schedule::load(StudentList studentList) 
{
	for (auto s : studentList.getStudentList()) {
		addStudent(s);
	}
}

void Schedule::erase() {
	slots.erase(slots.begin(), slots.end());
	slotCounter = -1;
	conflicts = 0;
}

void Schedule::help() {
	cout << "\t\t\t\tFusion Meeting Planner" << endl << endl;
	cout << "This program helps plan student centric faculty meetings, based on the following assumptions:" << endl;
	cout << "- One meeting per student with all the teachers of that student." << endl;
	cout << "- 30 minute meeting timeslots, up to[4] meetings per timeslot, [14] timeslots per day." << endl;
	cout << "- Minimize conflicts(when a teacher has to attend more than one meeting in a given time slot)." << endl;
	cout << "- Students are assigned to timeslots on a first come first serve basis based on their order in the Student List." << endl;
	cout << "- If student has conflict with next available timeslot, he is assigned to the next available timeslot." << endl;
	cout << "- If student has conflict with all available timeslots, he is assigned to first timeslot with least conflicts." << endl;
	cout << "The Student List may be sorted to optimize the assignement process.  The list of sorting options are listed below." << endl;
	cout << "Some trial and error with different oredering alternatives may be necessary to achieve the optimal solution.endl" << endl;
	cout << "An analytics option is provided to quickly compare different sorting alternatives to mitigate scheduling conflicts." << endl << endl;
	cout << "Sort Order Options:" << endl;
	cout << "1) Original File Order" << endl;
	cout << "2) Number of Teachers of the Student" << endl;
	cout << "3) Teacher Popularity (Students taking classes with most popular teachers are given priority)" << endl;
	cout << "4) Sum of Student Teacher's Students - counts all students for all the teachers of the student." << endl;
	cout << "5) Sort by option (1) then by option (2) and then by option (3) above." << endl;
	cout << "6) Sort by option (1) then by option (2) and then by option (4) above." << endl << endl << endl;
	cout << "Default Settings:   Mentors = 4   TimeSlots = 14   SortOption = 6" << endl << endl;


}

void Schedule::menu() 
{

	int n = -1, p, q, s, x, y;
	int sortOption = 6;			// Sort Student List by Sum of Student Teacher Students/Number of Students/File
	int oldSortOption, oldMaxTimeSlots;

	StudentList aStudentList;			// instantiate a StudentList
	string order = aStudentList.sortList(sortOption, "");  // sortList loads Student List and Sorts it.

	while (n != 0) {


		cout << "1)Students 2)Teachers 3)Sort 4)Schedule 5)Parameters 6)Analysis 7) Help 0)Quit ";
		cout << "Enter 1-8? ";
		cin >> n;
		cout << endl;

		switch (n) {
		case 0:
			break;
		case 1:

			cout << "Student List: (ordered by " << order << ")" << endl;
			aStudentList.print();
			break;
		case 2:
			cout << endl << "List of Teachers with number of students" << endl;
			aStudentList.printTeacherList();
			break;
		case 3:
			s = -1;
//			while (s != 0) {
				cout << endl << "Select Sort Method (currently ordered by " << order << ")" << endl;
				cout << "1)Unsorted 2)Number of Teachers 3)Teacher Popularity 4)Sum Teacher's Students 5)123 6)124  0)Quit ";
				cout << "Enter 0-5? ";
				cin >> s;
				cout << endl;
				if (s > 0 && s < 7) {
					order = aStudentList.sortList(s, "");
					sortOption = s;
				}
//			}
			break;
		case 4:
			cout << "Meeting Schedule (* denotes teacher with multiple meetings)" << endl;
			erase();
			load(aStudentList);
			print();
			cout << "Total conflicts: " << getConflicts();
			cout << "\tMaximum Periods: " << maxTimeSlots << "\tMentors: " << maxSlotSize;
			cout << "\tOrder: " << order << endl << endl;
			break;
		case 5:
			p = 0;
			q = 0;
			cout << "Enter the corresponding parameter: " << endl;
			cout << "Number of Mentors? ";
			cin >> p;
			if (p != 0) {
				setMaxSlotSize(p);
			}
			cout << "Number of Timeslots (time periods in a day)? ";
			cin >> q;
			if (q != 0) {
				setMaxTimeSlots(q);
			}
			// Checks that students / mentors >= maxTimesSlots, otherwise maxTimeSlots = students/mentors;
			// Otherwise can't fit students in schedule and results in infinite loop.
			q = int(ceil(aStudentList.size()*1.0 / getMaxSlotSize()));
			if (ceil(aStudentList.size()*1.0 / getMaxSlotSize()) > getMaxTimeSlots()) {
				setMaxTimeSlots(q);
				cout << "******* Number of Time Slots is too small and was adjusted to " << q << " ********" << endl;
			}
			erase();
			load(aStudentList);
			break;
		case 6:
			oldSortOption = sortOption;
			oldMaxTimeSlots = getMaxTimeSlots();
			cout << "Enter minimum number of Timeslots? ";
			cin >> x;
			// Checks that students / mentors >= maxTimesSlots, otherwise maxTimeSlots = students/mentors;
			// Otherwise can't fit students in schedule and results in infinite loop.
			if (ceil(aStudentList.size()*1.0 / getMaxSlotSize()) > x) {
				x = int (ceil(aStudentList.size()*1.0 / getMaxSlotSize()));
				cout << "******* Number of Time Slots is too small and was adjusted to " << x << " ********" << endl;
			}
			cout << "Enter maximum number of Timeslots? ";
			cin >> y;
			if (y < x) {
				y = x;
				cout << "******* Number of Time Slots is too small and was adjusted to " << y << " ********" << endl;
			}
			cout << endl << endl << endl << "\t\t\t\tMeeting Conflict Analysis" << endl << endl;
			cout << "\t\t\t(shows # of teacher meeting conflicts)" << endl << endl;
			cout << "\t\t\tNumber of Time Slots-> \t";
			for (int i = x; i <= y; ++i) {
				cout << "\t" << i;
			}
			cout << endl;
			cout << "Student List Sort Option:" << endl;
			for (int s = 1; s <= 6; ++s) {
				cout << s << ") " << aStudentList.sortList(s, order) << "\t";
				for (int i = x; i <= y; ++i) {
					setMaxTimeSlots(i);
					erase();
					load(aStudentList);
					cout << getConflicts() << "\t";
				}
				cout << endl;
			}
			cout << endl;
			sortOption = oldSortOption;
			setMaxTimeSlots(oldMaxTimeSlots);
			break;
		case 7:
			help();
			break;
		default:
			break;
		}
	}
}


/*void Schedule::menu() 
{

	int n = -1, p, q, s, x, y;
	string order = "File";


	StudentList aStudentList;			// instantiate a StudentList
	aStudentList.load("student.csv");

	while (n != 0) {


		cout << "1)Students 2)Teachers 3)Sort 4)Schedule 5)Parameters 6)Conflicts 7) Help 0)Quit ";
		cout << "Enter 1-8? ";
		cin >> n;
		cout << endl;

		switch (n) {
		case 0:
			break;
		case 1:

			cout << "Student List: (ordered by " << order << ")" << endl;
			aStudentList.print();
			break;
		case 2:
			cout << endl << "List of Teachers with number of students" << endl;
			aStudentList.printTeacherList();
			break;
		case 3:
			s = -1;
			while (s != 0) {
				cout << endl << "Select Sort Method (currently ordered by " << order << ")" << endl;
				cout << "1)Unsorted 2)Number of Teachers 3)Teacher Popularity 4)Sum Teacher's Students 5)123 6)124  0)Quit ";
				cout << "Enter 0-5? ";
				cin >> s;
				cout << endl;
				if (s > 0 && s < 7) {
					order = aStudentList.sortList(s, order);
				}
			}
			break;
		case 4:
			cout << "Meeting Schedule (* denotes teacher with multiple meetings)" << endl;
			aSchedule.erase();
			aSchedule.load(aStudentList);
			aSchedule.print();
			cout << "Total schedule conflicts: " << aSchedule.getConflicts() << endl << endl;
			break;
		case 5:
			p = 0;
			q = 0;
			cout << "Enter the corresponding parameter: " << endl;
			cout << "Number of Mentors? ";
			cin >> p;
			if (p != 0) {
				aSchedule.setMaxSlotSize(p);
			}
			cout << "Number of Timeslots (time periods in a day)? ";
			cin >> q;
			if (q != 0) {
				aSchedule.setMaxTimeSlots(q);
			}
			aSchedule.erase();
			aSchedule.load(aStudentList);
			break;
		case 6:

			cout << "Enter minimum number of Timeslots? ";
			cin >> x;
			cout << "Enter maximum number of Timeslots? ";
			cin >> y;
			cout << endl << endl << "\t\t\t\tMeeting Conflict Analysis" << endl << endl;
			cout << "\t\t\tNumber of Time Slots: \t";
			for (int i = x; i <= y; ++i) {
				cout << "\t" << i;
			}
			cout << endl;
			cout << "Sort Order" << endl;
			for (int s = 1; s <= 6; ++s) {
				cout << aStudentList.sortList(s, order) << "\t";
				for (int i = x; i <= y; ++i) {
					aSchedule.setMaxTimeSlots(i);
					aSchedule.erase();
					aSchedule.load(aStudentList);
					cout << aSchedule.getConflicts() << "\t";
				}
				cout << endl;
			}
			cout << endl;
			break;
		case 7:
			aSchedule.help();
			break;
		default:
			break;
		}
	}
	}*/
