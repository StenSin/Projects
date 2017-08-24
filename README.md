# emProject to CMake converter

This project takes an existing emProject xml-file as input and creates a CMake file as output .txt file. The program uses pugiXML library as xml-parser and is written in C++.

## Prerequisites

Jetbrains CLion version 2017.2.1 was used to create this program, which can be downloaded from https://www.jetbrains.com/clion/. A 30 day trial is possible to try out the program. There is also possibility to get a student licence as an university student. Installation guide of CLion can be found here: https://medium.com/@RobertSimoes/installing-clion-on-windows-for-c-c-newbies-like-me-4a346aaf9557
PugiXML library is used with this project in order to parse the .xml file.  This can be downloaded from https://github.com/zeux/pugixml . The necessary files, which need to be downloaded for using in this program can be found under : https://github.com/zeux/pugixml/tree/master/src .

## Using this program

A step by step series of examples that tell you have to get a development env running
1.	A folder needs to be created in order to run this program.
2.	The files found under this project need to be added to the program folder
3.	Folder named cmake-build-debug needs to be created. 
4.	The files downloaded from PugiXML need to be added to cmake-build-debug folder.
5.	The .xml emProject file, which is going to be converted to CMake needs to be added to the same folder. 
6.	 CLion needs to be opened. 
7.	Import project needs to be chosen and the path described as the location of the folder created for this program.
8.	Now that the program is chosen, the following changes need to be made in the code in main.cpp file.
9.	On line 26, the “tree2.xml” needs to be replaced with the name of the .xml file that is going to be converted (and has already been put to the correct folder as described ins step 5.
10.	On line number 120, the word Project2.txt needs to be replaced with the name of the file, which you want to be received as a .txt file converted into CMake. In this case the name is “Project2.txt. “ 
11.	The program needs to be run on the IDE, by using combination Alt+Shift+ F12 or from the menu Run by choosing Run.
12.	After the program has run, the filename that was chosen in step 10, can be found at the cmake-build-debug folder converted from .xml to cmake file. 


