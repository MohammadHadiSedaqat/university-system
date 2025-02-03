Report on the Report Card Issuance Project:   *Date: 2025/02/03*
Overview
The code can be divided into four main sections. Upon running the program, the following options are displayed:
 
# Option 1: Add a Student
After selecting this option, an array of the student's basic information is created. This includes:
 - Student's name
 - Student ID
 - Field of study 
 - Grade marks average
The function then allows the user to either enter the student's grades or return to the main menu:
Yes: If the user opts to enter grades, a new array is created to temporarily store the grades, number of units, and the desired course.
Then, the “studentMarkReadline” function is called to receive and store the grades in the “student_grades” array. The student's GPA
is calculated and stored in the “students” array along with the other information. The “sortStore” function is then called to sort
the students in descending order by GPA and store them in the appropriate file based on the field declared by the user. Finally,
the “reportCardMaker” function is called to store all details, including grades, in a file named after the student's student ID. 
No: If the user opts not to enter grades, the GPA defaults to zero. The “studentWithoutMarks” function is called to save the student
information without grades in a file named after the student's ID.
- In both cases, a file is created according to the field, where student numbers are stored to be used in the following sections. So stay tuned. 😊
# Option 2: Student List
This section includes six subsections that allow the user to filter students by field or display all students. There is also an option to return to the main menu. For each step:
 - The file is opened
 - Information is read line by line
 - The information is quickly printed
 - This process continues until all information is read
 
# Option 3: Issuing a Report Card
The user filters the students by major, and a file variable “computerID” is created. The “MAJOR_LIST” file is opened. If it does not exist,
an appropriate message is displayed, and the user returns to the main menu.
If the file exists, it checks whether the student file is saved. If it is not saved, an appropriate message is displayed, and the user returns
to the main menu. If the student file exists, the student IDs are listed, and a student ID is received from the user. It checks whether a file
named after the entered student ID exists. If it does, the selected ID’s report card will be printed.
# Option 4: Exit
Exit the program.
