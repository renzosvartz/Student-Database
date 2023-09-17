//Renzo Alejo Moron-Svartz
//Project 7 Student database
//Project 7 is a student database created with structures. The user
//may insert or delete a student from the database, and display the database.
//Note: After extensive testing, I believe this program is void of all input errors.
//Note 2: There are some code segments that seem similar among functions,
//and they may be replaced by functions. Due to priorities, I will be creating the functions in the future.

/*Program includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studentdatabase.h"

/*Global variable for number of students in the database*/
int numOfStudents = 0;

//main makes funtion calls to all other fundamental functions to this program's functionality (a student database)
int main(void)
{
	/*Variable definitions*/
	int option = 0; //the user's choice for the menu options
	StudentPTR linkedlistStudents = NULL; //linked list of students
	
	/*Welcome*/
	puts("");
	fprintf(stdout, "Welcome to the student database for Montgomery College.\n");
	puts("");
	
	/*Menu-driven user functions*/
	while (option != 8)
	{
		/*Prompt user and collect option*/
	        option = getOption();

		/*Feedback*/
		fprintf(stdout, "? %d\n\n", option);

		switch (option)
		{
			case 1:insertStudent(&linkedlistStudents);
				break;
			case 2:deleteStudent(&linkedlistStudents);
				break;
			case 3:displayDatabase(linkedlistStudents);
				break;
			case 4:exit(1);
				break; 
			default:fprintf(stderr, "Error: Option invalid. Try again.\n\n");
				break;
		}
	}		
}//end main	

//function insertStudent saves a new students data in the student linked list
void insertStudent(StudentPTR *students)
{
	/*Error-Checking*/
	if (numOfStudents == 5)
	{
		fprintf(stderr, "Error: Database full.\n\n");
	}
	else
	{
		/*Allocate memory*/
		StudentPTR newStudent = (Student *) malloc(sizeof(Student));

		/*Error-Checking*/
		if (newStudent == NULL)
		{
			fprintf(stderr, "Error: Could not allocated memory. Exitting program.\n\n");
			exit(1);
		}
		else
		{
			/*Collect data*/
			getStudentID(students, &(newStudent->studentID));
			getFirstName(newStudent->firstName);
			getLastName(newStudent->lastName);
			getnCourses(&(newStudent->nCourses));
			getCourses(newStudent->list, newStudent->nCourses);

			/*Store student in unsorted list*/
			newStudent->next = *students;
			*students = newStudent;
			fprintf(stdout, "Success: Student saved into database\n\n");
		}
	}
}//end insertStudent

//function getStudentID gets the students ID number
void getStudentID(StudentPTR *student, int *idNumber)
{
	char tryAgain = 'y';
	int flag = 0; //error-flag
	int c; //error

	while (tryAgain != 'n')
	{
		do
		{
			/*Error-Checking*/
            	    	do
               	 	{
				/*Prompt user*/
				fprintf(stdout, "Enter the student ID number: ");
               	         	flag = inputErrorChecking();
               	 	} while (flag);

			/*Collect student ID*/
               	 	fscanf(stdin, "%d", idNumber);
	
			flag = 0;
			if ((c = getc(stdin)) != '\n')
			{
				fprintf(stderr, "Error: Text found in the input. Try again.\n\n");
				clearLine();
				flag = 1;
			}
		} while (flag);

		/*Checking unique ID*/
 	 	StudentPTR currentID = *student;
    		while (currentID != NULL && currentID->studentID != *idNumber)
	  	{
		  	currentID = currentID->next;
	  	}
		if (currentID == NULL)
		{
			tryAgain = retry(); //ID Unique
		}
	  	else
     		{
        		fprintf(stderr, "Error: Student ID taken. Try again.\n\n"); //ID in use
     		}
	}
	numOfStudents++;
	fprintf(stdout, "Success: Student's ID number saved.\n\n");
	clearLine();
}//end getIDnumber

//function getFirstName gets the student's first name
void getFirstName(char firstName[])
{
	char tryAgain = 'y';
	int c; //error
	int flag = 0; //error flag
	
	while (tryAgain != 'n')
	{
		do
                {
                        /*Prompt user*/
                        fprintf(stdout, "Enter the student's first name (99 character limit - extra characters are ignored): ");
			
			/*Error-Checking*/
                        flag = 0;
                        if ((c = getc(stdin)) == '\n')
                        {
                                fprintf(stderr, "Error: Empty input.\n\n");
                        }
                        else
                        {
                                ungetc(c, stdin);
				/*Collect first name*/
                                fgets(firstName, 100, stdin);
                                flag = 1;
                        }
                } while(!flag);

                /*Error-Checking*/
                if (strlen(firstName) == 99)
                {
                        if (firstName[98] == '\n')
                        {
                                /*Name handling*/
                                firstName[98] = '\0';
                        }
                        else
                        {
                                clearLine();
                        }
                }
                else
                {
                        /*Name handling*/
                        firstName[strlen(firstName) - 1] = '\0';
                }

                /*Error-Checking*/
                tryAgain = retry();
	}
	fprintf(stdout, "Success: Student's first name saved.\n\n");
	clearLine();
}//end getFirstName

//function getLastName gets the student's last name
void getLastName(char lastName[])
{
	char tryAgain = 'y';
	int c; //error
	int flag = 0; //error flag

	while (tryAgain != 'n')
	{
		do
                {
                        /*Prompt user*/
                        fprintf(stdout, "Enter the student's last name (99 character limit - extra characters are ignored): ");

                        flag = 0;

			/*Error-Checking*/
                        if ((c = getc(stdin)) == '\n')
                        {
                                fprintf(stderr, "Error: Empty input.\n\n");
                        }
                        else
                        {
                                ungetc(c, stdin);
				/*Collect last name*/
                                fgets(lastName, 100, stdin);
                                flag = 1;
                        }
                } while(!flag);

		/*Error-Checking*/
                if (strlen(lastName) == 99)
                {
                        if (lastName[98] == '\n')
                        {
                                /*Name handling*/
                                lastName[98] = '\0';
                        }
                        else
                        {
                                clearLine();
                        }
                }
                else
                {
                        /*Name handling*/
                        lastName[strlen(lastName) - 1] = '\0';
                }

                /*Error-Checking*/
                tryAgain = retry();
	}
	fprintf(stdout, "Success: Student's last name saved.\n\n");
	clearLine();
}//end getLastName

//function getnCourses gets the number of courses a student will have
void getnCourses(int *nCourses)
{
	char tryAgain = 'y';
	int flag = 0; //error flag
	int c; //error	

	while (tryAgain != 'n')
	{

		do
                {
                        /*Error-Checking*/
                        do
                        {
                                /*Prompt user*/
                                fprintf(stdout, "Enter the number of courses the student is taking (0 to 5): ");
				flag = inputErrorChecking();
                        } while (flag);

                        /*Collect number of courses a student will be taking*/
                        fscanf(stdin, "%d", nCourses);

                        flag = 0;
			/*Error-Checking*/
                        if ((c = getc(stdin)) != '\n')
                        {
                                fprintf(stderr, "Error: Text found in the input. Try again.\n\n");
                                clearLine();
                                flag = 1;
                        }
			else
			{
				if (*nCourses < 0 || *nCourses > 5)
		                {
               	         		fprintf(stderr, "Error: Invalid number of courses. Try again.\n\n");
					flag = 1;
                		}
                		else
                		{
                        		tryAgain = retry();
                		}

			}
                } while (flag);
	}
	fprintf(stdout, "Success: Student's number of courses saved.\n\n");
	clearLine();
}//end getnCourses

//function getCourses saves all of the courses a student will be assigned
void getCourses(Course list[], int nCourses)
{
	int i = 0; //counter

	while (i < nCourses)
	{
		/*Allocate memory for new course*/
		CoursePTR newCourse = (Course *) malloc (sizeof(Course));

		/*Collect data*/
		getCourseName(newCourse->courseName);
		getCourseID(&(newCourse->courseID));
		getCourseCRN(&(newCourse->courseCRN));
		
		/*Store course in course list*/
		list[i++] = *newCourse;
	}
}//end getCourses

//function getCourseName gets the course name
void getCourseName(char courseName[])
{
        char tryAgain = 'y';
	int c; //error
	int flag = 0; //error flag

        while (tryAgain != 'n')
        {
		do
		{
			/*Prompt user*/
	                fprintf(stdout, "Enter the course name (4 character limit - extra characters are ignored): ");

			/*Error-Checking*/
			flag = 0;
			if ((c = getc(stdin)) == '\n')
			{
				fprintf(stderr, "Error: Empty input.\n\n");
			}
			else
			{
				ungetc(c, stdin);
				/*Collect course name*/
				fgets(courseName, 5, stdin);
				flag = 1;
			}
		} while(!flag);
		
		/*Error-Checking*/
                if (strlen(courseName) == 4)
                {
			if (courseName[3] == '\n')
			{
				/*Name handling*/
                        	courseName[3] = '\0';
			}
			else
			{
                        	clearLine();
			}
                }
		else
		{
			/*Name handling*/
                	courseName[strlen(courseName) - 1] = '\0';
		}

		/*Error-Checking*/
                tryAgain = retry();
        }
        fprintf(stdout, "Success: Course name saved.\n\n");
	clearLine();
}//end getCourseName

//function getCourseID gets the course ID
void getCourseID(int *idNumber)
{
        char tryAgain = 'y';
	int flag = 0; //error flag
	int c; //error

        while (tryAgain != 'n')
        {
		do
                {
                        /*Error-Checking*/
                        do
                        {
                                /*Prompt user*/
                                fprintf(stdout, "Enter the course ID number: ");
				flag = inputErrorChecking();
                        } while (flag);

                        /*Collect course ID*/
                        fscanf(stdin, "%d", idNumber);

                        flag = 0;
			
			/*Error-Checking*/
                        if ((c = getc(stdin)) != '\n')
                        {
                                fprintf(stderr, "Error: Text found in the input. Try again.\n\n");
                                clearLine();
                                flag = 1;
                        }
                } while (flag);
                tryAgain = retry();
        }
        fprintf(stdout, "Success: Course ID number saved.\n\n");
	clearLine();
}//end getCourseID

//function getCourseCRN gets the course CRN
void getCourseCRN(int *CRN)
{
        char tryAgain = 'y';
	int flag = 0; //error flag
	int c; //error

        while (tryAgain != 'n')
        {
		do
                {
                        /*Error-Checking*/
                        do
                        {
                                /*Prompt user*/
                                fprintf(stdout, "Enter the course registration number: ");
                                flag = inputErrorChecking();
                        } while (flag);

                        /*Collect CRN*/
                        fscanf(stdin, "%d", CRN);

                        flag = 0;

                        /*Error-Checking*/
                        if ((c = getc(stdin)) != '\n')
                        {
                                fprintf(stderr, "Error: Text found in the input. Try again.\n\n");
                                clearLine();
                                flag = 1;
                        }
                } while (flag);
                tryAgain = retry();
        }
        fprintf(stdout, "Success: Course CRN number saved.\n\n");
	clearLine();
}//end getCourseCRN

//function displayDatabase prints out the student information in the database
void displayDatabase(StudentPTR students)
{
	int i = 0;
	int courses;

	if (students == NULL)
	{
		fprintf(stderr, "Error: Database empty.\n");
	}
	
	/*Print*/
	while(students != NULL)
  	{
		/*Information*/
	    	fprintf(stdout, "Student ID: %d\nStudent Name: %s %s\nNumber of Courses: %d\n", students->studentID, students->firstName, students->lastName, students->nCourses);
   	
		/*Courses*/
		courses = students->nCourses;
	 	while (courses-- > 0)
    		{
      			fprintf(stdout, "Course Name: %s\nCourse ID: %d\nCourse CRN: %d\n", students->list[i].courseName, students->list[i].courseID, students->list[i].courseCRN);
  			i++;
    		}
		students = students->next;
		i = 0;
		puts("");
  	}
}//end displayDatabase

//function deleteStudent deletes a student from the linked list
void deleteStudent(StudentPTR *students)
{
	int idNumber = 0;
	int flag = 0; //error flag
	int c; //error
	int found = 0; //deletion flag
	StudentPTR currentStudent = *students;

	if (currentStudent == NULL)
	{
		fprintf(stderr, "Error: Database empty.\n\n");
	}
	else
	{
		/*Find student*/
		while (found == 0)
		{
			do
	                {
                        	/*Error-Checking*/
                        	do
                        	{
					currentStudent = *students;
                                	/*Prompt user*/
                                	fprintf(stdout, "Options: ");
                                	while(currentStudent != NULL)
                                	{
                                        	fprintf(stdout, "%d%c ", currentStudent->studentID, (currentStudent->next == NULL ? '\n' : ','));
                                        	currentStudent = currentStudent->next;
                                	}
                                	flag = inputErrorChecking();
                        	} while (flag);

                        	/*Collect student ID*/
                        	fscanf(stdin, "%d", idNumber);

         	               	flag = 0;
	
                        	/*Error-Checking*/
                        	if ((c = getc(stdin)) != '\n')
                        	{
                                	fprintf(stderr, "Error: Text found in the input. Try again.\n\n");
                             		clearLine();
                                	flag = 1;
                        	}
                	} while (flag);

			/*First student deletion*/
			if (idNumber == (*students)->studentID)
			{
				StudentPTR tempPTR = *students;
        		        *students = (*students)->next;
	               	 	free(tempPTR);
				found = 1;
				fprintf(stdout, "Success: Student assigned student ID %d deleted.\n\n", idNumber);
			}
			else
			{
				/*Allocate memory*/
               			StudentPTR previousStudent = *students;
               		 	StudentPTR currentStudent = (*students)->next;
                		/*Find the student being deleted from the linked list*/
                		while (currentStudent != NULL && currentStudent->studentID != idNumber)
                		{
                        		previousStudent = currentStudent;
                        		currentStudent = currentStudent->next;
                		}		
               	 		/*Deletion*/
				if (idNumber == currentStudent->studentID)
				{
        				StudentPTR tempPTR = currentStudent;
   	       		      		previousStudent->next = currentStudent->next;
        		        	free(tempPTR);
					found = 1;
					fprintf(stdout, "Success: Student assigned student ID %d deleted.\n\n", idNumber);
				}
				else
				{
					fprintf(stderr, "Error: Student ID was not in the database. Try again.\n\n");
				}
			}
		}
	}
}//end deleteStudent

//function getOption returns the users choice of options
int getOption()
{
	int option = 0;
	int flag = 0; //error flag
	int c; //error

	/*Recoverable data collection*/
	while (option < 1 || option > 8)
	{
		do
                {
                        /*Error-Checking*/
                        do
                        {
                                /*Prompt user*/
                                displayOptions();
				flag = inputErrorChecking();
                        } while (flag);

                        /*Collect option*/
                        fscanf(stdin, "%d", &option);

                        flag = 0;

                        /*Error-Checking*/
                        if ((c = getc(stdin)) != '\n')
                        {
                                fprintf(stderr, "Error: Text found in the input. Try again.\n\n");
                                clearLine();
                                flag = 1;
                        }
			else
			{
				if (option < 1 || option > 8)
				{
					fprintf(stderr, "Error: Invalid option. Try again.\n\n");
					flag = 1;
				}
			}
                } while (flag);
	}
	return option;
}//end getOptions
 
//function retry prompts the user to choose either retrying to save an input or to save the input
char retry()
{
	char option = 'z';
	int c; //error

	/*Error-Checking*/
        while (option != 'y' && option != 'n')
        {
		/*Prompt*/
                fprintf(stdout, "Do you want to try again? Type \'y\' to try again or \'n\' to save your input: ");

		/*Collect option*/
              	fscanf(stdin, "%c", &option);
		//option = fgetc(stdin);		

		/*Error-Checking*/
		if (option != 'y' && option != 'n')
		{
			fprintf(stderr, "Error: Invalid option. Try again.\n\n");
			if (option != '\n')
			{
				clearLine();
			}
		}
		else
		{
			if ((c = getc(stdin)) != '\n')
                        {
                                fprintf(stderr, "Error: Extra text found in the input. Try again.\n\n");
				option = 'z';
				clearLine();
                        }
			else
			{
				ungetc(c, stdin);
			}
		}
        }
	if (option == 'y')
	{
		clearLine();
	}
	puts("");
	return option;
}//end retry()
 
//inputErrorChecking checks input for errors and prints feedback
int inputErrorChecking()
{
	int c; //error
	int flag = 0; //error flag

	/*Error-Checking*/
        while (((c = getc(stdin)) == ' ' || c == '\t' || c == '\n' || isalpha(c) || ispunct(c)) && c != EOF)
        {
              	if (isalpha(c))
		{
			fprintf(stderr, "Error: Found text in the input. Try again.\n\n");
			//flag = 1;
			clearLine();
			return 1;
			//break;
		}
		else if (ispunct(c))
		{
			fprintf(stderr, "Error: Found symbols in the input. Try again.\n\n");
			//flag = 1;
			clearLine();
			return 1;
			//break;
		}
		else if (c == '\n')
		{
			fprintf(stderr, "Error: Empty input.\n\n");
			return 1;
		}
        }
	ungetc(c, stdin);
	return 0;
	//return flag;
}//end inputErrorChecking

//clearLine clears lines up until newline or end-of-file to prevent errors
void clearLine()
{
	int c; //trash
	while ((c = getc(stdin)) != '\n' && c != EOF)
		;
}//end clearLine

//displayOptions prints out menu
void displayOptions(void)
{
        fprintf(stdout, "Type 1-4 to select an option.\n");
        fprintf(stdout, "1. Insert a student into the database\n");
        fprintf(stdout, "2. Delete a student from the database\n");
        fprintf(stdout, "3. Display the database\n");
        fprintf(stdout, "4. Exit the program\n\n");
}//end displayOptions
