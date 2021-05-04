# Design Document - Conner Fissell: Project 4

## Status
Project 4 is fully complete and runs as it should with all of the required functionalities. 

## System Design and Implementation
### Transactions and Commits
For this project, some fairly significant changes were made. Two additional functions were added to the driver file: begin() and commit(). These two functions are used along with the others to help make the transactions work with the program. Three other boolean variables were added to the Database struct in order to allow for conditional checking. This checking is what makes the program run correctly on two different terminal windows at the same time. 

When a table is created, a file is also created that holds the table in the form of three separate strings. This file is used as a foundational object in the programs folder directory to also allow the user to operate the program with two different terminal windows. When the user begins a transaction in the process 1 window, a while loop iterates through the file that houses the original table and checks to see if the "trans" and "p1" flags are set to false and true, and it also checks for a line that determines if it is the original tables values, not the updated ones. The update that finishes off round 1 of process 1 actually updates the Table and Attriubte class objects that make up the back bone of the program. 

For process 2 in the second window, a conditional statement in the "useDB()" function checks whether a file exists or not (this is our Flights.txt file that holds our table) and since that file was created in process 1, the condition is met and the new database is created and added to our datebase vector. The necessary booleans are also set accordingly as well. These flags then allow this second process to start it's own transaction but since process 1 never commited it's own transaction, the update and commit here won't be allowed and an error will pop up. The original "Flights.txt" file still holds the original values so those then get printed to the screen. 

Commiting back on process 1 now changes the values in the "Flights.txt" file to the updated ones and those can now get printed to the screen in both windows. This finishes up the SQL test for this project. 

 

## Interface, Testing, Compile and Execution
Project 4 has the same type of compilation and execution operation and functionality as Project 3. The pa4Code directory contains a .cpp driver file called "driver," two .h class files called "Table" and "Attribute," and a makefile called "Makefile." The interface of the program runs exactly how the example program from the TA test video ran. Running "make driver" compiles the program. Then entering "./driver" into the command prompt will launch the program into "SQL Mode." A "-->" symbol pops up letting the user know that the program is now ready to accept SQL commands. This program was created using VS Code on Ubuntu 20.10. No external libraries that need to be downloaded and installed locally were used. 