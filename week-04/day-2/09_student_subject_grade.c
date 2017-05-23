#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {MATH, HISTORY, ENGLISH, SCIENCE}Subject;

typedef struct {
    Subject subject;
    int value;
}Grade;

typedef struct {
    char name[128];
    int age;
    Grade* grades;
    int grade_count;
}Student;

// TODO:
// Create a function the constructs a Student (returns a pointer to a new student)
// It should take it's name and it's age as parameter
// It should allocate 5 grades
// It should set the grade_count to 0
Student* konstrukt(int kor, char*nev)
{
	Student* s=(Student*) malloc(sizeof(Student));
	strcpy(s->name,nev);
	s->age = kor;
	s->grades = (Grade* )calloc(5, sizeof(Grade)) ;   
	s->grade_count = 0;
	return s;
}
// TODO:
// Create a function that takes 3 parameters:
// A pointer to a Student
// A Subject
// An int (1-5)
// It should set the last grade's values with the given arguments
void setgrade(Student*stu, Subject sub, int num )
{
	Grade* gr = stu->grades;
	gr += stu->grade_count-1;
	gr->subject = sub;
	gr->value = num;
}
// TODO:
// Create a function that takes a Student as a pointer and returns the subject
// that the student has worst grade in
Subject* worstgrade(Student *stu)
{
	int worst = 6;
	Subject *sub, bla;
	Grade *gr = stu->grades;
	for (int i=0; i< stu->grade_count; i++) {
		//printf("targy: jegy: %d \n",gr->value);
		printf("valami "); //fflush(stdio);
		if(gr->value < worst) {
			worst = gr->value;
			*sub = gr->subject;
		}
		gr++;
	}
	printf("legszarabb tárgy: %d jegy: %d \n",(int)*sub, worst);
	//bla= *sub;
	return sub;
}


void deconstruct(Student*stu)
{
	free(stu->grades);
	free(stu);
}
// TODO:
// Create a function that deconstructs a Student
// It should take a pointer that points to the student
// It should free each Grade and the Student itself

int main() {
//printf("%s\n", (char*)struct Subject[2]);
	Student *s=konstrukt(23, "Tomi");
	
	s->grade_count++;
	setgrade(s,MATH,3);
	s->grade_count++;
	setgrade(s,ENGLISH,1);
	s->grade_count++;
	setgrade(s,HISTORY,2);
	s->grade_count++;
	setgrade(s,SCIENCE,2);
	
	Subject *sub;
	sub = worstgrade(s);
	//{MATH, HISTORY, ENGLISH, SCIENCE}Subject;
	printf("legrosszabbul sikerult targy: %d\n", (Subject)*sub);
	deconstruct(s);
    return 0;
}
