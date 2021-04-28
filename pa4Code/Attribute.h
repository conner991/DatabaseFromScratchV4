/* -----------------------------------------------------------------------------
FILE NAME:         Attribute.h
DESCRIPTION:       Class file that holds the base class "Attribute"
USAGE:             
COMPILER:          GNU g++ compiler on Linux
NOTES:             This class holds all of the relevant information pertaining to 
                    an attribute within a table (name, data type, values). Allows for
                    manipulation and accessing of that data.

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Conner Fissell     04-07-2021         Initial Set up
Conner Fissell     04-09-2021         Updated Parser
Conner Fissell     04-10-2021         Worked on Selects
Conner Fissell     04-11-2021         Finished Selects
Conner Fissell     04-12-2021         Turned in project
----------------------------------------------------------------------------- */
#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <sys/stat.h> 
#include <sys/types.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <regex>
#include <iterator>
#include <stdio.h>
#include <unistd.h>




class Attribute {
     private: 
          std::string attributeName, attributeType;
          int numOfValues;
          std::vector<std::string> values;

     public:
          Attribute() {};
          ~Attribute() {};

          /* -----------------------------------------------------------------------------
          FUNCTION:          Attribute()
          DESCRIPTION:       Parameterized Constructor
          RETURNS:           None
          NOTES:             
          ------------------------------------------------------------------------------- */
          Attribute(std::string name, std::string type) {
               attributeName = name;
               attributeType = type;
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          createAttribute()
          DESCRIPTION:       Creates a new attribute by naming it and defining its type
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void createAttribute(std::string name, std::string type) {
               attributeName = name;
               attributeType = type;
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          displayAttribute()
          DESCRIPTION:       Prints one attribute to the screen
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void displayAttribute() {
               std::cout << attributeName << " " << attributeType;
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          getName()
          DESCRIPTION:       Returns an attributes name
          RETURNS:           string
          NOTES:             
          ------------------------------------------------------------------------------- */
          std::string getName() {
               return attributeName;
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          getNumOfValues()
          DESCRIPTION:       Returns the amount of values an attribute holds
          RETURNS:           int
          NOTES:             
          ------------------------------------------------------------------------------- */
          int getNumOfValues() {
               numOfValues = values.size();
               return numOfValues; 
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          addValue()
          DESCRIPTION:       Pushes a passed string into the values vector
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void addValue(std::string val) {
               values.push_back(val);
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          deleteValue()
          DESCRIPTION:       Removes a value from the values vector
          RETURNS:           bool
          NOTES:             
          ------------------------------------------------------------------------------- */
          bool deleteValue(std::vector<int> &valueIndexes) {

               bool deleted = false;
               int count = 0;
               std::string tempValue;
               
               
               // std::vector<std::string>::iterator it1 = values.begin();
               // std::vector<std::string>::iterator it2 = values.begin();

               // values.erase(values.begin());
               // values.erase(values.begin() + 3);

               // deleted = true;

               //auto nextIT = next(it1, valueIndexes[i]);

               // advance(it1,valueIndexes[i]);

               // values.erase(it1);


               for (int i = 0; i < valueIndexes.size(); i++) {

                    values.erase(values.begin() + valueIndexes[i]);
                    deleted = true;

               }

               return deleted;

          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          displayValue()
          DESCRIPTION:       Prints a value to the screen
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void displayValue(int i){

               std::cout << values[i] << " | ";
                   
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          valuesExist()
          DESCRIPTION:       Determines if a value is in the values vector
          RETURNS:           bool
          NOTES:             
          ------------------------------------------------------------------------------- */
          bool valuesExist(std::string val, int &valueCount) {

               bool valExists = false; 

               for (int i = 0; i < values.size(); i++) {

                    if (val == values[i]) {
                         valExists = true;
                         valueCount++;
                    }
               }

               return valExists;

          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          getValue()
          DESCRIPTION:       Returns a value at the passed in position i
          RETURNS:           string
          NOTES:             
          ------------------------------------------------------------------------------- */
          std::string getValue(int i) {
               return values[i];
          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          getValueIndexes()
          DESCRIPTION:       Pushes values that correspond to specific value positions in the 
                              values vector
          RETURNS:           void
          NOTES:             
          ------------------------------------------------------------------------------- */
          void getValueIndexes(std::string val, std::vector<int> &valueIndexes) {

               for (int i = 0; i < values.size(); i++) {

                    if (val == values[i]) {
                         
                         valueIndexes.push_back(i);
                         
                    }
               }

          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          getNumOfDuplicates()
          DESCRIPTION:       Returns the amount of times that a value is in the values vector
          RETURNS:           int
          NOTES:             
          ------------------------------------------------------------------------------- */
          int getNumOfDuplicates(std::string value) {

               int count = 0;

               // figures out how many of the same value are in this attribute
               for (int i = 0; i < values.size(); i++) {

                    if (values[i] == value) {
                         count++;
                    }
                    
               }

               return count;

          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          updateValue()
          DESCRIPTION:       Changes a value to a new passed in value
          RETURNS:           bool
          NOTES:             
          ------------------------------------------------------------------------------- */
          bool updateValue(std::string oldValue, std::string newValue) {

               bool success = false;

               for (int i = 0; i < values.size(); i++) {

                    if (oldValue == values[i]) {
                         
                         values[i] = newValue;
                         success = true;
                         return success;
                    }
               }

               return success;

          }

          /* -----------------------------------------------------------------------------
          FUNCTION:          updateMultipleValues()
          DESCRIPTION:       Updates multiple values in the values vector
          RETURNS:           bool
          NOTES:             
          ------------------------------------------------------------------------------- */
          bool updateMultipleValues(Attribute whereAtt, std::string newValue, std::string oldValue) {

               bool success = false;

               for (int i = 0; i < values.size(); i++) {

                    if (whereAtt.getValue(i) == oldValue) {
                         values[i] = newValue;
                         success = true;
                    }
                    

                    
               }

               return success;

          }
          
          

};




#endif