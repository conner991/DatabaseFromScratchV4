/* -----------------------------------------------------------------------------
FILE NAME:         driver.cpp
DESCRIPTION:       Driver file that contains main() and controls the whole program
USAGE:             
COMPILER:          GNU g++ compiler on Linux
NOTES:             

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Conner Fissell     04-07-2021         Initial Set up
Conner Fissell     04-09-2021         Updated Parser
Conner Fissell     04-10-2021         Worked on Selects
Conner Fissell     04-11-2021         Finished Selects
Conner Fissell     04-12-2021         Turned in project
----------------------------------------------------------------------------- */
#include "Table.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])


// Database struct that holds the Table ojects and other database info
struct Database
{
     bool inUse = false;
     std::string dbName;
     std::vector<Table> tables;
};

// Prototypes
bool inputParser(std::string inputLine, std::vector<std::string> &wordVector, bool &running);
void wordDecider(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector, int &dbCount);
void createDB(std::string dbName, std::vector<Database> &databases, int &dbCount);
void deleteDB(std::string name, std::vector<Database> &databases, int &dbCount);
void useDB(std::string name, std::vector<Database> &databases, int &dbCount);
void createTable(std::string name, std::vector<std::string> &wordVector, std::vector<Database> &databaseVector);
void dropTable(std::string name, std::vector<Database> &databaseVector);
void displayWholeTable(std::string name, std::vector<Database> &databaseVector);
void addAttribute(std::string table, std::string attName, std::string dt, std::vector<Database> &databaseVector);
void insert(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector);
void select(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector);
void selectMultipleTables(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector);
void updateTable(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector);
void deleteRecords(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector);
/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
int main(int argc, char* argv[])
{


     bool running = true; 
     int dbCount = 0;
     std::string inputLine;
     std::vector<std::string> wordVector;
     std::vector<Database> databaseVector;

     // Enter SQL Mode
     while (running) {
          std::cout << "--> ";
          std::getline(std::cin, inputLine);

          // Parse our input string into vector of word strings
          running = inputParser(inputLine, wordVector, running);

          // If .exit was not entered, move forward in program
          if (wordVector.size() != 0) {
               wordDecider(wordVector, databaseVector, dbCount);
          }
          
          // clear vector of input strings after each SQL command
          wordVector.clear();
     }


     std::cout << "All done.\n\n";     
     

     // Remove an empty directory
     //int removed = rmdir("test");



}

/* -----------------------------------------------------------------------------
FUNCTION:          inputParser() 
DESCRIPTION:       Parses the input the user enters into the command prompt
RETURNS:           bool running
NOTES:             
------------------------------------------------------------------------------- */
bool inputParser(std::string input, std::vector<std::string> &wordVector, bool &running)
{    
     std::string word, newWord1, newWord2;
     int Pposition, numOfSpaces = 0, lengthOfString; 


     // Make any letters in input string lowercase
     // std::transform(input.begin(), input.end(), input.begin(), ::tolower);
     
     // Check to make sure there is a semicolon at the end of the statement
     if (input.back() == ';' || input == ".exit") {


          const std::regex reg(R"([\s|,]+)");


          std::sregex_token_iterator it {input.begin(), input.end(), reg, -1};

          std::vector<std::string> wordVector2 {it, {} };

          // additional check to remove empty strings
          wordVector2.erase(std::remove_if(wordVector2.begin(), wordVector2.end(), [](std::string const& s) {return s.size() == 0;}), wordVector2.end());
 
          wordVector = wordVector2;

          // Separate out certain words due to lack of spaces for a table creation SQL statement
          if (wordVector[0] == "create" && wordVector[1] == "table") {

               for (int i = 0; i < wordVector[2].length(); i++) {

                    if (wordVector[2].at(i) == '(') {
                    
                         // i is the position of the "("
                         Pposition = i;

                         // Creates a string out of the first part of the input
                         newWord1.assign(wordVector[2], 0, Pposition);
                         
                         // Adds word to the string vector
                         //wordVector.push_back(word);

                         // Need to modify input string to capture the rest of the input words
                         wordVector[2].erase(0, Pposition + 1);


                    }
               }

               // Insert new word into original wordVector
               wordVector.insert(wordVector.begin() + 2, newWord1);

          }

          // Separate out certain words due to lack of spaces for an insert SQL statement
          else if (wordVector[0] == "insert") {

               for (int i = 0; i < wordVector[3].length(); i++) {

                    if (wordVector[3].at(i) == '(') {
                    
                    // i is the position of the "("
                    Pposition = i;

                    // Creates a string out of the first part of the input
                    newWord1.assign(wordVector[3], 0, Pposition);
                    
                    // Adds word to the string vector
                    //wordVector.push_back(word);

                    // Need to modify input string to capture the rest of the input words
                    wordVector[3].erase(0, Pposition + 1);


                    }
               }

               // Insert new word into original wordVector
               wordVector.insert(wordVector.begin() + 3, newWord1);

          }


          










          if (wordVector[0] == ".exit") {
               wordVector.clear();
               running = false;
               return running;
          }

          // else {
          //      wordVector.clear();
          //      std::cout << "Unknown Entry.\n";
          // }
         
          
     }

     else {
          std::cout << "Input statement must end with a semicolon.\n";
     }
          

     return running;

}

/* -----------------------------------------------------------------------------
FUNCTION:          WordDecider() 
DESCRIPTION:       Decides based on the parsed user input where the program should
                    go next.
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void wordDecider(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector, int &dbCount) 
{    
     int oldSize, newSize;
     char frontOfString;
     

     // Make first string in vector lower case
     std::transform(wordVector[0].begin(), wordVector[0].end(), wordVector[0].begin(), ::tolower);



     // Check first word in vector to see if it is one of the beginning SQL keywords
     if (wordVector[0] == "create" || wordVector[0] == "drop" || wordVector[0] == "use" || wordVector[0] == "select" || 
     wordVector[0] == "alter" || wordVector[0] == "insert" || wordVector[0] == "update"|| wordVector[0] == "delete") {
          
          // CREATE DATABASE or TABLE
          if (wordVector[0] == "create") {

               // Make second string in vector lower case
               std::transform(wordVector[1].begin(), wordVector[1].end(), wordVector[1].begin(), ::tolower);
               
               // then we're either gonna create a DATABASE or a TABLE (one of those SQL keywords will follow)
               
               // CREATE DATABASE
               if (wordVector[1] == "database") {

                    // Theres going to be a ";" at the end of our database name that we need to get rid of
                    oldSize = wordVector[2].size();
                    newSize = oldSize - 1;
                    wordVector[2].resize(newSize);
                    
                    // Call createDB function to create DB
                    std::string dbName1 = wordVector[2];
                    createDB(dbName1, databaseVector, dbCount);

               }

               // CREATE TABLE
               else if (wordVector[1] == "table") {

                    // Make third string in vector lower case
                    //std::transform(wordVector[2].begin(), wordVector[2].end(), wordVector[2].begin(), ::tolower);

                    
                    // Create tbl_x out of wordVector[2]
                    createTable(wordVector[2], wordVector, databaseVector);
                         

               }

               else {
                    std::cout << "DATABASE or TABLE must follow CREATE\n";
               }
          }


          // DROP DATABASE or TABLE
          else if (wordVector[0] == "drop") {

               // Make second string in vector lower case
               std::transform(wordVector[1].begin(), wordVector[1].end(), wordVector[1].begin(), ::tolower);
               
               // Same as "CREATE" except we're either gonna drop a created database or a table

               // DROP DATABASE
               if (wordVector[1] == "database") {
                    
                    // // Theres going to be a ";" at the end of our database name that we need to get rid of
                    oldSize = wordVector[2].size();
                    newSize = oldSize - 1;
                    wordVector[2].resize(newSize);

                    // Call deleteDB function to delete wordVector[2] database name
                    deleteDB(wordVector[2], databaseVector, dbCount);
                    
               }

               // DROP TABLE
               else if (wordVector[1] == "table") {

                    // Make third string in vector lower case
                    std::transform(wordVector[2].begin(), wordVector[2].end(), wordVector[2].begin(), ::tolower);
                    
                    // // Theres going to be a ";" at the end of our table name that we need to get rid of
                    oldSize = wordVector[2].size();
                    newSize = oldSize - 1;
                    wordVector[2].resize(newSize);
                    
                    // Now delete wordVector[2] table
                    dropTable(wordVector[2], databaseVector);
               
               }

               else {
                    std::cout << "DATABASE or TABLE must follow DROP.\n";
               }
          }


          // USE DATABASE
          else if (wordVector[0] == "use") {
     
               // Next word after "USE" is a database name 
               // Theres going to be a ";" at the end of our database name that we need to get rid of
               oldSize = wordVector[1].size();
               newSize = oldSize - 1;
               wordVector[1].resize(newSize);

               // USE our database wordVector[1] and check to see if we are already using it if this happens again
               useDB(wordVector[1], databaseVector, dbCount);
               

               
          }


          // SELECT 
          else if (wordVector[0] == "select") {
 

               // // Make third string in vector lower case
               // std::transform(wordVector[2].begin(), wordVector[2].end(), wordVector[2].begin(), ::tolower);

               // // Make third string in vector lower case
               // std::transform(wordVector[3].begin(), wordVector[3].end(), wordVector[3].begin(), ::tolower);


               select(wordVector, databaseVector);




               
               
               
          }


          // ALTER TABLE
          else if (wordVector[0] == "alter"){

               // Make second string in vector lower case
               std::transform(wordVector[1].begin(), wordVector[1].end(), wordVector[1].begin(), ::tolower);

               // Make third string in vector lower case
               std::transform(wordVector[2].begin(), wordVector[2].end(), wordVector[2].begin(), ::tolower);

               // Make fourth string in vector lower case
               std::transform(wordVector[3].begin(), wordVector[3].end(), wordVector[3].begin(), ::tolower);
               
               // Next word after "alter" is only ever going to be a SQL table keyword and that must be a created table
               if (wordVector[1] == "table") {

                    // ALTER is only ever going to work with a created table
                    
                    if (wordVector[3] == "add") {

                         // Theres going to be a ";" at the end of our datatype name that we need to get rid of
                         oldSize = wordVector[5].size();
                         newSize = oldSize - 1;
                         wordVector[5].resize(newSize);
                         
                         // attribute name (wordVector[4]) and datatype (wordVector[5] with a semicolon) are entered here
                         // add attribute to tbl_x here
                         addAttribute(wordVector[2], wordVector[4], wordVector[5], databaseVector);

                    }

                    
               }

               else {
                    std::cout << "Must be TABLE keyword\n";
               }
               
          }

          // INSERT 
          else if (wordVector[0] == "insert") {

               // Make second string in vector lower case
               std::transform(wordVector[1].begin(), wordVector[1].end(), wordVector[1].begin(), ::tolower);

               // Make third string in vector lower case
               //std::transform(wordVector[2].begin(), wordVector[2].end(), wordVector[2].begin(), ::tolower);

               if (wordVector[1] == "into") {

                    // Here we'll insert specific words from the input into our table
                    insert(wordVector, databaseVector);
               }

               else {
                    std::cout << "INTO must follow INSERT\n";
               }

          }

          // UPDATE 
          else if (wordVector[0] == "update") {

               // Make third string in vector lower case
               std::transform(wordVector[1].begin(), wordVector[1].end(), wordVector[1].begin(), ::tolower);

               // Make third string in vector lower case
               std::transform(wordVector[2].begin(), wordVector[2].end(), wordVector[2].begin(), ::tolower);

               // Make seventh string in vector lower case
               std::transform(wordVector[6].begin(), wordVector[6].end(), wordVector[6].begin(), ::tolower);

               // Here we'll update our table by changing specific attName values to other values
               updateTable(wordVector, databaseVector);
          }

          // DELETE 
          else if (wordVector[0] == "delete") {

               // Make second string in vector lower case
               std::transform(wordVector[1].begin(), wordVector[1].end(), wordVector[1].begin(), ::tolower);

               // Make third string in vector lower case
               std::transform(wordVector[2].begin(), wordVector[2].end(), wordVector[2].begin(), ::tolower);

               // Make fourth string in vector lower case
               std::transform(wordVector[3].begin(), wordVector[3].end(), wordVector[3].begin(), ::tolower);
               
               if (wordVector[1] == "from") {

                    // Here we'll delete specific attName values from our table
                    deleteRecords(wordVector, databaseVector);
               }

               else {
                    std::cout << "FROM must follow delete\n";
               }

                
          }
     }

     else {
          std::cout << "Unknown Command.\n";
     }
     

}

/* -----------------------------------------------------------------------------
FUNCTION:          createDB() 
DESCRIPTION:       creates a database object and adds it to the databaseVector
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void createDB(std::string name, std::vector<Database> &databaseVector, int &dbCount) 
{    
     bool inVector = false;
     struct Database db;

     // If there are more than 1 database entrys in our vector
     if (dbCount > 1) {

          for (int i = 0; i < databaseVector.size(); i++) {
                
                if (databaseVector[i].dbName == name) {
                     std::cout << "!Failed to create database " << name << " because it already exists.\n";
                     inVector = true;
                }
          }

          if (!inVector) { 

               // Now create a database with name by creating a directory in our project
               // const char* dbName = name.c_str();
                    
               // if (mkdir(dbName, 0777) == -1) {
               //      std::cout << "Error creating Database.\n";
               // }

               // Add name of database to vector
               db.dbName = name;
               databaseVector.push_back(db);
               std::cout << "Database " << name << " created.\n";
          

               dbCount++;
          }

     }

     else if (dbCount == 1) {    

          if (databaseVector.front().dbName == name) {
               std::cout << "!Failed to create database " << name << " because it already exists.\n";
          }

          else {

               // Now create a database with name by creating a directory in our project
               // const char* dbName = name.c_str();
                    
               // if (mkdir(dbName, 0777) == -1) {
               //      std::cout << "Error creating Database\n";
               // }

          
               // Add name of database to vector
               db.dbName = name;
               databaseVector.push_back(db);
               std::cout << "Database " << name << " created.\n";
               

               dbCount++;
          }
     }

     // Our database vector is empty 
     else {
          // Now create a database with name by creating a directory in our project
          // const char* dbName = name.c_str();
                    
          // if (mkdir(dbName, 0777) == -1) {
          //      std::cout << "Error creating Database\n";
          // }

          // Add name of database to vector
          db.dbName = name;
          databaseVector.push_back(db);
          std::cout << "Database " << name << " created.\n";
          

          dbCount++;
     }

     
}

/* -----------------------------------------------------------------------------
FUNCTION:          deleteDB() 
DESCRIPTION:       deletes a database from the database vector
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void deleteDB(std::string name, std::vector<Database> &databaseVector, int &dbCount) 
{         
     std::string tempName1, tempName2, s;
     struct Database tempDB;

     // If we have more than 1 database string in our vector
     if (dbCount > 1) {
          
          // Delete database, removes the corresponding directory string from the vector
          // by searching for it   
          for (auto i = databaseVector.begin(); i != databaseVector.end(); i++) {
               
               // Extract DB name string so we can compare it
               tempDB = *i;
               s = tempDB.dbName;
               
               if (s == name) {
                    
                    tempName1 = name;
                    databaseVector.erase(i);

                    // Delete database directory from project directory
                    // std::string removalString = "rm -r " + tempName1;
                    // system(removalString.c_str());
                    // std::cout << "Database " << tempName1 << " deleted.\n";

                    dbCount--;     

                    break; 
              
               }
               
          }
     }

     
     // if dbCount is equal to 1
     else {
          
          if (databaseVector.front().dbName == name) {
               
               // Delete database directory from project directory
               databaseVector.clear();


               // std::string removalString = "rm -r " + name;
               // system(removalString.c_str());
               // std::cout << "Database " << name << " deleted.\n";

               dbCount--;
          }

          else {
               std::cout << "!Failed to delete database " << name << " because it does not exist.\n";
          }
          
     }

     // else we are trying to delete an entry from an empty vector.  
     if (dbCount == 0) {
          std::cout << "!Failed to delete database " << name << " because it does not exist.\n";
     }
     
         
}

/* -----------------------------------------------------------------------------
FUNCTION:          useDB() 
DESCRIPTION:       Activates a database oject to be used
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void useDB(std::string name, std::vector<Database> &databaseVector, int &dbCount) 
{
     bool inVector = false;


     // If there are more than 1 database entrys in our vector
     if (dbCount > 1) {
     
          for (int i = 0; i < databaseVector.size(); i++) {

               // Set all database inUse booleans to false, to reset so we can swtich between them
               databaseVector[i].inUse = false;

               if (databaseVector[i].dbName == name && databaseVector[i].inUse == false) {
                    
                    std::cout << "Using database " << name << ".\n";
                    databaseVector[i].inUse = true;
                    inVector = true;
               }
               
               else if (databaseVector[i].dbName == name && databaseVector[i].inUse == true) {
                    std::cout << "!Already using database " << name << ".\n";
                    inVector = true;
               }
               

          }

          if (!inVector) {
               std::cout << "!Database " << name << " has not been created.\n";
          }


     }

     else if (dbCount == 1) {    

          if (databaseVector.front().dbName == name && databaseVector.front().inUse == false) {
               
               std::cout << "Using database " << name << ".\n";
               databaseVector.front().inUse = true;
          }

          else if (databaseVector.front().dbName == name && databaseVector.front().inUse == true) {
               std::cout << "!Already using database " << name << ".\n";
          }

          else {

               std::cout << "!Database " << name << " has not been created.\n";      
          }
     }

     // Our database vector is empty 
     else {
          std::cout << "!Database " << name << " has not been created.\n";
     }

}

/* -----------------------------------------------------------------------------
FUNCTION:          createTable() 
DESCRIPTION:       creates a Table object and adds it to the tables vector within 
                    a database struct object
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void createTable(std::string tableName, std::vector<std::string> &wordVector, std::vector<Database> &databaseVector) 
{    
     int count = 0, tableExpressionSize, oldSize, newSize;
     std::string attName, attDT, appended1, appended2, name, price;
     bool used = false;
     bool inDB = false;

     // Create Attribute objects to use
     Attribute att1, att2, att3;

     // Check for a database thats in use
     for (int i = 0; i < databaseVector.size(); i++) {
          
          if (databaseVector[i].inUse == true) {

               used = true;

               // check to make sure the table hasn't been created already
               for (int j = 0; j < databaseVector[i].tables.size(); j++) {

                    if (tableName == databaseVector[i].tables[j].getTableName()) {
                         inDB = true;
                         std::cout << "!Failed to create table " << tableName << " because it already exists.\n";
                    }
               }

               if (!inDB) {
                    
                    // Create a table for this database by creating a table object and naming it
                    Table newTable(tableName);
                    
                    if (tableName == "Employee") {
                         
                         // Store first attribute name in attName
                         attName = wordVector[3];

                         // Store its datatype in attDT
                         attDT = wordVector[4];

                         // Add attribute name and datatype to Attribute object
                         att1.createAttribute(attName, attDT);

                         // Now add attribute object to the Table attribute object vector
                         newTable.addAttribute(att1);

                         // Second attribute 
                         // Store second attribute name in attName
                         attName = wordVector[5];

                         // Now get attribute datatype, have to take off the ");" at the end
                         oldSize = wordVector[6].size();
                         newSize = oldSize - 2;
                         wordVector[6].resize(newSize);

                         // Store its datatype in attDT
                         attDT = wordVector[6];

                         // Add attribute name and datatype to Attribute object
                         att2.createAttribute(attName, attDT);

                         // Now add attribute object to the Table attribute object vector
                         newTable.addAttribute(att2);

                    }

                    else if (tableName == "Sales") {

                         // Store first attribute name in attName
                         attName = wordVector[3];

                         // Store its datatype in attDT
                         attDT = wordVector[4];

                         // Add attribute name and datatype to Attribute object
                         att1.createAttribute(attName, attDT);

                         // Now add attribute object to the Table attribute object vector
                         newTable.addAttribute(att1);

                         // Second attribute 
                         // Store second attribute name in attName
                         attName = wordVector[5];

                         // Now get attribute datatype, have to take off the ");" at the end
                         oldSize = wordVector[6].size();
                         newSize = oldSize - 2;
                         wordVector[6].resize(newSize);

                         // Store its datatype in attDT
                         attDT = wordVector[6];

                         // Add attribute name and datatype to Attribute object
                         att2.createAttribute(attName, attDT);

                         // Now add attribute object to the Table attribute object vector
                         newTable.addAttribute(att2);

                    }

               

                    // // go through wordVector of strings and create attributes
                    // for (int j = 0; j < wordVector.size(); j++) {

                    //      // Catch the first attribute in the parenthetical expression
                    //      if (wordVector[j] == "id") {
                         
                    //          // Need to get rid of the ( at the beginning of first attribute name
                    //          //wordVector[j].erase(0, 1);

                    //           // Store in attName
                    //           attName = wordVector[j];

                    //           // Now get attribute datatype, have to take off the , at the end
                    //           // oldSize = wordVector[j + 1].size();
                    //           // newSize = oldSize - 1;
                    //           // wordVector[j + 1].resize(newSize);

                    //           // Store in attDT
                    //           attDT = wordVector[j + 1];

                    //           // Add attribute name and datatype to Attribute object
                    //           att1.createAttribute(attName, attDT);

                    //           // Now add attribute object to the Table attribute object vector
                    //           newTable.addAttribute(att1);

                    //      }

                    
                         
                    //      // To capture other attributes in the expression
                    //      else if (wordVector[j] == "name") {
                         
                    //           // Store new attribute in attName          
                    //           attName = wordVector[j];

                    //           // Get attribute datatype, either this datatype ends with a ","
                    //           //if (wordVector[j + 1].back() == ',') {
                              
                    //                // oldSize = wordVector[j + 1].size();
                    //                // newSize = oldSize - 1;
                    //                // wordVector[j + 1].resize(newSize);

                    //                // Store in attDT
                    //                attDT = wordVector[j + 1];

                    //          // }

                    //           // Or it ends with a ");"
                    //           // else {

                    //           //      oldSize = wordVector[j + 1].size();
                    //           //      newSize = oldSize - 2;
                    //           //      wordVector[j + 1].resize(newSize);

                    //           //      // Store in attDT
                    //           //      attDT = wordVector[j + 1];

                    //           // }

                    //           // Add attribute name and datatype to Attribute object
                    //           att2.createAttribute(attName, attDT);

                    //           // Now add attribute object to the Table attribute object vector
                    //           newTable.addAttribute(att2);

                    //      }

                    //      else if (wordVector[j] == "price") {
                              
                    //           // Store new attribute in attName          
                    //           attName = wordVector[j];

                    //           // Get attribute datatype, either this datatype ends with a ","
                    //           // if (wordVector[j + 1].back() == ',') {
                              
                    //           //      oldSize = wordVector[j + 1].size();
                    //           //      newSize = oldSize - 1;
                    //           //      wordVector[j + 1].resize(newSize);

                    //                // Store in attDT
                    //                //attDT = wordVector[j + 1];

                    //          // }

                    //           // Or it ends with a ");"
                    //           // else {

                    //                oldSize = wordVector[j + 1].size();
                    //                newSize = oldSize - 2;
                    //                wordVector[j + 1].resize(newSize);

                    //                // Store in attDT
                    //                attDT = wordVector[j + 1];

                    //           // }

                    //           // Add attribute name and datatype to Attribute object
                    //           att3.createAttribute(attName, attDT);

                    //           // Now add attribute object to the Table attribute object vector
                    //           newTable.addAttribute(att3);
                    //      }

                    // }

                    // Add table with new attributes to the Database struct tables vector
                    databaseVector[i].tables.push_back(newTable);
                    std::cout << "Table " << tableName << " created.\n";

               }

               
          }

     }

     if (!used) {
               
          // Must be using a database in order to create a table 
          std::cout << "Failed to create table because there is no database in use.\n";
     }
     
}

/* -----------------------------------------------------------------------------
FUNCTION:          dropTable()
DESCRIPTION:       deletes a table object from the database ojects Table vector
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void dropTable(std::string tableName, std::vector<Database> &databaseVector) 
{    
     bool used = false;
     bool inDB = false;

     // Check for database that's in use
     for (int i = 0; i < databaseVector.size(); i++) {

          if (databaseVector[i].inUse == true) {

               used = true;

               Table tempTable;
               std::string tempName;

               for (auto it = databaseVector[i].tables.begin(); it != databaseVector[i].tables.end(); it++) {
                    
                    tempTable = *it;
                    tempName = tempTable.getTableName();

                    if (tempName == tableName) {
                         
                         databaseVector[i].tables.erase(it);
                         inDB = true;
                         std::cout << "Table " << tableName << " deleted.\n";

                         break;

                    }
               }

               

               if (!inDB) {
                    std::cout << "!Failed to delete " << tableName << " because it does not exist.\n";
               }

          }
     }

     if (!used) {
               
          // Must be using a database in order to create a table 
          std::cout << "Failed to drop table because there is no database in use.\n";
     }
}

/* -----------------------------------------------------------------------------
FUNCTION:          displayWholeTable()
DESCRIPTION:       prints out all of the table data to the screen
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void displayWholeTable(std::string tableName, std::vector<Database> &databaseVector)
{    
     bool used = false;
     bool inDB = false;
     int tableCount = 0;

     // Check for a database that's in use
     for (int i = 0; i < databaseVector.size(); i++) {

          if (databaseVector[i].inUse == true) {

               used = true;

               for (int j = 0; j < databaseVector[i].tables.size(); j++) {

                    if (tableName == databaseVector[i].tables[j].getTableName()) {
                         
                         databaseVector[i].tables[j].displayAttributesAndValues();
                         inDB = true;
                         
                    }
               }

               if (!inDB) {
                    
                    std::cout << "!Failed to query table " << tableName << " because it does not exist.\n";
               }
          } 
     }

     if (!used) {

          // Must be using a database in order to create a table 
          std::cout << "Failed to drop table because there is no database in use.\n";
     }
     
}

/* -----------------------------------------------------------------------------
FUNCTION:          addAttribute()
DESCRIPTION:       allows the user to add an attribute to the table in use
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void addAttribute(std::string tableName, std::string attName, std::string attDT, std::vector<Database> &databaseVector) 
{
     bool used = false;
     bool inDB = false;
     int tableCount = 0;

     // Check for a database that's in use
     for (int i = 0; i < databaseVector.size(); i++) {

          if (databaseVector[i].inUse == true) {

               used = true;

               for (int j = 0; j < databaseVector[i].tables.size(); j++) {

                    if (tableName == databaseVector[i].tables[j].getTableName()) {

                         // Create attribute to add to the table
                         Attribute att1;
                         att1.createAttribute(attName, attDT);
                         
                         databaseVector[i].tables[j].addAttribute(att1);
                         inDB = true;
                         std::cout << "Table " << tableName << " modified.\n";
                         
                    }
               }

               if (!inDB) {
                    
                    std::cout << "!Failed to modify table " << tableName << " because it does not exist.\n";
               }
          } 
     }

     if (!used) {

          // Must be using a database in order to create a table 
          std::cout << "Failed to drop table because there is no database in use.\n";
     }
}

/* -----------------------------------------------------------------------------
FUNCTION:          insert()
DESCRIPTION:       inserts attribute values into the table object which in turn inserts
                    the data into the appropriate Attribute objects. 
RETURNS:           
NOTES:             
------------------------------------------------------------------------------- */
void insert(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector)
{
     bool used = false;
     bool inDB = false;
     int oldSize, newSize, tableCount = 0;
     std::string tableName, value1, value2, value3;
     std::vector<std::string> valueHolder;     // holds the first line of values for each insertion

     // Check for a database that's in use
     for (int i = 0; i < databaseVector.size(); i++) {

          if (databaseVector[i].inUse == true) {

               used = true;

               tableName = wordVector[2];

               // Go through tables
               for (int j = 0; j < databaseVector[i].tables.size(); j++) {

                    if (tableName == databaseVector[i].tables[j].getTableName()) {

                         if (tableName == "Employee") {

                              // Erase the beginning string characters off of our first attribute value
                              //wordVector[3].erase(0, 7);

                              // Store in value string for readability 
                              value1 = wordVector[4];

                              // Now to get our second value
                              // Take off the "');" at the end
                              oldSize = wordVector[5].size();
                              newSize = oldSize - 3;
                              wordVector[5].resize(newSize);

                              // Erase the "'" at the beginning
                              wordVector[5].erase(0, 1);

                              // Store in value string for readability 
                              value2 = wordVector[5];

                              // Load up our value vector with the values
                              valueHolder.push_back(value1);
                              valueHolder.push_back(value2);

                              // Pass our value vector to the table object so we can add the 
                              // values to their corresponding attribute objects
                              databaseVector[i].tables[j].addValues(valueHolder);

                              std::cout << "1 new record inserted.\n";

                              valueHolder.clear();

                         }

                         else if (tableName == "Sales") {

                              // Erase the beginning string characters off of our first attribute value
                              //wordVector[3].erase(0, 7);

                              // Store in value string for readability 
                              value1 = wordVector[4];

                              // Now to get our second value
                              // Take off the ");" at the end
                              oldSize = wordVector[5].size();
                              newSize = oldSize - 2;
                              wordVector[5].resize(newSize);

                              // Store in value string for readability 
                              value2 = wordVector[5];

                              // Load up our value vector with the values
                              valueHolder.push_back(value1);
                              valueHolder.push_back(value2);

                              // Pass our value vector to the table object so we can add the 
                              // values to their corresponding attribute objects
                              databaseVector[i].tables[j].addValues(valueHolder);

                              std::cout << "1 new record inserted.\n";

                              valueHolder.clear();

                         }
                         


                    }

                    

               }

          }
          
     }

     if (!used) {

          // Must be using a database in order to create a table 
          std::cout << "Failed to insert values because there is no database in use.\n";
     }

}

/* -----------------------------------------------------------------------------
FUNCTION:          select()
DESCRIPTION:       grabs specific data from one or more tables and prints it out to the screen
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void select(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector) 
{
     bool used = false, inDB = false, inTable = false;
     int tableCount = 0, oldSize, newSize, valueCount, combo;
     std::string tableName, selectAtt1, selectAtt2, whereAtt, operater, compareValue, alias;
     std::vector<std::string> tableAliases, attValVector1, attValVector2;


     // Check for a database that's in use
     for (int i = 0; i < databaseVector.size(); i++) {

          if (databaseVector[i].inUse == true) {

               used = true;

               



               // See if we're working with one or more tables

               // If there are multiple tables that have been created
               if (databaseVector[i].tables.size() > 1) {

                    // Collect our tables aliases by going through all of the words and 
                    // finding our table names and then assigning aliases to them
                    // for (int j = 0; j < wordVector.size(); j++) {

                    //      if (wordVector[j] == "Employee") {

                    //           // Find alias name
                    //           alias = wordVector[j + 1];
                    //           // Add alias name to corresponding table (Employee)
                    //           databaseVector[i].tables[0].setAliasName(alias);
                    //           // Add alias name to vector
                    //           tableAliases.push_back(alias);

                    //      }

                    //      else if (wordVector[j] == "Sales") {

                    //           // Find alias name
                    //           alias = wordVector[j + 1];
                    //           // Add alias name to corresponding table (Sales)
                    //           databaseVector[i].tables[1].setAliasName(alias);
                    //           // Add alias name to vector
                    //           tableAliases.push_back(alias);

                    //      }

                    // }
 
                    // Figure out what types of Select statements we have here
                    for (int j = 0; j < wordVector.size(); j++) {
                         
                         // A join using "where"
                         if (wordVector[j] == "where") {

                              // Grab comparison operator
                              operater = wordVector[9];
                              
                              
                              if (operater == "=") {   

                                   size_t found1 = wordVector[8].find(".id");
                                   size_t found2 = wordVector[10].find(".employeeID");


                                   // If the two different attributes from two different tables are present
                                   if (found1 != std::string::npos && found2 != std::string::npos) {

                                        // Grab the values from both attributes and store them in two vectors
                                        databaseVector[i].tables[0].getAttValues("id", attValVector1);
                                        databaseVector[i].tables[1].getAttValues("employeeID", attValVector2);

                                        
                                        //combo = attValVector1.size() * attValVector2.size();

                                        // Print out the attributes
                                        databaseVector[i].tables[0].displayAttributes();
                                        databaseVector[i].tables[1].displayAttributes();

                                        std::cout << "\n";
                                        
                                        // Now we need to compare the values and print out the ones that match
                                        for (int k = 0; k < attValVector1.size(); k++) {

                                             for (int l = 0; l < attValVector2.size(); l++) {

                                                  if (attValVector1[k] == attValVector2[l]) {
                                                       
                                                       databaseVector[i].tables[0].displayRow(k);
                                                       databaseVector[i].tables[1].displayRow(l);

                                                       std::cout << "\n";

                                                  }

                                             }

                         

                                        }

                                   }

                                   else {
                                        std::cout << "One or more attributes not recognized.\n";
                                   }

                              }



                         }
                         
                         // A join using "on"
                         else if (wordVector[j] == "on") {

                              // This is a inner join statement 
                              if (wordVector[5] == "inner") {

                                   // Grab comparison operator
                                   operater = wordVector[11];
                              
                              
                                   if (operater == "=") {   

                                        size_t found1= wordVector[10].find(".id");
                                        size_t found2= wordVector[12].find(".employeeID");


                                        // If the two different attributes from two different tables are present
                                        if (found1 != std::string::npos && found2 != std::string::npos) {

                                             // Grab the values from both attributes and store them in two vectors
                                             databaseVector[i].tables[0].getAttValues("id", attValVector1);
                                             databaseVector[i].tables[1].getAttValues("employeeID", attValVector2);

                                             
                                             //combo = attValVector1.size() * attValVector2.size();

                                             // Print out the attributes
                                             databaseVector[i].tables[0].displayAttributes();
                                             databaseVector[i].tables[1].displayAttributes();

                                             std::cout << "\n";
                                             
                                             // Now we need to compare the values and print out the ones that match
                                             for (int k = 0; k < attValVector1.size(); k++) {

                                                  for (int l = 0; l < attValVector2.size(); l++) {

                                                       if (attValVector1[k] == attValVector2[l]) {
                                                            
                                                            databaseVector[i].tables[0].displayRow(k);
                                                            databaseVector[i].tables[1].displayRow(l);

                                                            std::cout << "\n";

                                                       }

                                                  }

                              

                                             }

                                        }

                                        else {
                                             std::cout << "One or more attributes not recognized.\n";
                                        }

                                   }
                              
                              }
                              
                              
                              // This is a left outer join statement
                              else if (wordVector[5] == "left") {

                                   // Grab comparison operator
                                   operater = wordVector[12];
                              
                                   if (operater == "=") {   

                                        size_t found1= wordVector[11].find(".id");
                                        size_t found2= wordVector[13].find(".employeeID");


                                        // If the two different attributes from two different tables are present
                                        if (found1 != std::string::npos && found2 != std::string::npos) {

                                             // Grab the values from both attributes and store them in two vectors
                                             databaseVector[i].tables[0].getAttValues("id", attValVector1);
                                             databaseVector[i].tables[1].getAttValues("employeeID", attValVector2);

                                             
                                             //combo = attValVector1.size() * attValVector2.size();

                                             // Print out the attributes
                                             databaseVector[i].tables[0].displayAttributes();
                                             databaseVector[i].tables[1].displayAttributes();

                                             std::cout << "\n";
                              
                                             
                                             // Now we need to compare the values and print out the ones that match
                                             for (int k = 0; k < attValVector1.size(); k++) {

                                                  for (int l = 0; l < attValVector2.size(); l++) {

                                                       if (attValVector1[k] == attValVector2[l]) {

                                                            databaseVector[i].tables[0].displayRow(k);
                                                            databaseVector[i].tables[1].displayRow(l);

                                                            std::cout << "\n";

                                                       }
                                                  
                                                  }
                                             
                                             }
                              

                                             databaseVector[i].tables[0].displayRow(2);
                                             std::cout << " | ";
                                             std::cout << "\n";

                                        }

                                        else {
                                             std::cout << "One or more attributes not recognized.\n";
                                        }

                              

                                   
                                   }

                              
                              }
                              
                         }

                         
                    
                    }




               }

               // There is only one table that has been created
               else {

                    // Get table name that we're selecting from
                    tableName = wordVector[4];

                    // Search for the table we're working with 
                    for (int j = 0; j < databaseVector[i].tables.size(); j++) {

                         if (tableName == databaseVector[i].tables[j].getTableName()) {

                              inDB = true;

                              // For selecting picked individual attributes from ONE table
                              if (wordVector[3] == "from" && wordVector[5] == "where") {

                                   // Now to get our first attribute
                                   selectAtt1 = wordVector[1];

                                   // Second attribute
                                   selectAtt2 = wordVector[2];

                                   // Third "where" attribute
                                   whereAtt = wordVector[6];

                                   // Third "where" attribute
                                   operater = wordVector[7];

                                   // Third "where" attribute
                                   // Take off the ";" at the end
                                   oldSize = wordVector[8].size();
                                   newSize = oldSize - 1;
                                   wordVector[8].resize(newSize);
                                   compareValue= wordVector[8];

                                   // If attributes exists in table
                                   if ((databaseVector[i].tables[j].attInTable(selectAtt1)) && (databaseVector[i].tables[j].attInTable(selectAtt2))
                                        && (databaseVector[i].tables[j].attInTable(whereAtt))) {

                                        inTable = true;


                                        if (operater == "!=") {
                                        
                                             // If the selection doesn't happen 
                                             if (!databaseVector[i].tables[j].compareSelectOne(selectAtt1, selectAtt2, whereAtt, operater, compareValue)) {

                                                  std::cout << "Selection failed.\n";

                                             }

                                        
                                        
                                        }


                                   }

                                   if (!inTable) {
                                        std::cout << "Attributes not found.\n";
                                   }

                              }

                              else {
                                   std::cout << "FROM and WHERE must be included in SELECT command.\n";
                              }
                         
                              


                         }

                    }

                    if (!inDB) {
                         std::cout << "Table not found.\n";
                    }

               }
               
          }
     }

     if (!used) {

          // Must be using a database in order to create a table 
          std::cout << "Failed to select values because there is no database in use.\n";
     }

}

/* -----------------------------------------------------------------------------
FUNCTION:          updateTable()
DESCRIPTION:       allows the user to change certain data values within the table
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void updateTable(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector)
{
     bool used = false;
     bool inDB = false, inTable = false, valueFound = false;
     int tableCount = 0, valueCount = 0, oldSize, newSize;
     std::string tableName, setAttName, whereAttName, newUpdate, oldValue;

     // Check for a database that's in use
     for (int i = 0; i < databaseVector.size(); i++) {

          if (databaseVector[i].inUse == true) {

               used = true;

               // Get table name that we're inserting into
               tableName = wordVector[1];

               // Search for the table we're working with 
               for (int j = 0; j < databaseVector[i].tables.size(); j++) {

                    if (tableName == databaseVector[i].tables[j].getTableName()) {

                         inDB = true;
                          

                         if (wordVector[2] == "set") {

                              // If attributes exists in table
                              if ((databaseVector[i].tables[j].attInTable(wordVector[3])) && (databaseVector[i].tables[j].attInTable(wordVector[7]))) {

                                   inTable = true;

                                   
                                   // Take off the "'"s from our varchar values
                                   if (wordVector[5] == "'Gizmo'") {
                                        // Now to get our second value
                                        // Take off the "'" at the end
                                        oldSize = wordVector[5].size();
                                        newSize = oldSize - 1;
                                        wordVector[5].resize(newSize);

                                        // Erase the "'" at the beginning
                                        wordVector[5].erase(0, 1);
                                   }

                                   if ((wordVector[9] == "'Gizmo';") || (wordVector[9] == "'SuperGizmo';")) {
                                        // Now to get our second value
                                        // Take off the "';" at the end
                                        oldSize = wordVector[9].size();
                                        newSize = oldSize - 2;
                                        wordVector[9].resize(newSize);

                                        // Erase the "'" at the beginning
                                        wordVector[9].erase(0, 1);
                                   }

                              
                                   
                                   // heres our attribute name that we're gonna change the value of
                                   setAttName = wordVector[3];

                                   // heres our attribute name that decides which setAttName value(s) gets updated
                                   whereAttName = wordVector[7];

                                   // here is our old value
                                   oldValue = wordVector[9];

                                   // lets get our new string that we're going to update the table with
                                   newUpdate = wordVector[5];


                                   // If the value(s) that decide which other attributes values get updated exit 
                                   if (databaseVector[i].tables[j].attValueExits(whereAttName, oldValue, valueCount)) {

                                        valueFound = true;

                                        if (valueCount == 1) {
                                             
                                             // Attempt to update the value(s)
                                             if (databaseVector[i].tables[j].updateAttValue(whereAttName, setAttName, oldValue, newUpdate)) {

                                                  std::cout << "1 record modified.\n";

                                             }
                                        }

                                        else if (valueCount > 1) {

                                             // Attempt to update the value(s)
                                             if (databaseVector[i].tables[j].updateAttValue(whereAttName, setAttName, oldValue, newUpdate)) {

                                                  std::cout << valueCount << " records modified.\n";

                                             }
                                        }
                                        
                                        

                                   }

                                   if (!valueFound) {
                                        std::cout << "Where value not found.\n";
                                   }

                              }
                              

                              if (!inTable) {
                                   std::cout << "Attribute not found.\n";
                              }

                         }

                         else {
                              std::cout << "SET must follow UPDATE and Table Name\n";
                         }

                    
                    }

               
               }

               if (!inDB) {
                    std::cout << "Table not found.\n";
               }

          }
     }

     if (!used) {

          // Must be using a database in order to update values
          std::cout << "Failed to update values because there is no database in use.\n";
     }

}

/* -----------------------------------------------------------------------------
FUNCTION:          deleteRecords()
DESCRIPTION:       removes specific data values from the table 
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void deleteRecords(std::vector<std::string> &wordVector, std::vector<Database> &databaseVector)
{
     bool used = false, inDB = false, valueFound = false;
     int tableCount = 0, valueCount = 0, oldSize, newSize;
     std::string tableName, attName, valToDelete, operater;

     // Check for a database that's in use
     for (int i = 0; i < databaseVector.size(); i++) {

          if (databaseVector[i].inUse == true) {

               used = true;

               // Get table name that we're inserting into
               tableName = wordVector[2];

               // Search for the table we're working with 
               for (int j = 0; j < databaseVector[i].tables.size(); j++) {

                    if (tableName == databaseVector[i].tables[j].getTableName()) {

                         inDB = true;

                         if (wordVector[3] == "where") {

                              if (wordVector[5] == "=") {

                                   // Grab attribute catagory whcih contains the value we're trying to delete
                                   attName = wordVector[4];
                                   

                                   // Take off the "'"s from our varchar values
                                   if (wordVector[6] == "'Gizmo';") {
                                        
                                        // Now to get our second value
                                        // Take off the "'" at the end
                                        oldSize = wordVector[6].size();
                                        newSize = oldSize - 2;
                                        wordVector[6].resize(newSize);

                                        // Erase the "'" at the beginning
                                        wordVector[6].erase(0, 1);

                                        valToDelete = wordVector[6];
                                   }

                                   // Value we want to delete is not a varchar data type
                                   else {

                                        // Now to get our value
                                        // Take off the ";" at the end
                                        oldSize = wordVector[6].size();
                                        newSize = oldSize - 1;
                                        wordVector[6].resize(newSize);

                                        valToDelete = wordVector[6];
                                   }
                                   

                                   // If the value that we're trying to delete exits
                                   if (databaseVector[i].tables[j].attValueExits(attName, valToDelete, valueCount)) {

                                        valueFound = true;

                                        if (valueCount == 1) {

                                             if (databaseVector[i].tables[j].deleteValues(attName, valToDelete)) {
                                                  
                                                  std::cout << valueCount << " record deleted.\n";
                                             }
                                             
                                        }

                                        else if (valueCount > 1) {

                                             if (databaseVector[i].tables[j].deleteValues(attName, valToDelete)) {
                                                  
                                                  std::cout << valueCount << " records deleted.\n";
                                             }

                                        }

                                   }

                                   if (!valueFound) {
                                        std::cout << "Where value not found.\n";
                                   }

                              }


                              else if (wordVector[5] == ">") {
                                   
                                   // Grab attribute catagory which contains the value we're trying to delete
                                   attName = wordVector[4];

                                   // Now to get our value
                                   // Take off the ";" at the end
                                   oldSize = wordVector[6].size();
                                   newSize = oldSize - 1;
                                   wordVector[6].resize(newSize);

                                   // Grab string that contains the value that we're comparing the other values to
                                   valToDelete = wordVector[6];

                                   // Grab the operator string 
                                   operater = wordVector[5];

                                   // If the value that we're trying to delete exits
                                   if (databaseVector[i].tables[j].compareDelete(attName, valToDelete, operater, valueCount)) {

                                        valueFound = true;

                                        if (valueCount == 1) {

                                             std::cout << valueCount << " record deleted.\n";
                                             
                                        }

                                        else if (valueCount > 1) {

                                             std::cout << valueCount << " records deleted.\n";

                                        }

                                   }

                                   if (!valueFound) {
                                        std::cout << "Where value not found.\n";
                                   }


                              }

               
                         }

                         else {
                              std::cout << "WHERE must follow table name.\n";
                         }

               
                    }


               }

               if (!inDB) {
                    std::cout << "Table not found.\n";
               }
               
               

               
          }
     }

     if (!used) {

          // Must be using a database in order to create a table 
          std::cout << "Failed to delete values because there is no database in use.\n";
     }

}