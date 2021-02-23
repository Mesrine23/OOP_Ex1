#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

class School;
class Floor;
class Class;
class Corridor;
class Schoolyard;
class Stairs;
class Student;
class Teacher;


///////////////////////////////////////////////////////////////////////////////////



class Student {
	private:
		string name;
		string at; /* at = where he is at the moment */
		int fl,cl;
	public:
		Student(string nam, int f, int c);
		~Student();
		void print();
		void getF_CL(int &f, int &c);
		string getAT();
		void setAT(string place);
};

class Teacher {
	private:
		string name;
		int fl,cl,f; /* f = flag which shows whether he is, or not in class */
	public:
		Teacher(string nam, int f, int c, int FLAG=0);
		~Teacher();
		void print();
		void getF_CL(int &f, int &c);
		void setFLAG();
		int getFLAG();
};

class Class {
	private:
		int ppl; /* how many people are in this place */
		int capacity; /* capacity of place */
		Student** list;
		Teacher* teacher;
	public:
		Class(int cap);
		~Class();
		void print();
		void getCL(int &i, int &j, int &flag);
		void enter(Student* st);
		void place(Teacher* t, int f, int c);
};

class Corridor{
	private:
		int ppl; /* how many people are in this place */
		int capacity; /* capacity of place */
		Student** list;
	public:
		Corridor(int cap);
		~Corridor();
		void print();
		void getCORR(int &i, int &j);
		void enter(Student* st);
		void leave(Student* st);
};

class Schoolyard{
	private:
		int ppl; /* how many people are in this place */
		int capacity; /* capacity of place */
		Student** list;
	public:
		Schoolyard(int cap);
		~Schoolyard();
		void print();
		void getYARD(int &i, int &j);
		void enter(Student* st);
		void leave(Student* st);
};

class Stairs{
	private:
		int ppl; /* how many people are in this place */
		int capacity; /* capacity of place */
		Student** list;
	public:
		Stairs(int cap);
		~Stairs();
		void print();
		void getSTAIRS(int &i, int &j);
		void enter(Student* st);
		void leave();
};

class Floor{
	private:
		Class* c1;
		Class* c2;
		Class* c3;
		Class* c4;
		Class* c5;
		Class* c6;
		Corridor* corr;
	public:
		Floor(int capCL, int capCORR);
		~Floor();
		void print();
		void enter(Student* st, int i, int j, int &q);
		void place(Teacher* t, int f, int c);
};

class School{
	private:
		int STppl;
		int TCHRppl;
		Floor* f1;
		Floor* f2;
		Floor* f3;
		Schoolyard* yard;
		Stairs* stair;
		Student** STlist;
		Teacher** TCHRlist;
	public:
		School(int CL, int CORR, int ST, int YARD);
		~School();
		void print();
		void enter(Student* st); //student enters school
		void place(Teacher* t, int f, int c);
		void leave();
};



///////////////////////////////////////////////////////////////////////////////////



School::School(int CL, int CORR, int ST, int YARD)
{
	cout << "A School has been created!" << endl << endl;
	STppl = 0;
	TCHRppl = 0;
	STlist = (Student**)malloc(sizeof(Student*)*((CL+1)*18)); // (CL+1)*18 = max people
	TCHRlist = (Teacher**)malloc(sizeof(Teacher*)*18);
	yard = new Schoolyard(YARD);
	stair = new Stairs(ST);
	//cout << "Creating Floor No.1 -> " ;
	f1 = new Floor(CL,CORR);
	//cout << "Creating Floor No.2 -> " ;
	f2 = new Floor(CL,CORR);
	//cout << "Creating Floor No.3 -> " ;
	f3 = new Floor(CL,CORR);
}
School::~School()
{
	delete yard;
	delete stair;
	delete f1;
	delete f2;
	delete f3;
	cout << "A School to be destroyed!" << endl;
}

Schoolyard::Schoolyard(int cap) {
	this->ppl=0;
	this->capacity = cap;
	list = (Student**)malloc(sizeof(Student*)*cap);
	//cout << "created schoolyard of cap: " << capacity << endl;
}
Schoolyard::~Schoolyard(){
	//cout << "BOOM schoolyard" << endl;
}

Stairs::Stairs(int cap) {
	this->ppl = 0;
	this->capacity = cap;
	list = (Student**)malloc(sizeof(Student*)*cap);
	//cout << "created stairs of cap: " << capacity << endl;
}
Stairs::~Stairs(){
	//cout << "BOOM stairs" << endl;
}

Class::Class(int cap) {
	this->ppl = 0;
	this->capacity = cap;
	list = (Student**)malloc(sizeof(Student*)*cap);
	teacher = (Teacher*)malloc(sizeof(Teacher));
	teacher = NULL;
	//cout << "Done with Class" << endl;
}
Class::~Class() {
	//cout << "BOOM class" << endl;
}

Corridor::Corridor(int cap) {
	this->ppl = 0;
	this->capacity = cap;
	list = (Student**)malloc(sizeof(Student*)*cap);
	//cout << "Done with Corridor" << endl;
}
Corridor::~Corridor() {
	//cout << "BOOM corridor" << endl;
}

Floor::Floor(int capCL, int capCORR) {
	//cout << "Done" << endl;
	//cout << "Creating Class No.1 -> " ;
	c1 = new Class(capCL);
	//cout << "Creating Class No.2 -> " ;
	c2 = new Class(capCL);
	//cout << "Creating Class No.3 -> " ;
	c3 = new Class(capCL);
	//cout << "Creating Class No.4 -> " ;
	c4 = new Class(capCL);
	//cout << "Creating Class No.5 -> " ;
	c5 = new Class(capCL);
	//cout << "Creating Class No.6 -> " ;
	c6 = new Class(capCL);
	//cout << "Creating Corridor -> " ;
	corr = new Corridor(capCORR);
}
Floor::~Floor() {
	delete c1;
	delete c2;
	delete c3;
	delete c4;
	delete c5;
	delete c6;
	delete corr;
	//cout << "BOOM Floor" << endl;
}

Student::Student(string nam, int f, int c) {
	this->name = nam;
	this->fl = f;
	this->cl = c;
	this->at="OFF";
	cout << "A New Student has been created!" << endl << name << " -> Floor No." << fl << ", Class No. " << cl << endl << endl;
}
Student::~Student() {
	cout << "A Student to be destroyed!" << endl << name << endl;
}

Teacher::Teacher(string nam, int f, int c, int FLAG) {
	this->name = nam;
	this->fl = f;
	this->cl = c;
	this->f=FLAG;
	cout << "A New Teacher has been created!" << endl << name << " -> Floor No." << fl << ", Class No. " << cl << endl << endl;
}
Teacher::~Teacher() {
	cout << "A Teacher to be destroyed!" << endl << name << endl;
}



///////////////////////////////////////////////////////////////////////////////////

void School::print() {
	cout << "SCHOOL LIFE CONSISTS OF: " << endl;
	/*for(int i = 0 ; i<STppl ; ++i)
	{
		STlist[i]->print();
		cout<<endl;
	}*/
	cout << endl;
	yard->print();
	stair->print();
	cout << "-Floor number 1 contains:" << endl;
	f1->print();
	cout << "-Floor number 2 contains:" << endl;
	f2->print();
	cout << "-Floor number 3 contains:" << endl;
	f3->print();
	cout << endl;
}

void Schoolyard::print() {
	int i;
	cout << "->People in Schoolyard are: (students=" << ppl << "/" << capacity << ")" << endl;
	for(i=0 ; i<ppl ; ++i)
	{
		list[i]->print();
		cout << endl;
	}
}

void Stairs::print() {
	int i;
	cout << "-->People in Stairs are: (students=" << ppl << "/" << capacity << ")" << endl;
	for(i=0 ; i<ppl ; ++i)
	{
		list[i]->print();
		cout << endl;
	}
}

void Corridor::print() {
	int i;
	cout << "->People in Corridor are: (students=" << ppl << "/" << capacity << ")" << endl;
	for(i=0 ; i<ppl ; ++i)
	{
		list[i]->print();
		cout << endl;
	}
}

void Class::print() {
	int i;
	if(teacher!=NULL)
	{
		cout << "Teacher is -> ";
		teacher->print();
		cout << endl;
	}
	else
		cout << "No Teacher!" << endl;

	for(i=0 ; i<ppl ; ++i)
	{
		list[i]->print();
		cout << endl;
	}
}

void Floor::print() {
	corr->print();
	cout << "---->People in class 1 are:" << endl;
	c1->print();
	cout << "---->People in class 2 are:" << endl;
	c2->print();
	cout << "---->People in class 3 are:" << endl;
	c3->print();
	cout << "---->People in class 4 are:" << endl;
	c4->print();
	cout << "---->People in class 5 are:" << endl;
	c5->print();
	cout << "---->People in class 6 are:" << endl;
	c6->print();
}

void School::enter(Student* st) {
	int i,j,q=0;
	st->print();
	cout << " enters School" << endl;
	st->setAT("School");
	STlist [STppl] = st;
	++STppl;
	yard->getYARD(i,j);
	if (i<j)
	{
		//this->leave();
		yard->enter(st);
		st->setAT("Schoolyard");
		stair->getSTAIRS(i,j);
		if (i<j)
		{
			yard->leave(st);
			stair->enter(st);
			st->setAT("Stairs");
			st->getF_CL(i,j);
			if(i==1)
				f1->enter(st,i,j,q);
			else if (i==2)
				f2->enter(st,i,j,q);
			else
				f3->enter(st,i,j,q);

			if(q==1)
				stair->leave();
		}
	}
}

void Floor::enter(Student* st, int f, int c, int &q) {
	int i,j,flag;
	corr->getCORR(i,j);
	if(i<j)
	{
		st->print();
		cout << " exits Stairs" << endl;
		st->print();
		cout << " enters Floor" << endl;
		corr->enter(st);
		st->setAT("Corridor");
		q=1;
		if(c==1)
		{
			c1->getCL(i,j,flag);
			if((i<j) && (flag==0))
			{
				corr->leave(st);
				c1->enter(st);
				st->setAT("Classroom");
			}
		}
		else if (c==2)
		{
			c2->getCL(i,j,flag);
			if((i<j) && (flag==0))
			{
				corr->leave(st);
				c2->enter(st);
				st->setAT("Classroom");
			}
		}
		else if (c==3)
		{
			c3->getCL(i,j,flag);
			if((i<j) && (flag==0))
			{
				corr->leave(st);
				c3->enter(st);
				st->setAT("Classroom");
			}
		}
		else if (c==4)
		{
			c4->getCL(i,j,flag);
			if((i<j) && (flag==0))
			{
				corr->leave(st);
				c4->enter(st);
				st->setAT("Classroom");
			}
		}
		else if (c==5)
		{
			c5->getCL(i,j,flag);
			if((i<j) && (flag==0))
			{
				corr->leave(st);
				c5->enter(st);
				st->setAT("Classroom");
			}
		}
		else if (c==6)
		{
			c6->getCL(i,j,flag);
			if((i<j) && (flag==0))
			{
				corr->leave(st);
				c6->enter(st);
				st->setAT("Classroom");
			}
		}
	}
}

void Class::enter(Student* st) {
	st->print();
	cout << " enters Classroom" << endl;
	list[ppl] = st;
	++ppl;
}

void Corridor::enter(Student* st) {
	st->print();
	cout << " enters Corridor" << endl;
	list[ppl] = st;
	++ppl;
}
void Corridor::leave(Student* st) {
	st->print();
	cout << " exits Corridor" << endl;
	--ppl;
	list[ppl] = NULL;
}

void Schoolyard::enter(Student* st) {
	st->print();
	cout << " enters Schoolyard" << endl;
	list[ppl] = st;
	++ppl;
}
void Schoolyard::leave(Student* st) {
	st->print();
	cout << " exits Schoolyard" << endl;
	--ppl;
	list[ppl] = NULL;
}

void Stairs::enter(Student* st) {
	st->print();
	cout << " enters Stairs" << endl;
	list[ppl] = st;
	++ppl;
}
void Stairs::leave() {
	--ppl;
	list[ppl] = NULL;
}

/*void School::leave() {
	STlist[STppl] = NULL;
	--STppl;
}*/

void School::place(Teacher* t, int f, int c) {
	if (f==1)
		f1->place(t,f,c);
	else if (f==2)
		f2->place(t,f,c);
	else if (f==3)
		f3->place(t,f,c);
}

void Floor::place(Teacher* t, int f, int c) {
	if(c==1)
		c1->place(t,f,c);
	if(c==2)
		c2->place(t,f,c);
	if(c==3)
		c3->place(t,f,c);
	if(c==4)
		c4->place(t,f,c);
	if(c==5)
		c5->place(t,f,c);
	else
		c6->place(t,f,c);
}

void Class::place(Teacher* t, int f, int c) {
	teacher = t;
	t->setFLAG();
}


void Schoolyard::getYARD(int &i, int &j) {
	i = ppl;
	j = capacity;
}

void Stairs::getSTAIRS(int &i, int &j) {
	i = ppl;
	j = capacity;
}

void Corridor::getCORR(int &i, int &j) {
	i = ppl;
	j = capacity;
}
void Class::getCL(int &i, int &j, int &flag) {
	i = ppl;
	j = capacity;
	if(teacher==NULL)
		flag=0;
	else
		flag=1;
}

void Student::getF_CL(int &f, int &c)
{
	f = fl;
	c = cl;
}

void Student::setAT(string place) {
	this->at = place;
}

string Student::getAT(){
	return at;
}

void Student::print() {
	cout << name;
}

void Teacher::getF_CL(int &f, int &c) {
	f = fl;
	c = cl;
}

void Teacher::setFLAG() {
	f = 1;
}

int Teacher::getFLAG(){
	return f;
}

void Teacher::print() {
	cout << name;
}

///////////////////////////////////////////////////////////////////////////////////



int main(int argc, char* argv[]) // GIVE 2 -> 3 -> 6 -> 15
{

	int CL, CORR, ST, Y;
	int i=0;
	//School s;
	string s;

	CL = atoi(argv[1]);
	CORR = atoi(argv[2]);
	ST = atoi(argv[3]);
	Y = atoi(argv[4]);

	/* SOS START OF STUDENT & TEACHER CREATION */
	Student** st = (Student**)malloc(sizeof(Student*)*(CL*18));
	Teacher** tchr = (Teacher**)malloc(sizeof(Teacher*)*18);

	ifstream inputFile;

	inputFile.open("studentsFULL.txt");
	if (!inputFile)
	{
		cout << "Cannot find input file" << endl;
		exit(-1);
	}

	int infoF,infoC,j=0;

	string token,nam;
	string delimiter = "-";
	string info;



	while( getline (inputFile,s))
	{
		size_t pos = 0;
		size_t last = 0;
		size_t next = 0;
		j=0;
		while ((next = s.find(delimiter, last)) != string::npos)
		{
			if (j==0)
			{
				info = s.substr(last, next-last);
				//cout << info << endl;
				last = next + 1;
				++j;
				nam = info;
			}
			else
			{
				info = s.substr(last, next-last);
				stringstream geek(info);
				infoF=0;
				geek >> infoF;
				//cout << test << endl;
				last = next + 1;
				++j;
			}
		}

		info = s.substr(last);
		stringstream geek(info);
		infoC=0;
		geek >> infoC;
		//cout << test << endl;


		st[i] = new Student(nam,infoF,infoC);
		++i;
	}
	inputFile.close();

	cout << endl << "********** END OF STUDENT CREATION **********" << endl << endl << endl;

	inputFile.open("teachersFULL.txt");
	if (!inputFile)
	{
		cout << "Cannot find input file" << endl;
		exit(-1);
	}

	i=0;
	while( getline (inputFile,s))
	{
		size_t pos = 0;
		size_t last = 0;
		size_t next = 0;
		j=0;
		while ((next = s.find(delimiter, last)) != string::npos)
		{
			if (j==0)
			{
				info = s.substr(last, next-last);
				//cout << info << endl;
				last = next + 1;
				++j;
				nam = info;
			}
			else
			{
				info = s.substr(last, next-last);
				stringstream geek(info);
				infoF=0;
				geek >> infoF;
				//cout << test << endl;
				last = next + 1;
				++j;
			}
		}

		info = s.substr(last);
		stringstream geek(info);
		infoC=0;
		geek >> infoC;
		//cout << test << endl;


		tchr[i] = new Teacher(nam,infoF,infoC);
		++i;
	}
	inputFile.close();

	cout << endl << "********** END OF TEACHER CREATION **********" << endl << endl << endl;
	/* SOS END OF STUDENT & TEACHER CREATION */

	School school(CL,CORR,ST,Y);

	long now;
	now=time(NULL); // now is current time
	srand((unsigned int)now); // definition of rand() -> gave here current time as seed

	int choose;
	int guess;
	int all=0;

	while(all!=(CL+1)*18)
	{
		choose = rand()%2;
		if(choose==0) // students
		{
			choose = rand()%(CL*18);
			if(st[choose]->getAT()!="OFF")
				continue;
			else
			{
				school.enter(st[choose]);
				++all;
			}
		}
		else // teachers
		{
			choose = rand()%18;
			if(tchr[choose]->getFLAG()==1)
				continue;
			else
			{
				guess = rand()%2;
				if(guess==0)
				{
					int f,c;
					tchr[choose]->getF_CL(f,c);
					school.place(tchr[choose],f,c);
					++all;
				}
				else
				{
					tchr[choose]->setFLAG();
					++all;
				}
			}
		}
	}


	cout << endl << "********** END OF ENTER/PLACE **********" << endl << endl;

	school.print();

	cout << endl << endl;

	for(i=0 ; i<(CL*18) ; ++i)
		delete st[i];
	delete st;

	for(i=0 ; i<18 ; ++i)
		delete tchr[i];
	delete tchr;

	cout << endl << endl;

}
