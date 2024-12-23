 // *********************************************************
// Program: TT4L_G01.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT4L
// Trimester: 2430
// Member_1: 242UC244FY | FEQHAH DELILAH BINTI MOHD FAIZUL | feqhah01@gmail.com | 013-662 0012
// Member_2: 242UC244CK | WAN HANANI IMAN | EMAIL | PHONE
// Member_3: 242UC244L8 | VIDHYA DARINEY A/P RAJASINGAM | EMAIL | PHONE
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
// - Create pseudocode, flowcharts, and sample input/output screenshots.
// - Draft the overall user documentation and explanations for program behavior.
// - Collaborate on pseudocode.
// *********************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype> //for isdigit()
#include <cstdlib> //for system()
using namespace std;

//function prototypes
bool has_substring(const string& line, const string& substring);
void create_output_screen_and_file(const string& fileOutputName);
void create_database(const string& fileInputName, const string& fileOutputName); //to display & log database name
void create_table(vector<vector<string>>& table, string& tableName);
void insert_into_table(vector<vector<string>>&table);
void select_all_from_table_in_csv_mode(const vector<vector<string>>& table, const string& fileCsv);




int main()
{
    string fileInputName = "C:\\cpp_assignment\\fileInput1.mdb";
    //string fileInput name = "C:\\Your Name\\fileInput2.mdb";
    //string fileInput name = "C:\\your name\\fileInput3.mdb";
    string fileOutputName =  "C:\\cpp_assignment\\fileOutput1.txt";
    string fileCsv =  "C:\\cpp_assignment\\output.csv";

    system ("mkdir C:\\cpp_assignment"); //to ensure directory exist
    ifstream fileInput(fileInputName);
    ofstream fileOutput;
    vector<vector<string>> table;
    string tableName;


    if ( !fileInput.is_open() )
    {
        cout << "Unable to open file: " << fileInputName << endl;
        return -1;
    }

    // Process input file
    string line;
    while (getline(fileInput, line)) {
            cout << "Line read: " << line << endl; //debugging output
        if (has_substring(line, "CREATE TABLE")) {
            cout << "Creating table: " << tableName << endl;
            create_table(table, tableName);
        } else if (has_substring(line, "INSERT INTO")) {
            cout << "Inserting data into table: " << tableName << endl;
            insert_into_table(table);
        }
    }


        /*else if ( has_substring(line, "DATABASES;"))
        {
            cout << "> " << line << endl;
            cout << "?" << endl;
        }
        else if ( has_substring(line, "?1"))
        {
            cout << "?1" << endl;
        }
        else if ( has_substring(line, "?2"))
        {
            cout << "?2" << endl;
        }
        else if ( has_substring(line, "?3"))
        {
            cout << "3" << endl;
        }
        else if ( has_substring(line, "?4"))
        {
            cout << "?4" << endl;
        }
        else if ( has_substring(line, "?5"))
        {
            cout << "?5" << endl;
        }
        else if ( has_substring(line, "?6"))
        {
            cout << "?6" << endl;
        } */
      //  else
       // {
       //     cout << "Error message : Invalid input command" << endl;
       // }

        fileInput.close();


        //fileOutputName = "fileOutput1.txt"; //incorrect
        //cout << "> CREATE " << fileOutputName << ";" endl;

        //create_database(fileInputName);
        create_database(fileInputName, fileOutputName); //call create_database to display n log database name


        // Output table in CSV mode
        select_all_from_table_in_csv_mode(table, fileCsv);


        return 0;
}

    // function definitions
    bool has_substring(const string& line, const string& substring)
    {
        return line.find(substring) != string::npos;
    }

    //CREATE OUTPUT SCREEN------------------------------------------------
    void create_output_screen_and_file(const string& fileOutputName)
    {
        ofstream outputFile(fileOutputName);

        if (!outputFile.is_open())
        {
            cout << "Unable to open output file for writing." << endl;
            return;
        }

        string summary = "Database output summary.";
        cout << summary << endl;
        outputFile << summary << endl;

        outputFile.close();
        cout << "Summary written to " << fileOutputName << endl;
    }

    void create_database(const string& fileInputName, const string& fileOutputName)
    {
        cout << ">DATABASES;" << endl; //display on console
        cout << fileInputName << endl;

        ofstream fileOutput(fileOutputName); //open output file for writng
        if (!fileOutput.is_open())
        {
            cout << "Error: Unable to create output file: " << fileOutputName << endl; //display error message if output file cant be created
            return;
        }
        //write db info to the output file
        fileOutput << "> DATABASES;" << endl; //db header
        fileOutput << fileInputName << endl; //name of the db file

        fileOutput.close();
        cout << "Database information written to " << fileOutputName << endl;
    }

    void create_table(vector<vector<string>>&table, string& tableName)
    {

        tableName="Customer";

        vector<string> columnnames = {
            "customer_id",
            "customer_name",
            "customer_city",
            "customer_state",
            "customer_country",
            "customer_phone",
            "customer_email"
        };
        vector<string> columntypes={
            "INT",
            "TEXT",
            "TEXT",
            "TEXT",
            "TEXT",
            "TEXT",
            "TEXT"
        };
        table.clear();
        table.push_back(columnnames);
        table.push_back(columntypes);

        cout<<tableName<<"has successfully been created."<< endl;



    }

    void insert_into_table(vector<vector<string>>&table)
    {
        //let's say there's no table created, so therefore...
        if (table.empty()){
            cerr<<"No table found.";
            return;
        }

        const vector<string>&columnnames = table[0];
        const vector<string>& columntypes = table[1];
        vector<string> newRow;


        cout<<"Enter 'exit' at any time to stop input";

        for (size_t i=0; i<columnnames.size(); i++)
            {
            string value;
            cout<<","<<columnnames[i]<<"("<<columntypes[i]<<")";
            cin>>value;

            // Check for 'exit' keyword to break the loop
            if (value == "exit") {
                cout << "Input terminated by user." << endl;
                return;
            }

            //the part above is for string, below is for int input
            if (columntypes[i]=="INT"){

                for (char c : value)
                    {
                        if(!isdigit(c)){
                            cerr<<"Error:"<<columnnames[i]<<"column only accepts integer";
                            return;
                        }
                }
            }
            newRow.push_back(value);
        }
        table.push_back(newRow);
        cout<<"Row successfully made";
    }

    //SELECT ALL FROM TABLE------------------------------------------------
    void select_all_from_table_in_csv_mode(const vector<vector<string>>& table, const string& fileCsv)
    {
        if (table.empty())
        {
            cerr << "Table is empty." << endl;
            return;
        }

        ofstream outputFile(fileCsv);
        if (!outputFile.is_open())
        {
            cerr << "Unable to open file for csv output." << endl;
            return;
        }

        for (const auto& row : table)
        {
            for (size_t i= 0; i < row.size(); ++i)
            {
                outputFile << row[i];

                if (i < row.size() - 1)
                {
                    outputFile << ";";
                }
            }
        }

        outputFile.close();
        cout << "Table exported to" << fileCsv << endl;
    }


