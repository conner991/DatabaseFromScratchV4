# Design Document - Conner Fissell: Project 3

## Status
Project 3 is fully complete and runs as it should with all of the required functionalities. 

## System Design and Implementation
### Joins
For the implementation of the joins, I made significant changes to the "Select" function in the driver file. I modified it to recognize how many tables have been created. In this case we have created two tables, "Employee" and "Sales," the function hits an if statement that checks the database struct objects tables vectors size and if it is greater than one, we enter the if statement's scope.

Next, we enter a for loop that iterates over the number of string words that are in the wordVector. This gives us a chance to test each string so we can figure out which type of SQL command was entered into the prompt. For this project we have three different types of Joins being entered: a "Where" join, a "Inner" join, and a "left outer" join. All three of these joins use the same major technique to test the different data collected in the two tables in order for the join to work appropriately. 

An if statement tests the type of operator located in the wordVector so that the function can decide what type of comparison operation needs to be performed. In this case the SQL statement is going to test equality between two different attributes, the Employee id column and the Sales employeeID column which both contain ints. These are stored as strings and get converted to ints if necessary. Another if statement checks to see that the wordVector contains the right attribute phrases and then goes into a double nested for loop the compare the two attribute columns. 

The for loops perform comparisons between all the the two attributes values so for our two tables, since there are three values in both attributes, there will be a total of 9 comparisons to check for all cases of equality. Whenever any of the values in the two attribute columns matches, we enter an if statement that calls a Table member function on both tables. This function is called "displayRow" and it cycles through all attributes in the table and prints their values to the screen depending on which location int value was passed into the function. This location value determines the row of the table that will be printed. This tells the Attribute "displayValue" function which value to print and this location value is passed into the displayRow function based on the nested for loops from before. 

This is the essence of how the joins work. Since the first two joins print the same information but with different syntax, the code follows a mostly similar procedure. For the left outer join, all that code does differently is print some additional material at the end, this being the extra and final row from the Employee table. 
 

## Interface, Testing, Compile and Execution
Project 3 has the same type of compilation and execution operation and functionality as Project 2. The pa3Code directory contains a .cpp driver file called "driver," two .h class files called "Table" and "Attribute," and a makefile called "Makefile." The interface of the program runs exactly how the example program from the TA test video ran. This design was also modeled after the terminal interface design that is on the paper guide. Running "make driver" compiles the program. Then entering "./driver" into the command prompt will launch the program into "SQL Mode." A "-->" symbol pops up letting the user know that the program is now ready to accept SQL commands. This program was created using VS Code on Ubuntu 20.10. No external libraries that need to be downloaded and installed locally were used. 