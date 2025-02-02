#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;
namespace fs = filesystem;

int n;
bool stringValid(const string &textInput) {
    for (char text : textInput) {
        if (!isalpha(text) && text != ' ')
            return false;
    }
    return true;
} // برسی می کند که ورودی آیا رشته است یا خیر
bool majorValid(const string &textInput) {
    string majors[4] = {"Computer", "Industrial", "Electrical", "Mechanical"};
    for (int i = 0; i < 4; i++) {
        if (textInput == majors[i]) {
            return true;
            break;
        }
    }
    return false;
} // برسی می کند آیا رشته درست وارد شده یا خیر
bool numbersValid (const string &textInput) {
    return !textInput.empty() && all_of(textInput.begin(), textInput.end(),::isdigit);
} // برسی می کند آیا ورودی عدد است یا خیر
bool doubleValid(const string &textInput) {
    istringstream iss(textInput);
    double number;
    char alphabet;
    return (iss >> number) && !(iss >> alphabet);
} // برسی می کند آیا در بخش نمره عدد وارد شده یا خیر
string marksMaker(const double mark) {
    string averageResult = to_string(mark);
    short decimal = averageResult.find('.');
    if (decimal != string::npos)
        averageResult = averageResult.substr(0, decimal + 3);
    return averageResult;
} // تعداد ارقام اعشار را ۲ تا قرار می دهد
struct StudentProperty
{
    string fullName; string id; string major;
}; // مشخصات اصلی دانشجو: نام‌، کد دانشجویی،‌ رشته
struct StudentMark
{
    string subject; string unit; double mark{};
}; // مشخصات درس، تعداد واحد، نمره درس دانشجو
void studentPropertyReadline(string personProperty[4])
{
    StudentProperty person;
    cout << "Enter Student's Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        getline(cin,person.fullName);
        if (stringValid(person.fullName))
            break;
        else
            cout << "Invalid Student's Name. Please enter a valid name (only characters): ";
    }
    cout << "Enter Student's ID: ";
    while (true) {
        getline(cin,person.id);
        if (numbersValid(person.id))
            break;
        else
            cout << "Invalid Student's ID. Please enter a valid ID (only numbers): ";
    }
    cout << "Entr Student's Major (Computer, Industrial, Electrical, Mechanical): ";
    while (true) {
        getline(cin,person.major);
        if (stringValid(person.major) && majorValid(person.major))
            break;
        else
            cout << "Invalid Student's Major. Please enter a valid major (from above majors with capital letter): ";
    }
    personProperty[0] = person.fullName; personProperty[1] = person.id; personProperty[2] = person.major;
} // ورودی مشخصات اصلی دانشجو: نام‌، کد دانشجویی،‌ رشته
void studentMarkReadline(string personMark[][3], string personProperty[4])
{
    StudentMark person;
    double average = 0;
    cout << "Enter the subject numbers: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cin >> n;
        if (numbersValid(to_string(n))) {
            if (n <= 10 && n >= 1)
                break;
            else
                cout << "Invalid number. Please enter a number between '1' and '10' ";
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << "number " << i + 1 << ": " << '\n';
        cout << "Enter the subject: ";
        if (i == 0)
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true) {
            getline(cin,person.subject);
            if (stringValid(person.subject))
                break;
            else
                cout << "Invalid Subject's Name. Please enter a valid name (only characters): ";
        }
        cout << "Enter the unit: ";
        while (true) {
            getline(cin,person.unit);
            if (numbersValid(person.unit))
                break;
            else
                cout << "Invalid Subject's unit. Please enter a valid unit (only numbers): ";
        }
        cout << "Enter the mark: ";
        string alterMark;
        while (true) {
            getline(cin,alterMark);
            if (doubleValid(alterMark)) {
                person.mark = stod(alterMark);
                break;
            }
            else
                cout << "Invalid Subject's mark. Please enter a valid mark (integer or double number): ";
        }
        personMark[i][0] = person.subject; personMark[i][1] = person.unit; personMark[i][2] = marksMaker(person.mark);
        average += person.mark;
    }
    average /= n;
    personProperty[3] = marksMaker(average);
    cout << "The student's properties and marks have been saved.\n" << endl;
} // ورودی مشخصات درس، تعداد واحد، نمره درس دانشجو
int getMajorCode(const string &major)
{
    if (major == "Computer") return 0;
    else if (major == "Industrial") return 1;
    else if (major == "Electrical") return 2;
    else if (major == "Mechanical") return 3;
    else return -1;
} // برسی مقدار عددی رشته
void writeToFile(fstream &file, const string &filename, const string &data)
{
    file.open(filename, ios::app);
    if (file.is_open())
    {
        file << data << endl;
        file.close();
    }
    else
        cout << "Error opening " << filename << "!\n";
} // مرتب‌ سازی لیست دانشجو ها
void sortStore(string students[][4], int count, fstream &Computer_list, fstream &Industrial_list, fstream &Electrical_list, fstream &Mechanical_list)
{
    // Sorting logic remains the same
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (stod(students[j][3]) < stod(students[j + 1][3]))
            {
                for (int k = 0; k < 4; k++)
                    swap(students[j][k], students[j + 1][k]);
            }
        }
    }
    // Store sorted students in respective files
    for (int i = 0; i < count; i++)
    {
        string data = students[i][0] + " / " + students[i][1] + " / " + students[i][2] + " / " + students[i][3];
        switch (getMajorCode(students[i][2]))
        {
            case 0: writeToFile(Computer_list, "Computer_list.txt", data); break;
            case 1: writeToFile(Industrial_list, "Industrial_list.txt", data); break;
            case 2: writeToFile(Electrical_list, "Electrical_list.txt", data); break;
            case 3: writeToFile(Mechanical_list, "Mechanical_list.txt", data); break;
        }
    }
} // ساخت لیست دانشجو ها
void reportCardMaker(string student[][4],string personMark[][3], int rsc)
{
    switch (getMajorCode(student[rsc][2]))
    {
        case 0:
        {
                fstream computer;
                computer.open(student[rsc][1]+".txt",ios::app);
                if (computer.is_open())
                {
                    computer << left << "Name: " << setw(30) << student[rsc][0] << "ID: " << setw(20) << student[rsc][1] << "\n"
                    << "Major: " << setw(28) << student[rsc][2] << "Average: " << setw(18) << student[rsc][3] << "\n";
                    computer << "-------------------------------------------------" << endl;
                    for (int i = 0; i < n; i++)
                        computer << left << "Subject: " << setw(13) << personMark[i][0] << "Unit: " << setw(10) << personMark[i][1] << "Mark: "<< setw(10) << personMark[i][2] << "\n";
                    computer.close();
                }
                fstream computerID;
                computerID.open("ComputerID_list", ios::app);
                if (computerID.is_open())
                    computerID << student[rsc][1] << '\n';
                computerID.close();
                break;
        }
        case 1:
        {
            {
                fstream industrial;
                industrial.open(student[rsc][1]+".txt", ios::app);
                if (industrial.is_open())
                {
                    industrial << left << "Name: " << setw(30) << student[rsc][0] << "ID: " << setw(20) << student[rsc][1] << "\n"
                    << "Major: " << setw(28) << student[rsc][2] << "Average: " << setw(18) << student[rsc][3] << "\n";
                    industrial << "-------------------------------------------------" << endl;
                    for (int i = 0; i < n; i++)
                        industrial << left << "Subject: " << setw(13) << personMark[i][0] << "Unit: " << setw(10) << personMark[i][1] << "Mark: "<< setw(10) << personMark[i][2] << "\n";
                    industrial.close();
                }
                fstream industrialID;
                industrialID.open("IndustrialID_list", ios::app);
                if (industrialID.is_open())
                    industrialID << student[rsc][1] << '\n';
                industrialID.close();
                break;
            }
        }
        case 2:
        {
            fstream electrical;
            electrical.open(student[rsc][1]+".txt", ios::app);
            if (electrical.is_open())
            {
                electrical << left << "Name: " << setw(30) << student[rsc][0] << "ID: " << setw(20) << student[rsc][1] << "\n"
                << "Major: " << setw(28) << student[rsc][2] << "Average: " << setw(18) << student[rsc][3] << "\n";
                electrical << "-------------------------------------------------" << endl;
                for (int i = 0; i < n; i++)
                    electrical << left << "Subject: " << setw(13) << personMark[i][0] << "Unit: " << setw(10) << personMark[i][1] << "Mark: "<< setw(10) << personMark[i][2] << "\n";
                electrical.close();
            }
            fstream electricalID;
            electricalID.open("ElectricalID_list", ios::app);
            if (electricalID.is_open())
                electricalID << student[rsc][1] << '\n';
            electricalID.close();
            break;
        }
        case 3:
        {
            fstream mechanical;
            mechanical.open(student[rsc][1]+".txt", ios::app);
            if (mechanical.is_open())
            {
                mechanical << left << "Name: " << setw(30) << student[rsc][0] << "ID: " << setw(20) << student[rsc][1] << "\n"
                << "Major: " << setw(28) << student[rsc][2] << "Average: " << setw(18) << student[rsc][3] << "\n";
                mechanical << "-------------------------------------------------" << endl;
                for (int i = 0; i < n; i++)
                    mechanical << left << "Subject: " << setw(13) << personMark[i][0] << "Unit: " << setw(10) << personMark[i][1] << "Mark: "<< setw(10) << personMark[i][2] << "\n";
                mechanical.close();
            }
            fstream mechanicalID;
            mechanicalID.open("MechanicalID_list", ios::app);
            if (mechanicalID.is_open())
                mechanicalID << student[rsc][1] << '\n';
            mechanicalID.close();
            break;
        }
    }
} // ساخت کارنامه دانشجو
void studentWithoutMarks(string students[][4],int rsc) {
    fstream major;
    major.open(students[rsc][1]+".txt", ios::app);
    if (major.is_open()) {
        major << "Name: " << students[rsc][0]<< " / " << "ID: " << students[rsc][1]<< " / "  << "Major: " << students[rsc][2] << " / " << "Average: " << students[rsc][3];
        major.close();
    }
    fstream list;
    list.open("students_without_marks", ios::app);
    if (list.is_open()) {
        list << students[rsc][1]<< '\n';
        list.close();
    }
} // ساخت فایل برای دانشجویان بدون نمره

int main()
{
    const int MAX_STUDENTS = 100;
    string students[MAX_STUDENTS][4]; // آرایه برای ذخیره موقت دانشجو ها
    int Registered_student_Count = 0; // تعداد دانش‌آموزان ثبت‌ شده
    fstream Computer_list;
    fstream Industrial_list;
    fstream Electrical_list;
    fstream Mechanical_list;

    while (true)
    {
        cout << "1. Add new student\n"
             << "2. Students list\n"
             << "3. Student without marks report\n"
             << "4. Report card\n"
             << "5. Exit\n"
             << "Enter your choice: ";

        int input_number;
        cin >> input_number;

        switch (input_number)
        {
            case 1: {
                        if (Registered_student_Count >= MAX_STUDENTS)
                        {
                            cout << "Maximum number of students reached!\n";
                            break;
                        }

                        studentPropertyReadline(students[Registered_student_Count]);

                        cout << "Do you want to add his/her grades? (y/n): ";
                        char yes_no;
                        cin >> yes_no;

                        if (yes_no == 'y' || yes_no == 'Y')
                        {
                            string student_grades[10][3]; // فرض کردیم حداکثر ۱۰ درس وجود دارد
                            studentMarkReadline(student_grades, students[Registered_student_Count]);
                            Registered_student_Count++;
                            sortStore(students,Registered_student_Count,Computer_list,Industrial_list,Electrical_list,Mechanical_list);
                            reportCardMaker(students, student_grades, Registered_student_Count-1);
                            n = 0;
                        }
                        else if (yes_no == 'n' || yes_no == 'N')
                        {
                            Registered_student_Count++;
                            students[Registered_student_Count][3] = "0"; // اگر نمره‌ای وارد نشد، معدل ۰
                            studentWithoutMarks(students, Registered_student_Count-1);
                            cout << "The student's properties with '0' average have been saved.\n" << endl;
                        }
                        else
                            cout << "Invalid input. Please enter 'y' or 'n'.\n";
                        break;
                    }
            case 2: {
                        int filter_input;
                        cout << "Press '1' to show all " << "\n"
                             << "Press '2' to filter by Computer Engineering" << "\t"
                             << "Press '3' to filter by Industrial Engineering" << "\n"
                             << "Press '4' to filter by Electrical Engineering" << "\t"
                             << "Press '5' to filter by Mechanical Engineering" << "\n"
                             << "press '6' to back to menu and main" << "\n";

                             while (cin >> filter_input)
                             {
                                if (filter_input > 6 || filter_input < 1)
                                    cout << "invalid input, Please enter a number between '1' to '6'." << "\n" << "Enter your choice: ";
                                else
                                    break;
                             }

                             if (filter_input == 6) break;
                             switch (filter_input)
                             {
                                case 1: {
                                            Computer_list.open("Computer_list.txt", ios::in);
                                                {
                                                    if(Computer_list.is_open())
                                                    {
                                                        string output_Computer;
                                                        while (getline (Computer_list, output_Computer))
                                                            cout << output_Computer << "\n";
                                                        Computer_list.close();
                                                    }
                                                }

                                            Industrial_list.open("Industrial_list.txt", ios::in);
                                                {
                                                    if(Industrial_list.is_open())
                                                    {
                                                        string output_Industrial;
                                                        while (getline(Industrial_list, output_Industrial))
                                                        {
                                                            cout << output_Industrial << "\n";
                                                        }
                                                        Industrial_list.close();
                                                    }
                                                }

                                            Electrical_list.open("Electrical_list.txt", ios::in);
                                                {   if(Electrical_list.is_open())
                                                    {
                                                        string output_Electrical;
                                                        while (getline(Electrical_list, output_Electrical))
                                                        {
                                                            cout << output_Electrical << "\n";
                                                        }
                                                        Electrical_list.close();
                                                    }
                                                }

                                            Mechanical_list.open("Mechanical_list.txt", ios::in);
                                                {   if(Mechanical_list.is_open())
                                                    {
                                                        string output_Mechanical;
                                                        while (getline(Mechanical_list, output_Mechanical))
                                                        {
                                                            cout << output_Mechanical << "\n";
                                                        }
                                                        Mechanical_list.close();
                                                    }
                                                }
                                    cout << '\n';
                                        break;
                                        }
                                case 2: {
                                            Computer_list.open("Computer_list.txt", ios::in);
                                            {
                                                if(Computer_list.is_open())
                                                {
                                                    string output_Computer;
                                                    while (getline(Computer_list, output_Computer))
                                                        cout << output_Computer << "\n";
                                                    Computer_list.close();
                                                }
                                            }
                                    cout << '\n';
                                        break;
                                        }
                                case 3: {
                                            Industrial_list.open("Industrial_list.txt", ios::in);
                                            {
                                                if(Industrial_list.is_open())
                                                {
                                                    string output_Industrial;
                                                    while (getline(Industrial_list, output_Industrial))
                                                        cout << output_Industrial << "\n";
                                                    Industrial_list.close();
                                                }
                                            }
                                    cout << '\n';
                                        break;
                                        }
                                case 4: {
                                            Electrical_list.open("Electrical_list.txt", ios::in);
                                            {   if(Electrical_list.is_open())
                                                {
                                                    string output_Electrical;
                                                    while (getline(Electrical_list, output_Electrical))
                                                        cout << output_Electrical << "\n";
                                                    Electrical_list.close();
                                                }
                                            }
                                    cout << '\n';
                                        break;
                                        }
                                case 5: {
                                            Mechanical_list.open("Mechanical_list.txt", ios::in);
                                            {   if(Mechanical_list.is_open())
                                                {
                                                    string output_Mechanical;
                                                    while (getline(Mechanical_list, output_Mechanical))
                                                        cout << output_Mechanical << "\n";
                                                    Mechanical_list.close();
                                                }
                                            }
                                    cout << '\n';
                                        break;
                                        }
                            }
                    break;
                    }
            case 3:
            {
                while (true) {
                    string id;
                    fstream major;
                    major.open("students_without_marks", ios::in);
                    if (!major) {
                        cout << "Not any Computer Student has been registered. Please enter '1' to register.";
                        cout << endl;
                        break;
                    }
                    if (major.is_open()) {
                        if (major.peek() == ifstream::traits_type::eof()) {
                            cout << "Not any Computer Student has been registered. Please enter '1' to register.";
                            cout << endl;
                            break;
                        }
                        else {
                            string line;
                            while (getline(major, line))
                                cout << line << "\n";
                            major.close();
                        }
                    }
                    cout << "Enter the id of student: ";
                    cin >> id;
                    id += ".txt";
                    if (fs::exists(id))
                    {
                        fstream idfile(id,ios::in);
                        if (idfile.is_open())
                        {
                            string line;
                            while (getline(idfile,line))
                                cout << line << "\n";
                            idfile.close();
                        }
                        cout << "\n";
                        break;
                    }
                }
                break;
            }
            case 4:
            {
                int filter_input;
                bool valid = false;
                while (!valid)
                    {
                        cout << "Press '1' to show Computer Engineering students   "
                        << "Press '2' to show Industrial Engineering students\n"
                        << "Press '3' to show Electrical Engineering students\t"
                        << "Press '4' to show Mechanical Engineering students\n";
                        cout << "Please enter your choice: ";
                        cin >> filter_input;
                        switch (filter_input)
                        {
                            case 1:
                            {
                                valid = true;
                                while (true)
                                {
                                    string id;
                                    fstream computerID;
                                    computerID.open("ComputerID_list", ios::in);
                                    if (!computerID) {
                                        cout << "Not any Computer Student has been registered. Please enter '1' to register.";
                                        cout << endl;
                                        break;
                                    }
                                    if (computerID.is_open()) {
                                        if (computerID.peek() == ifstream::traits_type::eof()) {
                                            cout << "Not any Computer Student has been registered. Please enter '1' to register.";
                                            cout << endl;
                                            break;
                                        }
                                        else {
                                            string line;
                                            while (getline(computerID, line))
                                                cout << line << "\n";
                                            computerID.close();
                                        }
                                    }
                                    cout << "Enter the id of student: ";
                                    cin >> id;
                                    id += ".txt";
                                    if (fs::exists(id))
                                    {
                                        fstream idfile(id,ios::in);
                                        if (idfile.is_open())
                                        {
                                            string line;
                                            while (getline(idfile,line))
                                                cout << line << "\n";
                                            idfile.close();
                                        }
                                        cout << "\n";
                                        break;
                                    }
                                    else
                                        cout << "id not found. Please choose one of the top numbers: ";
                                }
                                break;
                            }
                            case 2:
                            {
                                break;
                            }
                            case 3:
                            {
                                valid = true;
                                while (true)
                                {
                                    string id;
                                    fstream electricalID;
                                    electricalID.open("ElectricalID_list", ios::in);
                                    if (!electricalID) {
                                        cout << "Not any Computer Student has been registered. Please enter '1' to register.";
                                        cout << endl;
                                        break;
                                    }
                                    if (electricalID.is_open()) {
                                        if (electricalID.peek() == ifstream::traits_type::eof()) {
                                            cout << "Not any Computer Student has been registered. Please enter '1' to register.";
                                            cout << endl;
                                            break;
                                        }
                                        else {
                                            string line;
                                            while (getline(electricalID, line))
                                                cout << line << "\n";
                                            electricalID.close();
                                        }
                                    }
                                    cout << "Enter the id of student: ";
                                    cin >> id;
                                    id +=".txt";
                                    if (fs::exists(id))
                                    {
                                        fstream idfile(id,ios::in);
                                        if (idfile.is_open())
                                        {
                                            string line;
                                            while (getline(idfile,line))
                                            cout << line << "\n";
                                            idfile.close();
                                        }
                                        break;
                                    }
                                    else
                                        cout << "id not found. Please choose one of the top numbers: ";
                                }
                                cout << "\n";
                                break;
                            }
                            case 4:
                            {
                                valid = true;
                                while (true)
                                {
                                    string id;
                                    fstream mechanicalID;
                                    mechanicalID.open("MechanicalID_list", ios::in);
                                    if (!mechanicalID) {
                                        cout << "Not any Computer Student has been registered. Please enter '1' to register.";
                                        cout << endl;
                                        break;
                                    }
                                    if (mechanicalID.is_open()) {
                                        if (mechanicalID.peek() == ifstream::traits_type::eof()) {
                                            cout << "Not any Computer Student has been registered. Please enter '1' to register.";
                                            cout << endl;
                                            break;
                                        }
                                        else {
                                            string line;
                                            while (getline(mechanicalID, line))
                                                cout << line << "\n";
                                            mechanicalID.close();
                                        }
                                    }
                                    cout << "Enter the id of student: ";
                                    cin >> id;
                                    id +=".txt";
                                    if (fs::exists(id))
                                    {
                                        fstream idfile(id,ios::in);
                                        if (idfile.is_open())
                                        {
                                            string line;
                                            while (getline(idfile,line))
                                            cout << line << "\n";
                                            idfile.close();
                                        }
                                        break;
                                    }
                                    else
                                        cout << "id not found. Please choose one of the top numbers: ";
                                }
                                cout << "\n";
                                break;
                            }
                            default:
                                cout << "Invalid input. Please enter a number between 1 and 4.\n";
                                break;
                        }
                    }
                break;
            }
            case 5: {
                        cout << "Exiting...\n";
                        return 0;
                    }
            default:
                cout << "Invalid input. Please enter a number between '1' to '5'.\n";
        }
    }
}