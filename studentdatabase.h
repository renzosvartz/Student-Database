/*Program typdefs*/
typedef struct classes
{
        char courseName[5];
        int courseID;
        int courseCRN;
} Course;
typedef Course *CoursePTR;
typedef struct scholar
{
        int studentID;
        char firstName[100];
        char lastName[100];
        int nCourses;
        Course list[5];
        struct scholar *next;
} Student;
typedef Student *StudentPTR;

/*Program function prototypes*/
//function insertStudent saves a new students data in the student linked list
void insertStudent(StudentPTR *students);
//function getStudentID gets the students ID number
void getStudentID(StudentPTR *student,int *);
//function getFirstName gets the student's first name
void getFirstName(char firstName[]);
//function getLastName gets the student's last name
void getLastName(char lastName[]);
//function getnCourses gets the number of courses a student will have
void getnCourses(int *nCourses);
//function getCourses saves all of the courses a student will be assigned
void getCourses(Course list[], int nCourses);
//function getCourseName gets the course name
void getCourseName(char courseName[]);
//function getCourseID gets the course ID
void getCourseID(int *idNumber);
//function getCourseCRN gets the course CRN
void getCourseCRN(int *CRN);
//function deleteStudent deletes a student from the linked list
void deleteStudent(StudentPTR *students);
//function displayDatabase prints out the student information in the database
void displayDatabase(StudentPTR students);
//displayOptions prints out menu
void displayOptions();
//function getOption returns the users choice of options
int getOption();
//function retry prompts the user to choose either retrying to save an input or to save the input
char retry();
//inputErrorChecking checks input for errors and prints feedback
int inputErrorChecking();
//clearLine clears lines up until newline or end-of-file to prevent errors
void clearLine();
