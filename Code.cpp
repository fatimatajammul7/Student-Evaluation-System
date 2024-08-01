#include<iostream>
#include<fstream>

using namespace std;


class helper
{
public:
	static int stringlenght( char* str )
	{
		int count =0;
		for(int i=0;i<str[i]!='\0';i++){                          //calculates the length of string
			count++;
		}
		return count;
	}
	static char* getstringfrombuffer(char* str)
	{
		char* B = 0;
		int B_Length = stringlenght(str);
		if (B_Length > 0){	
			B = new char[B_Length+1];
			char* tempD = B;
			for (char* temp = str; *temp != '\0'; temp++, tempD++)
				*tempD = *temp;                                                 //deep copy
			*tempD = '\0';
		}
		return B;
	}
	static bool SEARCHSTRING(char* rollno, char*tofindrollno)
	{
		bool check=false;
		int k=0;
		if(rollno[k]==tofindrollno[k])
		{
			for(int j=1; j<9; j++)
			{
				if(rollno[j]==tofindrollno[j])
					k++;			
			}
			if(k==8)
			{
				check=true;                            //condition to check if roll no becomes equal tofindrollno
			}
			
		}
		return check;
	}
};


class StudentEvaluation
{
	char RollNo[9];
	char* FirstName;
	char* LastName;
	int* QMarks;
	int* aMarks;
	int total;
	static int totalstudents;
	static int tA;
	static int tQ;
	static int* Atotal;
	static int* Qtotal;

	
public:
	friend void PrintStatistics(StudentEvaluation* studentList);//Global

	StudentEvaluation()
	{
		FirstName=0;
		LastName=0;
		aMarks=0;
		QMarks=0;
		total=0;
		for(int i=0; i<9; i++)
		{
			RollNo[i]=0;
		}
	}

	void ReadFromFileE(ifstream& fin)
	{
		char fname[40];
		char lname[40];
		fin>>RollNo;
		fin>>fname;
		fin>>lname;
		FirstName=helper::getstringfrombuffer(fname);
		LastName=helper::getstringfrombuffer(lname);

		total=0;
		QMarks = new int[tQ];
		for(int i=0; i<tQ; i++)
		{ 
		    fin>>QMarks[i];
			total=total+QMarks[i];                      //total marks of quizzes
		}

		aMarks = new int[tA];
		for(int i=0; i<tA; i++)
		{
			fin>>aMarks[i];                           //total marks of assighnments
		    total=total+aMarks[i];
		}
		

	}

    int Gettotal()
	{
		return total;                              // total marks of each student
	}

	static int Gettotalstudents()
	{
		return totalstudents;
	}

	char* Getrollno()
	{
		return RollNo;
	}

	void SetValues(int totalst, int totalquiz, int totalassi, int* qtotals, int* atotals)
	{
	    
		totalstudents=totalst;
		tA=totalassi;
		tQ=totalquiz;
		Atotal = new int[tA];
		for(int i=0; i<tA; i++)
		{
			Atotal[i]=atotals[i];
		}
		Qtotal = new int[tQ];
		for(int i=0; i<tQ; i++)
		{
			Qtotal[i]=qtotals[i];
		}

	    
	}

	void Print()
	{
		cout<<RollNo<<"\t"<<FirstName<<" "<<LastName<<"\t";
		for(int k=0; k<tQ; k++)
		{
			cout<<QMarks[k]<<"\t";
		}
		for(int k=0; k<tA; k++)
		{
			cout<<aMarks[k]<<"\t";
		}
		cout<<total;
	    cout<<endl;
	}

	~StudentEvaluation()
	{
		if(FirstName!=0)
			delete[] FirstName;
		if(LastName!=0)
			delete[] LastName;
		if(QMarks!=0)
			delete[] QMarks;
		if(aMarks!=0)
			delete[] aMarks;
		//Deallocate memory yourself
	}

	void PrintingofSearchStudent()
	{
		int total1=0;
		int TOTAL=0;
		cout<<"Student Information:"<<endl;
		cout<<"Roll no:\t"<<RollNo;
		cout<<endl;
		cout<<"Name:\t\t"<<FirstName<<" "<<LastName;
		cout<<endl;
		cout<<"Quizzes Marks:"<<endl;
		for(int i=0; i<tQ;i++)
		{
			cout<<"\t\tQ"<<i+1<<"\t\t"<<QMarks[i]<<"/"<<Qtotal[i];
			total1=total1+QMarks[i];
			TOTAL=TOTAL+Qtotal[i];
			cout<<endl;
		}
		cout<<"Assignment Marks:"<<endl;
		for(int i=0; i<tA;i++)
		{
			cout<<"\t\tA"<<i+1<<"\t\t"<<aMarks[i]<<"/"<<Atotal[i];
			total1=total1+aMarks[i];
			TOTAL=TOTAL+Atotal[i];
			cout<<endl;
		}
		cout<<"Total:"<<endl;
		cout<<"\t\t\t\t"<<total1<<"/"<<TOTAL;
		
	}
	StudentEvaluation(const StudentEvaluation& RHS)
	{	
		for(int i = 0; i < 9; i++)
		{
			RollNo[i] = RHS.RollNo[i];
		}
		FirstName =  helper::getstringfrombuffer(RHS.FirstName);
		LastName =  helper::getstringfrombuffer(RHS.LastName);
		QMarks = new int[tQ];
		aMarks = new int[tA];
		for(int i = 0; i < tQ; i++)
		{
			QMarks[i] = RHS.QMarks[i];
		}
		for(int i = 0; i < tA; i++)
		{
			aMarks[i] = RHS.aMarks[i];
		}
		total = RHS.total;
	}


	StudentEvaluation& operator=(const StudentEvaluation& RHS)
	{
		if(&RHS != this)
		{
			for(int i = 0; i < 9; i++)
			{
				RollNo[i] = RHS.RollNo[i];
			}
			delete[] FirstName;
			FirstName=0;
			delete[] LastName;
			LastName=0;
			FirstName =  helper::getstringfrombuffer(RHS.FirstName);
			LastName =  helper::getstringfrombuffer(RHS.LastName);
			delete[] QMarks;
			QMarks=0;
			delete[] aMarks;
			aMarks=0;
			QMarks = new int[tQ];
			aMarks = new int[tA];
			for(int i = 0; i < tQ; i++)
			{
				QMarks[i] = RHS.QMarks[i];
			}
			for(int i = 0; i < tA; i++)
			{
				aMarks[i] = RHS.aMarks[i];
			}
			total = RHS.total;
		}
		return *this;
	}
	static void DeleteStaticArrays()
	{
		if(Qtotal)
		{
			delete[] Qtotal;
			Qtotal=0;
		}
		if(Atotal)
		{
			delete[] Atotal;
			Atotal=0;
		}
	}
};


int StudentEvaluation::totalstudents = 0;
int StudentEvaluation::tQ = 0;
int StudentEvaluation::tA = 0;
int* StudentEvaluation:: Atotal=0;
int* StudentEvaluation:: Qtotal=0;


StudentEvaluation* ReadFromFile()
{
	 int totalstudents;
	 int tA;
	 int tQ;
	ifstream fin;
	fin.open("gradesheet.txt");
	fin>>totalstudents;
	StudentEvaluation* arr = new StudentEvaluation[totalstudents];
	fin>>tQ;
	fin>>tA;
	int* qTotals = new int[tQ];
	for(int i=0; i<tQ; i++)
	{
		fin>>qTotals[i];
	}

	int* aTotals = new int[tA];
	for(int i=0; i<tA; i++)
	{
		fin>>aTotals[i];
	}

	arr->SetValues(totalstudents,tQ,tA,qTotals, aTotals); // setting the values

	for(int i=0; i<totalstudents; i++)
	{
		arr[i].ReadFromFileE(fin);
	}
	delete [] qTotals;
	qTotals=0;
	delete [] aTotals;
	aTotals=0;
	return arr;
	

}

void PrintALL(StudentEvaluation* List)
{
	int totalstud=StudentEvaluation::Gettotalstudents();
	for(int i=0; i<totalstud; i++)
	{
		List[i].Print();
	}
}

void Sortlist(StudentEvaluation* list)
{
	StudentEvaluation temporary;
	int i,j;
	int totalstud=StudentEvaluation::Gettotalstudents(); 
	for(i=0; i<totalstud-1; i++)
	{
		for(j=0; j<totalstud-1-i; j++)
		{
			if(list[j].StudentEvaluation::Gettotal() > list[j+1].StudentEvaluation::Gettotal())
			{
				temporary=list[j+1];
				list[j+1]=list[j];                 //sorting algorithm
				list[j]=temporary;
				
			}
		}
	}

}
void SearchStudentByRollNo(StudentEvaluation* studentList, char* tofindrollno)
{
	int totalstud=StudentEvaluation::Gettotalstudents();
	bool check=false;
	int F=0;
	for(int i=0; i<totalstud;i++)
	{
		if(helper::SEARCHSTRING(studentList[i].StudentEvaluation::Getrollno(), tofindrollno)==true)
		{
			check=true;
			F=i;
		}
	}

	if(check==true)
	{
		studentList[F].PrintingofSearchStudent();
	}
	else
	{
		cout<<"Student not Found";
	}
	cout<<endl;
    
}
void PrintStatistics(StudentEvaluation* studentList)//Global
{
	int size=studentList->tQ+studentList->tA;
	int* arrmin=new int[size];
	int totalstud=studentList->totalstudents;
	int qmin,amin;
	int k=0;
    for(int j=0;  j<studentList->tQ; j++)
	{
		qmin=studentList[0].QMarks[j];
		for(int i=0; i<totalstud; i++)
	    {
			if(studentList[i].QMarks[j]<qmin)
			{
				qmin=studentList[i].QMarks[j];                           
			}
		}
		arrmin[k]=qmin;                    //Finding minimum of each quiz and saving it in an array
		k++;
	}

	for(int j=0;  j<studentList->tA; j++)
	{
		amin=studentList[0].aMarks[j];
		for(int i=0; i<totalstud; i++)
	    {
			if(studentList[i].aMarks[j]<amin)
			{
				amin=studentList[i].aMarks[j];
			}
		}
		arrmin[k]=amin;                     //Finding minimum of each assighnment and saving it in an array
		k++;
	}
	int* arrmax=new int[size];
	int amax, qmax;
	k=0;
    for(int j=0;  j<studentList->tQ; j++)
	{
		qmax=studentList[0].QMarks[j];
		for(int i=0; i<totalstud; i++)
	    {
			if(studentList[i].QMarks[j]>qmax)
			{
				qmax=studentList[i].QMarks[j];
			}
		}
		arrmax[k]=qmax;                           //Finding maximum of each quiz and saving it in an array
		k++;
	}

	for(int j=0;  j<studentList->tA; j++)
	{
		amax=studentList[0].aMarks[j];
		for(int i=0; i<totalstud; i++)
	    {
			if(studentList[i].aMarks[j]>amax)
			{
				amax=studentList[i].aMarks[j];
			}
		}
		arrmax[k]=amax;                                     //Finding maximum of each assighnment and saving it in an array
		k++;
	}
	int* arravg=new int[size];
	int aavg, qavg, atotal, qtotal;
	k=0;
    for(int j=0;  j<studentList->tQ; j++)
	{
		qtotal=0;
		for(int i=0; i<totalstud; i++)
	    {
			qtotal=qtotal+studentList[i].QMarks[j];
		}
		qavg=qtotal/totalstud;
		arravg[k]=qavg;                                    //Finding average of each quiz and saving it in an array
		k++;
	}
	for(int j=0;  j<studentList->tA; j++)
	{
		atotal=0;
		for(int i=0; i<totalstud; i++)
	    {
			atotal=atotal+studentList[i].aMarks[j];
		}
		aavg=atotal/totalstud;
		arravg[k]=aavg;                                    //Finding average of each quiz and saving it in an array
		k++;
	}
	cout<<"-----------------------------------------------------Class Statistics-----------------------------------------------"<<endl;
	cout<<"                Q1\tQ2\tQ3\tQ4\tA1\tA2\tA3\tA4"<<endl;
	cout<<"Total:  \t";
    for(int i=0; i<studentList->tQ; i++)
	{
		cout<<studentList->Qtotal[i]<<"\t";
	}
	for(int i=0; i<studentList->tA; i++)
	{
		cout<<studentList->Atotal[i]<<"\t";
	}
	cout<<endl;
	cout<<"Maximum:\t";
    for(int i=0; i<size; i++)
	{
		cout<<arrmax[i]<<"\t";
	}
	cout<<endl;
	cout<<"Minimum:\t";
    for(int i=0; i<size; i++)
	{
		cout<<arrmin[i]<<"\t";
	}
	cout<<endl;
	cout<<"Average:\t";
    for(int i=0; i<size; i++)
	{
		cout<<arravg[i]<<"\t";
	}
	cout<<endl;
	delete []arrmax;
	arrmax=0;
	delete []arrmin;
	arrmin=0;
	delete []arravg;
	arravg=0;

}

void main(){

	StudentEvaluation* studentList = ReadFromFile();
	cout<<endl<<endl;
	cout<<"-------------------------------------------------Data Read from File---------------------------------------------"<<endl;
	cout<<"Roll No.\tName\t\tQ1\tQ2\tQ3\tQ4\tA1\tA2\tA3\tA4\tTotal"<<endl;
	PrintALL(studentList);
	cout<<endl<<endl;


	Sortlist(studentList);
	cout<<"-----------------------------------------------------------Sorted List--------------------------------------------"<<endl;
	cout<<"Roll No.\tName\t\tQ1\tQ2\tQ3\tQ4\tA1\tA2\tA3\tA4\tTotal"<<endl;
	PrintALL(studentList);
	cout<<endl<<endl;


	cout<<"----------------------------------------------------Student Information--------------------------------------"<<endl;
	char tofindrollno[]= {'1','5','L','-','1','2','3','4','\0'};
	cout<<endl<<endl;
	cout<<"Enter Student Roll No:\t"<<tofindrollno<<endl<<endl;
	SearchStudentByRollNo( studentList,tofindrollno);

    char tofindrollno1[]= {'1','5','L','-','4','0','2','3','\0'};
	cout<<endl<<endl;
	cout<<"Enter Student Roll No:\t"<<tofindrollno1<<endl<<endl;
	SearchStudentByRollNo(studentList,tofindrollno1);
	PrintStatistics(studentList);
	

	if(studentList)
		delete[] studentList;
	studentList=0;
	StudentEvaluation::DeleteStaticArrays();
	system("pause");
	

}