 // *********************************************************
// Program: TT4L_G01.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT4L
// Trimester: 2430
// Member_1: 242UC244FY | FEQHAH DELILAH BINTI MOHD FAIZUL | feqhah01@gmail.com | 013-662 0012
// Member_2: 242UC244CK | WAN HANANI IMAN | EMAIL | PHONE
// Member_3: 242UC244L8 | VIDHYA DARINEY A/P RAJASINGAM | vidhya.dariney.rajasingam@student.mmu.edu.my | PHONE
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
// Update Functionality:
// - Accepts the table, the column name, the value to search, the column to update, and the new value.
// - Searches for rows matching the search criteria.
// - Updates the row and logs the changes to the output file.
// Collaborative Tasks:
// - Fix errors in other members' code and ensure consistent functionality across modules.

// Member_2: Wan Hanani Iman
// Table Operations:
// - Write the functions create_table(), insert_into_table(), and countrow().
// - Implement countrow() to count the number of rows in a given table.
// - Ensure the table supports two data types (INT and TEXT) and inserts rows correctly.
// - Fixed and ensure format is the same as the report.
// Error Handling:
// - Add error-checking mechanisms for file processing and database/table creation.
// - Assist in writing pseudocode and documentation for these functions.
// Collaborative Tasks:
// - Fix errors in other members' code and ensure consistent functionality across modules.

// Member_3: Vidhya Dariney
// Output and CSV Mode:
// - Write the functions create_output_screen_and_file(), select_all_from_table_in_csv_mode(), and delete_from_table().
// Delete Functionality:
// - Implement delete_from_table() to remove rows based on the given criteria.
// - Ensure the delete function logs changes to the output file.
// - Implement select_all_from_table_in_csv_mode() to view the table data in CSV format.
// - Ensure data from all three input files is properly exported and formatted in CSV outputs.
// Code Cleanup:
// - Clean up and organize code to ensure readability and maintainability.
// - Assist in writing pseudocode and documentation for these functions.
// Collaborative Tasks:
// - Fix errors in other members' code and ensure consistent functionality across modules.

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
void create_table(vector<vector<string>>& table, const vector<string>& headers, const vector<string>& header_types, const string& fileOutputName);
void insert_into_table(vector<vector<string>>& table, const string& line, const vector<string>& headers, const string& fileInputName, const string& fileOutputName);
void select_all_from_table_in_csv_mode(const vector<vector<string>>& table, const string& fileOutputName);
void update_table(vector<vector<string>>& table, const string& searchColumn, const string& searchValue, const string& updateColumn, const string& newValue, const string& fileOutputName);
int count_row(vector<vector<string>>& table, const string& fileOutputName);
void delete_from_table(vector<vector<string>>& table,const string& fileInputName,const string& fileOutputName);


int main()
{


    string fileInputName = "C:\\cpp_assignment\\fileInput3.mdb";
    string fileOutputName =  "C:\\cpp_assignment\\fileOutput3.txt";
    system("mkdir C:\\cpp_assignment"); //to ensure directory exist

    ifstream fileInput(fileInputName);
    ofstream fileOutput(fileOutputName);
    vector<vector<string>> table;
    vector<string> headers = {"customer_id", "customer_name", "customer_city", "customer_state", "customer_country", "customer_phone", "customer_email"};
    vector<string> header_types={"INT", "TEXT", "TEXT", "TEXT", "TEXT", "TEXT", "TEXT"};

    create_database(fileInputName, fileOutputName);

    if ( !fileInput.is_open() )
    {
        cerr << "Unable to open file: " << fileInputName << endl;
        return -1;
    }

    // Process input file
    string line;
    string completeCommand; //for full command

    //update fn in main
    while (getline(fileInput, line))
    {

        if (has_substring(line, "UPDATE"))
        {

            select_all_from_table_in_csv_mode(table,fileOutputName);
            cout<<">TABLES; "<<endl;
            cout<<"customer"<<endl;

            // check if ada "UPDATE" dalam line
            size_t setPos = line.find("SET"); //find "SET" position
            size_t wherePos = line.find("WHERE"); // finf "WHERE" position

            if (setPos != string::npos && wherePos != string::npos)
            {
                //proceed if got "SET","WHERE"
                string updatePart = line.substr(setPos + 3, wherePos - setPos - 3);
                stringstream updateStream(updatePart); //stream for processing update
                string updateColumn, newValue;

                // read column and new value to update
                getline(updateStream, updateColumn, '=');
                getline(updateStream, newValue, ';');

                // Remove spaces before and after update column and new value
                updateColumn.erase(remove_if(updateColumn.begin(), updateColumn.end(), ::isspace), updateColumn.end());
                newValue.erase(remove_if(newValue.begin(), newValue.end(), ::isspace), newValue.end());

                // Remove quotes from newValue
                if (newValue.front() == '\'' && newValue.back() == '\'')
                {
                    newValue = newValue.substr(1, newValue.size() - 2);
                }

                // parse the "WHERE" part to get search column and search value
                string searchPart = line.substr(wherePos + 5); // ambik part lepas "WHERE"
                stringstream searchStream(searchPart);
                string searchColumn, searchValue;

                // read search column and search value
                getline(searchStream, searchColumn, '=');
                getline(searchStream, searchValue, ';');

                // Remove spaces and quotes
                searchColumn.erase(remove_if(searchColumn.begin(), searchColumn.end(), ::isspace), searchColumn.end());
                if (searchValue.front() == '\'' && searchValue.back() == '\'')
                {
                    searchValue = searchValue.substr(1, searchValue.size() - 2);
                }

                update_table(table, searchColumn, searchValue, updateColumn, newValue, fileOutputName);
                select_all_from_table_in_csv_mode(table, fileOutputName);
            }
        }



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


        else if (has_substring(line, "CREATE TABLE"))
        {
            create_table(table, headers, header_types, fileOutputName);
        }


        else if (has_substring(line, "SELECT*FROM customer"))
        {
            fileOutput<<">INSERT INTO";
            for (const auto& row : table)
            {
                for (size_t j = 0; j < row.size(); ++j)
                {
                   cout << row[j];
                   fileOutput << row[j];

                   if (j < row.size() - 1)
                   {
                       cout << " , ";
                       fileOutput << " , ";
                   }

                }

                cout << endl;
                fileOutput << endl;

             }
        }

        else if (has_substring (line, "DELETE"))
        {
            delete_from_table(table, fileInputName, fileOutputName);
            select_all_from_table_in_csv_mode(table, fileOutputName);
        }


    }

    int rowCount = count_row(table, fileOutputName);
    fileInput.close();
    fileOutput.close();
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

        cout<<" CREATE"<<fileOutputName;

        string summary = "Database output summary.";
        cout << summary << endl;
        fileOutput << summary << endl;


        cout << "Summary written to " << fileOutputName << endl;
        fileOutput.close();
    }

    //CREATE DATABASE-----------------------------------------------------------------------------------------------------
   void create_database(const string& fileInputName, const string& fileOutputName)
   {
       ofstream fileOutput(fileOutputName, ios::app);
       if (!fileOutput.is_open())
       {
            cerr << "Error: Unable to create output file: " << fileOutputName << endl;
            return;
       }

       cout << "> CREATE " << fileOutputName << endl;
       fileOutput << "> CREATE " << fileOutputName << ";" << endl;

       cout << "> DATABASES;" << endl;
       fileOutput << "> DATABASES;" << endl;

       cout << fileInputName << endl;
       fileOutput << fileInputName << endl;

       fileOutput.close(); // Ensure file is closed after writing
    }


    //CREATE TABLE-----------------------------------------------------------------------------------------------------
   void create_table(vector<vector<string>>& table, const vector<string>& headers, const vector<string>& header_types, const string& fileOutputName)
    {

        ofstream fileOutput(fileOutputName, ios::app); //open output file for writing

        table.clear(); //clear existing data
        table.push_back(headers); //add headers as first row
        cout << "> CREATE TABLE "<<endl;
        cout<<"("<<endl;

        fileOutput << "> CREATE TABLE "<<endl;
        fileOutput<<"("<<endl;

        for (size_t i = 0; i < headers.size(); ++i)
        {
            cout << headers[i] <<" "<< header_types[i]<< endl;
            fileOutput << headers[i] <<" "<< header_types[i]<<endl;
        }

        cout <<");"<< endl;
        fileOutput <<");"<< endl;
        fileOutput.close();

    }

    //INSERT INTO TABLE-----------------------------------------------------------------------------------------------------
    void insert_into_table(vector<vector<string>>& table, const string& line, const vector<string>& headers, const string& fileInputName, const string& fileOutputName)
    {
        ofstream fileOutput(fileOutputName, ios::app);
        if (!fileOutput.is_open())
        {
                cerr << "Unable to open output file for writing." << endl;
                return;
        }

        size_t pos = line.find("VALUES");
        if (pos == string::npos)
        {
            cerr << "Error: Invalid INSERT INTO statement. Missing 'VALUES' keyword." << endl;
            return;
        }

        // Extract the part after "VALUES"
        string valuesPart = line.substr(pos + string("VALUES").length());
        valuesPart = valuesPart.substr(1, valuesPart.length() - 2);

        size_t start = valuesPart.find('(') + 1; // Start after '('
        size_t end = valuesPart.find(')'); // End at ')'
        string values = valuesPart.substr(start, end - start); // Get the values inside the parentheses

        // Parse the values
        vector<string> newRow;
        stringstream ss(values);
        string value;

        while (getline(ss, value, ','))
        {
            // Trim spaces and quotes
            value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());
            newRow.push_back(value);
        }

        // Ensure the new row has the correct number of columns
        if (newRow.size() != headers.size())
        {
            cerr << "Error: Number of values does not match number of columns." << endl;
            return;
        }

        // Add the new row to the table (only once)
        table.push_back(newRow);

        // Confirmation message (matching terminal output)
        cout << "> INSERT INTO " << endl;
        fileOutput << "> INSERT INTO " << endl;

        // Print the column names
        cout << "customer (";
        fileOutput << "customer (";
        for (size_t i = 0; i < headers.size(); ++i)
        {
            cout << headers[i];
            fileOutput << headers[i];
            if (i < headers.size() - 1)
            {
                cout << ", ";
                fileOutput << ", ";
            }
        }

        cout << ")" << endl;
        fileOutput << ")" << endl;

        cout << "VALUES (" ;
        fileOutput << "VALUES (" ;

        // Print the values
        for (const auto& val : newRow)
        {
            cout << val << " ";
            fileOutput << val << " ";
        }

        cout << ")" << endl;
        fileOutput << ")" << endl;
        fileOutput.close();

    }
    //SELECT ALL FROM TABLE-------------------------------------------------------------------------------------------------
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

        cout<<"> SELECT * FROM customer"<<endl;
        fileOutput << "> SELECT * FROM customer;" << endl;


        for (const auto& row : table)
        {
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
            cout<<endl;
            fileOutput << "\n";
        }

        fileOutput.close();

    }


    //COUNT ROW-------------------------------------------------------------------------------------------------------------
    int count_row(vector<vector<string>>& table, const string& fileOutputName)
    {
        ofstream fileOutput(fileOutputName, ios::app);

        int rowcount=  table.empty()? 0:table.size()-1;
        cout<<"> SELECT COUNT (*) FROM customer;"<<endl;
        cout<<rowcount<<endl;
        fileOutput<<"> SELECT COUNT (*) FROM customer;"<<endl;
        fileOutput<<rowcount<<endl;
        fileOutput.close();
        return rowcount;

    }

    //DELETE FROM TABLE-----------------------------------------------------------------------------------------------------
    void delete_from_table(vector<vector<string>>& table, const string& fileInputName, const string& fileOutputName)
    {
        ifstream fileInput(fileInputName);
        ofstream fileOutput(fileOutputName, ios::app);

        if (!fileInput.is_open())
        {
            cerr << "Unable to open file for deleting row." << endl;
            return;
        }

        if (!fileOutput.is_open())
        {
            cerr << "Unable to open file for storing the deleting process." << endl;
            return;
        }

        string line;

        while(getline(fileInput, line))
        {
            if(has_substring(line, "DELETE FROM") && has_substring(line, "WHERE") && has_substring(line, ";"))
            {
                // to take row id number (string)
                size_t deleteStart = line.find("customer_id=")+12;
                size_t deleteEnd = line.find(";", deleteStart);
                string deleteID = line.substr(deleteStart, deleteEnd - deleteStart);
                // to turn the string into int
                int deleteId = stoi(deleteID);

                cout << "> DELETE FROM customer WHERE customer id= " << deleteId << endl;
                fileOutput << "> DELETE FROM customer WHERE customer id= " << deleteId << endl;

                // the actual deleting process
                for (size_t i = 0; i < table.size(); ++i) //go through table's rows
                {
                    if (i == deleteId) //
                    {
                        table.erase(table.begin() + i); // table.begin() = first element = 0, + i = exact row id, so it becomes table.erase(i) = specific row
                        break;
                    }
                }

            }
        }

    }

    //UPDATE TABLE ----------------------------------------------------------------------------------------------------------
    void update_table(vector<vector<string>>& table, const string& searchColumn, const string& searchValue, const string& updateColumn, const string& newValue, const string& fileOutputName)
    {
        ofstream fileOutput(fileOutputName, ios::app); //open file output utk append
        int searchIndex = -1, updateIndex = -1;
        //to find index column utk search and update dlm header
        for (size_t i = 0; i < table[0].size(); ++i)
        {
            if (table[0][i] == searchColumn) searchIndex = i; //find column yg kita nak search
            if (table[0][i] == updateColumn) updateIndex = i; //find column yg nak update
        }

        //if column not found..
        if (searchIndex == -1 || updateIndex == -1)
        {
            fileOutput << "Error: Column not found!" << endl;
            cout << "Error: Column not found!" << endl;
            return; //return if got any error
        }

        bool updated = false; // track if any row was updated

        //loop for each row
        for (size_t i = 1; i < table.size(); ++i)
        {
            if (table[i][searchIndex] == searchValue)
            {
                table[i][updateIndex] = newValue;
                updated = true; //successfully updated
            }
         }

        if(updated)
        {
           fileOutput << "> UPDATE " << table[0][0] << " SET " << updateColumn << " = " << newValue << " WHERE " << searchColumn << " = " << searchValue << ";" << endl ;
           cout << "> UPDATE " << table[0][0] << " SET " << updateColumn << " = " << newValue << "' WHERE " << searchColumn << " = " << searchValue << ";" << endl ;
        }

        else
        {
           fileOutput << "No rows found matching the condition: " << searchColumn << " = " << searchValue << endl;
           cout << "No rows updated!" << endl;
        }

        fileOutput.close();
}




