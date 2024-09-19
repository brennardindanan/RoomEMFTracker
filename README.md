# About
This program's purpose is to store Room IDs (between 350000 and 400000) and EMF Values (between 0.00 and 5.00) through repeated user input until desired exit or error. Once the data is gathered, Room IDs and their corresponding EMF values, along with the total amount of entries, shall be printed out in a table,  for easy readability. A second table will follow where Room IDs and corresponding EMF values above 4.5, and the total amount of entries that fit, will be printed as well. 

## Technologies Used
![C](https://img.shields.io/badge/-C-A8B9CC?style=flat&logo=c&logoColor=white) ![Linux](https://img.shields.io/badge/-Linux-FCC624?style=flat&logo=linux&logoColor=black)

# List of Files
- brennard_a1.c: Contains source code needed to execute
- README.md: Contains this description

# Compiling and Executing
1. Navigate to the folder containing the source code in a terminal,
2. Use the command 'make' to create the file 'a1' which can be executed,
3. use the command './a1' while in the folder containing the executable to run the program.

# Usage Instructions
1. Type one integer (between 350000 and 400000) and one float (between 0.00 and 5.00) when prompted, separated by a space, representing the Room ID and EMF Value respectively. Continue inputting until satisfied, however max entries is 16. 
2. When finished, type '-1 -1' to exit.
3. Analyze the first printed table, containing Room IDs and their corresponding EMF Values, along with the total number of entries.
4. Analyze the second printed table, containing Room IDs with the corresponding EMF Value above 4.5, along with the amount of entries that fit such a criteria. 
