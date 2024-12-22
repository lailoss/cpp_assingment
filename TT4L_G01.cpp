// *********************************************************
// Program: TT4L_G01.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT4L
// Trimester: 2430
// Member_1: 242UC244FY | FEQHAH DELILAH BINTI MOHD FAIZUK | feqhah01@gmail.com | 013-662 0012
// Member_2: 242UC244CK | WAN HANANI IMAN | EMAIL | PHONE
// Member_3: 242UC244L8 | VIDHYA DARINEY | EMAIL | PHONE
// *********************************************************
// *********************************************************
// Task Distribution
// Member_1: Feqhah Delilah
// File Handling: fileInput1.mdb & fileOutput1.txt
// - Create and read from the first input file (fileInput1.mdb).
// - Handle the logic to output the database name and view the database in the program.
// - Create a file output for this input (fileOutput1.txt).
// - Implement create_database() to display the database name.
// - Write code to load and display table data using the first file.
// - Assist in writing pseudocode and documentation for these functions.

// Member_2: Wan Hanani Iman
// Table Operations:
// - Write the functions create_table() and insert_into_table().
// - Ensure the table supports two data types (INT and TEXT) and inserts rows correctly.
// Error Handling:
// - Add error-checking mechanisms for file processing and database/table creation.
// - Assist in writing pseudocode and documentation for these functions.

// Member_3: Vidhya Dariney
// create_output_screen_and_file()
// select_all_from_table_in_csv_mode()
// Output and CSV Mode:
// - Implement select_all_from_table_in_csv_mode() to view the table data in CSV format.
// - Ensure data from all three input files is properly exported and formatted in CSV outputs.
// Explanations and Reports:
// - Create structured diagrams, flowcharts, and sample input/output screenshots.
// - Draft the overall user documentation and explanations for program behavior.
// - Collaborate on pseudocode.
// *********************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//function prototypes
void create_output_screen_and_file();
void create_database(const string& fileInputName, const string& fileOutputName); //to display & log database name
void create_table();
void insert_into_table();
void select_all_from_table_in_csv_mode();

int main()
{


    string fileInputName = "C:\\cpp_assingment\\fileInput1.mdb";
    //string fileInput name = "C:\\Your Name\\fileInput2.mdb";
    //string fileInput name = "C:\\your name\\fileInput3.mdb";
    string fileOutputName =  "C:\\cpp_assignment\\fileOutput1.txt";

    fstream fileInput;
    fileInput.open(fileInputName);

    if ( !fileInput.is_open() )
    {
        cout << "Unable to open file" << endl;
        exit(-1);
    }

    string line;
    while ( getline(fileInput, line))
    {
        cout << line << endl;
    }

        fileInput.close();

        //fileOutputName = "fileOutput1.txt"; //incorrect
        //cout << "> CREATE " << fileOutputName << ";" endl;

        //create_database(fileInputName);
        create_database(fileInputName, fileOutputName); //call create_database to display n log database name


        return 0;
}

    // function definitions
    void create_output_screen_and_file()
    {

    }
    void create_database(const string& fileInputName, const string& fileOutputName)
    {
        cout << ">DATABASES;" << endl; //display on console
        cout << fileInputName << endl;

        ofstream fileOutput(fileOutputName); //open output file for writng
        if (!fileOutput.is_open())
        {
            cout << "Unable to create output file: " << fileOutputName << endl; //display error message if output file cant be created
            return;
        }
        //write db info to the output file
        fileOutput << "> DATABASES;" << endl; //db header
        fileOutput << fileInputName << endl; //name of the db file

        fileOutput.close();

        cout << "Database information written to " << fileOutputName << endl;
    }

    void create_table()
    {

    }
    void insert_into_table()
    {

    }
    void select_all_from_table_in_csv_mode()
    {

    }


