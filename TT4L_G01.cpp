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
// -create_output_screen_and_file()
// -select_all_from_table_in_csv_mode()
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
#include <sstream>
#include <cctype> //for isdigit()
#include <cstdlib> //for system()
#include <algorithm> //for remove
using namespace std;

//function prototypes
bool has_substring(const string& line, const string& substring);
void create_output_screen_and_file(const string& fileOutputName);
void create_database(const string& fileInputName, const string& fileOutputName); //to display & log database name
void create_table(vector<vector<string>>& table, const vector<string>& headers, const string& fileOutputName);
void insert_into_table(vector<vector<string>>& table, const string& line, const vector<string>& headers, const string& fileInputName, const string& fileOutputName);
void select_all_from_table_in_csv_mode(const vector<vector<string>>& table, const string& fileOutputName);
int count_row(vector<vector<string>>& table);



int main()
{

    string fileInputName = "C:\\cpp_assignment\\fileInput1.mdb";
    string fileOutputName =  "C:\\cpp_assignment\\fileOutput1.txt";
    system("mkdir C:\\cpp_assignment"); //to ensure directory exist



    ifstream fileInput(fileInputName);
     ofstream fileOutput(fileOutputName, ios::app);
    vector<vector<string>> table;
    //string tableName;
    vector<string> headers = {"customer_id", "customer_name", "customer_city", "customer_state", "customer_country", "customer_phone", "customer_email"};

     create_database(fileInputName, fileOutputName);

    if ( !fileInput.is_open() )
    {
        cerr << "Unable to open file: " << fileInputName << endl;
        return -1;
    }


    //cout << ">DATABASES;"<<endl;
    //cout << fileInputName << endl;

    // Process input file
    string line;
    string completeCommand; //for full command

    while (getline(fileInput, line))
    {
         // Combine lines for multi-line commands
        if (has_substring(line, "INSERT INTO") || !completeCommand.empty())
        {
            completeCommand += line;
            if (line.find(';') != string::npos)
            { // End of command
                insert_into_table(table, completeCommand, headers, fileInputName, fileOutputName);
                completeCommand.clear();
            }
            continue; // Skip the rest of the processing for this line
        }

        if (has_substring(line, "CREATE TABLE"))
        {
            create_table(table, headers, fileOutputName);
        }

        /*if (has_substring(line, "CREATE TABLE"))  //original dell code ---------
        {
            cout << "Creating table. " << endl;
            create_table(table, headers);
        }

        else if (has_substring(line, "INSERT INTO"))
        {
            cout << "Inserting data into table " << endl;
            insert_into_table(table,line,headers);
        }*/

        else if (has_substring(line, "SELECT*FROM customer"))
        {
            //cout << "Displaying table in terminal:" << endl;
            //fileOutput << "Displaying table in terminal:" << endl;

                   // Print table rows

            fileOutput<<">INSERT INTO";
             for (const auto& row : table) {
                for (size_t j = 0; j < row.size(); ++j) {
                    cout << row[j];
                    fileOutput << row[j];
                    if (j < row.size() - 1) {
                        cout << " , ";
                        fileOutput << " , ";
                    }
                }
                cout << endl;
                fileOutput << endl;
            }
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




        //fileOutputName = "fileOutput1.txt"; //incorrect
        //cout << "> CREATE " << fileOutputName << ";" endl;

        //create_database(fileInputName);
        //call create_database to display n log database name


        // Output table in CSV mode
        select_all_from_table_in_csv_mode(table,fileOutputName);

        int rowcount=count_row(table);
        cout<<">SELECT COUNT (*) FROM customer;"<<endl;
        cout<<rowcount<<endl;

        fileOutput<<">SELECT COUNT (*) FROM customer;"<<endl;
        fileOutput<<rowcount<<endl;

        fileInput.close();
        fileOutput.close();
;
        return 0;
}

    // function definitions
    bool has_substring(const string& line, const string& substring)
    {
        return line.find(substring) != string::npos;
    }

    //CREATE OUTPUT SCREEN------------------------------------------------------------------------------------------------
    void create_output_screen_and_file(const string& fileInputName,const string& fileOutputName)
    {
        ifstream fileInput(fileInputName);
        ofstream fileOutput(fileOutputName, ios::app);

        if (!fileOutput.is_open())
        {
            cout << "Unable to open output file for writing." << endl;
            return;
        }

        cout<<"CREATE"<<fileOutputName;

        string summary = "Database output summary.";
        cout << summary << endl;
        fileOutput << summary << endl;


        cout << "Summary written to " << fileOutputName << endl;
        fileOutput.close();
    }

    //CREATE DATABASE-----------------------------------------------------------------------------------------------------
   void create_database(const string& fileInputName, const string& fileOutputName) {
    ofstream fileOutput(fileOutputName, ios::app);
    if (!fileOutput.is_open()) {
        cerr << "Error: Unable to create output file: " << fileOutputName << endl;
        return;
    }

    cout << ">CREATE " << fileOutputName << endl;
    fileOutput << ">CREATE " << fileOutputName << ";" << endl;

    cout << ">DATABASES;" << endl;
    fileOutput << ">DATABASES;" << endl;

    cout << fileInputName << endl;
    fileOutput << fileInputName << endl;

    fileOutput.close(); // Ensure file is closed after writing
}


        /*if (!fileOutput.is_open())
        {
            cout << "Error: Unable to create output file: " << fileOutputName << endl; //display error message if output file cant be created
            return;
        }


        //write db info to the output file
        //fileOutput << "> DATABASE ;" << endl; //db header
        //fileOutput<<":"<<endl;
         //name of the db file */

       // fileOutput.close();




    //CREATE TABLE-----------------------------------------------------------------------------------------------------
    void create_table(vector<vector<string>>& table, const vector<string>& headers, const string& fileOutputName)
    {

        ofstream fileOutput(fileOutputName, ios::app); //open output file for writing

        table.clear(); //clear existing data
        table.push_back(headers); //add headers as first row
        cout << ">CREATE TABLE "<<endl;
        cout<<"("<<endl;

        fileOutput << ">CREATE TABLE "<<endl;
        fileOutput<<"("<<endl;

        for (size_t i = 0; i < headers.size(); ++i) {
        cout << headers[i] << endl;
        fileOutput << headers[i] << endl;
    }
        cout <<");"<< endl;
        fileOutput <<");"<< endl;
fileOutput.close();

    }

    //INSERT INTO TABLE-----------------------------------------------------------------------------------------------------
    void insert_into_table(vector<vector<string>>& table, const string& line, const vector<string>& headers, const string& fileInputName, const string& fileOutputName)
    {
        ifstream fileInput(fileInputName);
        ofstream fileOutput(fileOutputName, ios::app);


       size_t pos = line.find("VALUES");
    if (pos == string::npos)
    {
        cerr << "Error: Invalid INSERT INTO statement. Missing 'VALUES' keyword." << endl;
        return;
    }

    // Extract the part after "VALUES"
    string valuesPart = line.substr(pos);
    size_t keywordLength = string("VALUES").length();

    // Trim everything up to and including "VALUES"
    valuesPart = valuesPart.substr(keywordLength);


    // Parse the values
   vector<string> newRow;
    stringstream ss(valuesPart);
    string value;

    while (getline(ss, value, ',')) {

    value.erase(remove(value.begin(), value.end(), '\''), value.end());

        newRow.push_back(value);
    }


    table.push_back(newRow);

    // Confirmation message
    cout << ">INSERT INTO "<<endl;
    fileOutput << ">INSERT INTO "<<endl;
    cout<<"VALUE";
    fileOutput<<"VALUE";
    for (const auto& val : newRow)
    {
        cout << val << " ";
        fileOutput << val << " ";

    }
    cout << endl;
    fileOutput << endl;
    fileOutput.close();
}
    //SELECT ALL FROM TABLE------------------------------------------------------------------------------------------
    void select_all_from_table_in_csv_mode(const vector<vector<string>>& table, const string& fileOutputName)
    {
        if (table.empty()) //check if table is empty
        {
            cerr << "Table is empty." << endl;
            return;
        }

        ofstream fileOutput(fileOutputName, ios::app); //open output file in append mode
        if (!fileOutput.is_open())
        {
            cerr << "Unable to open file for csv output." << endl;
            return;
        }

        cout<<"SELECT * FROM customer"<<endl;


          for (const auto& row : table){
                for (size_t j =0;j <row.size(); ++j) //iterates through the data value you get what i mean??
                {

                    cout<<row[j];
                    fileOutput << row[j];
                    if (j < row.size() - 1)
                    {
                        cout<<",";
                        fileOutput << ",";
                    }
                }
                }
                cout<<endl;
                fileOutput << "\n";
        fileOutput.close();
       // cout << "Table exported to " << fileOutputName << endl;
    }


    //COUNT ROW--------------------------------------------------------------
    int count_row(vector<vector<string>>& table){


    return table.empty()? 0:table.size()-1;}
