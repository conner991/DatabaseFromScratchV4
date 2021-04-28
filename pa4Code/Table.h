/* -----------------------------------------------------------------------------
FILE NAME:         Table.h
DESCRIPTION:       Class file that holds the base class "Table"
USAGE:             
COMPILER:          GNU g++ compiler on Linux
NOTES:             This class holds all of the necessary information pertaining to 
                    a created Table (name, number of attributes, and the attribute 
                    objects themselves). This class inherits from the Attribute class
                    and uses many of that class' member functions to handle the metadata
                    of the table. The driver uses this classes objects and member fucntions
                    more often than the Attribute classes objects and functions.

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Conner Fissell     04-07-2021         Initial Set up
Conner Fissell     04-09-2021         Updated Parser
Conner Fissell     04-10-2021         Worked on Selects
Conner Fissell     04-11-2021         Finished Selects
Conner Fissell     04-12-2021         Turned in project
----------------------------------------------------------------------------- */
#ifndef __TABLE_H__
#define __TABLE_H__

#include "Attribute.h"


class Table : public Attribute {
     private:
          std::string tableName, alias;
          int numOfAttributes;
          std::vector<Attribute> attributes; 

     public:

          Table() {};
          ~Table() {};

          /* -----------------------------------------------------------------------------
          FUNCTION:          Table()
          DESCRIPTION:       Parameterized constructor
          RETURNS:           None
          NOTES:             
          ------------------------------------------------------------------------------- */
          Table(std::string name) {
               tableName = name;
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          addAttribute()
          DESCRIPTION:       Pushes an attribute to the attributes vector
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void addAttribute(Attribute a) {
               attributes.push_back(a);
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          getNumOfAttributes()
          DESCRIPTION:       Returns the number of attributes in the table 
          RETURNS:           int
          NOTES:             
          ------------------------------------------------------------------------------- */
          int getNumOfAttributes() {
               
               numOfAttributes = attributes.size();
               
               return numOfAttributes;
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          getAttribute()
          DESCRIPTION:       Returns the attribute name that gets passed in
          RETURNS:           string
          NOTES:             
          ------------------------------------------------------------------------------- */
          std::string getAttribute(std::string attName) {

               // Cycle through vector of attributes
               for (int i = 0; i < attributes.size(); i++) {

                    if (attributes[i].getName() == attName) {
                         return attributes[i].getName();
                    }
               }
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          attInTable()
          DESCRIPTION:       Determines if an attribute exists in the table 
          RETURNS:           bool
          NOTES:             
          ------------------------------------------------------------------------------- */
          bool attInTable(std::string attName) {

               bool inTable = false;

               // Cycle through vector of attributes
               for (int i = 0; i < attributes.size(); i++) {

                    if (attributes[i].getName() == attName) {
                         inTable = true;
                         return inTable;
                    }
               }

               if (!inTable) {
                    std::cout << "Attribute not found.\n";
               }

               return inTable;
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          removeAttribute()
          DESCRIPTION:       Removes an attribute from the table
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void removeAttribute(Attribute a) {
               
               Attribute tempAtt;
               std::string tempName;

               for (auto it = attributes.begin(); it != attributes.end(); it++) {
                    
                    tempAtt = *it;
                    tempName = tempAtt.getName();

                    if (tempName == a.getName()) {
                         attributes.erase(it);
                    }
               }
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          displayTableName()
          DESCRIPTION:       Prints the tables name to the screen
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void displayTableName() {
               std::cout << "Table name is: " << tableName << "\n";
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          displayAttributes()
          DESCRIPTION:       Prints all of the attributes in the table to the screen
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void displayAttributes() {

               for (int i = 0; i < attributes.size(); i++) {
                    
                    attributes[i].displayAttribute();
                    std::cout << " | ";
               }

               //std::cout << "\n";
               
          }    

          /* -----------------------------------------------------------------------------
          FUNCTION:          displayRow()
          DESCRIPTION:       Calls the displayValue attribute memeber function repeatedly for 
                              all the attributes in the table. Prints the row at location
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void displayRow(int location) {

               for (int i = 0; i < getNumOfAttributes(); i++) {

                    attributes[i].displayValue(location);
               }

          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          displayAttributesAndValues()
          DESCRIPTION:       Prints out all of the attrbutes and corresponding values to the
                              screen
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void displayAttributesAndValues() {

               // Print out attributes
               for (int i = 0; i < attributes.size(); i++) {
                    
                    attributes[i].displayAttribute();
                    std::cout << " | ";
               }

               std::cout << "\n";

               for (int j = 0; j < attributes[0].getNumOfValues(); j++) {

                    // Print out related values 
                    for (int k = 0; k < attributes.size(); k++) {

                         attributes[k].displayValue(j);
                    }

                    std::cout << "\n";
               }
               
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          getTableName()
          DESCRIPTION:       Returns the name of the table
          RETURNS:           string
          NOTES:             
          ------------------------------------------------------------------------------- */
          std::string getTableName() {
               return tableName;
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          clearTable()
          DESCRIPTION:       Deletes all of the attributes in the table
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void clearTable() {
               attributes.clear();
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          addValues()
          DESCRIPTION:       Adds the values in the valVector to the arributes
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void addValues(std::vector<std::string> valVector) {

               // Here we add each value in valVector to it's corresponding attribute object
               // using the addValue method in the Attribute class
               for (int i = 0; i < attributes.size(); i++) {
                    attributes[i].addValue(valVector[i]);
               }

          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          setAliasName()
          DESCRIPTION:       Sets the alias name for the table
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void setAliasName(std::string a) {
               alias = a;
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          getAliasName()
          DESCRIPTION:       Returns the alias name
          RETURNS:           string
          NOTES:             
          ------------------------------------------------------------------------------- */
          std::string getAliasName() {
               return alias;
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          getAttValues()
          DESCRIPTION:       Returns a vector of values in an attribute
          RETURNS:           vector<string>
          NOTES:             
          ------------------------------------------------------------------------------- */
          std::vector<std::string> getAttValues(std::string att, std::vector<std::string> &valVector) {

               std::string temp;

               // Grab all the values from a specific attribute
               for (int i = 0; i < attributes.size(); i++) {
                    
                    if (attributes[i].getName() == att) {

                         // Load up valVector with attributes[i]s values
                         for (int j = 0; j < attributes[i].getNumOfValues(); j++) {
                              temp = attributes[i].getValue(j);
                              valVector.push_back(temp);
                         }
                    }
                    
               }

               return valVector;

          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          attValuesExits()
          DESCRIPTION:       Determines whether an attribute and its values exit in the table
          RETURNS:           bool
          NOTES:             
          ------------------------------------------------------------------------------- */
          bool attValueExits(std::string attName, std::string val, int &valueCount) {

               bool inAtt = false;

               // search for passed in value in attributes vector object
               // Cycle through vector of attributes
               for (int i = 0; i < attributes.size(); i++) {

                    if (attributes[i].getName() == attName) {
                         
                         // search for specific value within the attribute object
                         for (int j = 0; j < attributes[i].getNumOfValues(); j++) {
                              
                              if (inAtt) {
                                   return inAtt; 
                              }

                              // If the value is there
                              if (attributes[i].valuesExist(val, valueCount)) {
                                   
                                   inAtt = true;
                              }
                         }

                         
                    }

               }

               return inAtt;

          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          compareDelete()
          DESCRIPTION:       Compares values in the attribute and deletes the ones that satisfy
                              the comparison condition 
          RETURNS:           bool
          NOTES:             
          ------------------------------------------------------------------------------- */
          bool compareDelete(std::string attName, std::string value, std::string operater, int &valueCount) {

               bool comparable = false;
               std::vector<int> valueIndexes;
               float fValue1, fValue2;

               if (operater == ">") {

                    // Cycle through vector of attributes to find the one we're comparing values within
                    for (int i = 0; i < attributes.size(); i++) {

                         if (attributes[i].getName() == attName) {
                         
                              // search for specific value within the attribute object
                              for (int j = 0; j < attributes[i].getNumOfValues(); j++) {

                                   // First convert our strings to floats so we can compare
                                   fValue1 = std::stof(value);
                                   fValue2 = std::stof(attributes[i].getValue(j));


                                   // If our comparing value is less than the ones in the attributes value 
                                   // vector, then save the indexes.
                                   if (fValue1 < fValue2) {

                                        valueIndexes.push_back(j);     
                                        valueCount++; 
                                        comparable = true;
                                   }
                              }

                              // Go through every attribute and delete every value at their respective indexes
                              for (int i = 0; i < attributes.size(); i++) {

                                   comparable = attributes[i].deleteValue(valueIndexes);                    

                              }

                         
                         }

                    }

               }

               return comparable;

          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          compareSelectOne()
          DESCRIPTION:       Compares different values between attributes for one table and
                              prints the ones that satisfy the condition to the screen
          RETURNS:           bool
          NOTES:             
          ------------------------------------------------------------------------------- */
          bool compareSelectOne(std::string selectAtt1, std::string selectAtt2, std::string whereAtt, std::string operater, std::string compareValue) {
          
               bool selected1 = false, selected2 = false;
               std::vector<int> valueIndexes;
               int v1, v2, valueCount = 0;

               if (operater == "!=") {

                    // Cycle through vector of attributes to find the one we're comparing values within
                    for (int i = 0; i < attributes.size(); i++) {

                         if (attributes[i].getName() == whereAtt) {

                              // search through where attribute so we can compare values within it
                              for (int j = 0; j < attributes[i].getNumOfValues(); j++) {

                                   // First convert our strings to ints so we can compare
                                   v1 = std::stoi(compareValue);
                                   v2 = std::stoi(attributes[i].getValue(j));


                                   // If our comparing value doesn't equal the ones in the attribute's value 
                                   // vector, then save the indexes.
                                   if (v1 != v2) {

                                        valueIndexes.push_back(j);     
                                        valueCount++; 
                                        selected1 = true;
                                   }
                              }

                         }

                    }

                    // We want to display every attribute value within valueIndexes AND 
                    // thats NOT within the where attribute.

                    // First display the attributes
                    for (int i = 0; i < attributes.size(); i++) {
                    
                         if (attributes[i].getName() != whereAtt) {
                         
                              attributes[i].displayAttribute();
                              std::cout << " | ";
                         }
                    
                    }

                    std::cout << "\n";

                    // Then display the associated values
                    for (int i = 0; i < attributes.size(); i++) {
                    
                         if (attributes[i].getName() != whereAtt) {

                              for (int j = 0; j < valueCount; j++) {

                                   attributes[i].displayValue(valueIndexes[j]);
                                   selected2 = true;
                                   
                              }
                         
                         }
                    
                    }

                    std::cout << "\n";

                    if (selected1 && selected2) {
                         return selected1;
                    }


               }

               return selected1;
          
          
          
          
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          updateAttValue()
          DESCRIPTION:       Compares different attribute values with each other and updates
                              the values accordingly
          RETURNS:           bool
          NOTES:             
          ------------------------------------------------------------------------------- */
          bool updateAttValue(std::string whereAttName, std::string setAttName, std::string oldValue, std::string newValue) {

               bool success;
               int where, set;
               std::vector<int> valueIndexes;


               // if we're updating the same attribute
               if (whereAttName == setAttName) {

                    // Cycle through vector of attributes
                    for (int i = 0; i < attributes.size(); i++) {
                    
                         if (attributes[i].getName() == setAttName) {

                              success = attributes[i].updateValue(oldValue, newValue);

                         }      
                    }              

               }

               // We're changing an attribute value based on 1 or more different attribute values
               else {

                    // search for passed in value in attributes vector object
                    // Cycle through vector of attributes
                    for (int i = 0; i < attributes.size(); i++) {

                         // Find our deciding attribute
                         if (attributes[i].getName() == whereAttName) {
                         
                              // find our "where" attribute number
                              where = i;
                         
                         }

                         // Find our set attribute
                         if (attributes[i].getName() == setAttName) {
                         
                              // find our "set" attribute number
                              set = i;
                         
                         }

                    }

                    // go into the where attribute and figure out which values are getting counted and updated 
                    attributes[where].getValueIndexes(oldValue, valueIndexes);

                    // Noe go into the set attribute and set the indexes values to the new value
                    success = attributes[set].updateMultipleValues(attributes[where], newValue, oldValue);


               }

               return success;

          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          deleteValues()
          DESCRIPTION:       Removes values from the specified attribute
          RETURNS:           bool
          NOTES:             
          ------------------------------------------------------------------------------- */
          bool deleteValues(std::string attName, std::string valToDelete) {

               bool deleted = false;
               std::vector<int> valueIndexes;

               // Search for attribute that contains the value we want to delete 
               for (int i = 0; i < attributes.size(); i++) {

                    if (attributes[i].getName() == attName) {

                         // Figure out the indexes of where it's located in the attribute values vector
                         attributes[i].getValueIndexes(valToDelete, valueIndexes);

                    }

               }

               // Go through every attribute and delete every value at their respective indexes
               for (int i = 0; i < attributes.size(); i++) {

                    deleted = attributes[i].deleteValue(valueIndexes);                    

               }

               return deleted;

          }

          

};


#endif
