/*  Program: Calculator v1.1 (with extra credit a)
 *	Author: Daniel Zelfo
 *	Class: CSCI 220
 *	Date: 11/4/2019
 *	Description: This Program consists of a Simple Text Editor Class which uses a List Class to hold its content. 
 *				 The text editor is able to move between the content characters, input characters and words, delete characters and words, and display its content.
 *	I certify that the code below is my own work.
 *
 *	Exception(s): N/A
 *
 */

#include <iostream>
#include "SimpleTextEditor.h"
//#include "List.h"

using namespace std;

int main()
{
	//getting the starting string from teh user and creating the editor object
	string startStr;
	cout << "Enter a start string: ";
	getline(cin, startStr);
	SimpleTextEditor editor(startStr);

	//running the menu in the text editor
	editor.menu();
}