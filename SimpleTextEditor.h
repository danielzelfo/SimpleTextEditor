#include "List.h"
#include <iostream>
#include <string>

//the Text Editor Class
class SimpleTextEditor {
private:
	/* Private Data Members:
	 * The content - a list of characters
	 * The cursor - an iterator in the content list
	 */
	List<char> content;
	List<char>::Iterator cursor;

public:
	//constructor with starting string
	SimpleTextEditor(string);

	//move left or right
	bool moveLeft();
	bool moveRight();

	//insert or delete a character
	void insertChar(char);
	void deleteChar();

	//get or set current postition
	int currentPosition();
	bool goToPosition(int);

	//insert or delete word
	void insertWord(string);
	void deleteWord();

	//display the content with the cursor at the current position
	void display();

	//the menu
	void menu();
};

//constructor with strating string parameter
SimpleTextEditor::SimpleTextEditor(string startContent) {
	//looping through each character of the string and inserting it in the content list
	for (int i = 0; i < startContent.length(); i++)
		content.insertBack(startContent[i]);

	//setting the cursor to the end of the content
	cursor = ++content.end();
}

//move the cursor left if not already at the start
//returning a boolean to check for failure in the menu
bool SimpleTextEditor::moveLeft() {
	//checking if we aren't at the start
	if (cursor == content.begin())
		return false;

	//moving left
	--cursor;
	return true;
}

//move the cursor right if not already at the end
//returning a boolean to check for failure in the menu
bool SimpleTextEditor::moveRight() {
	//checking if we aren't at the end
	if (cursor == ++content.end())
		return false;

	//moving right
	++cursor;
	return true;
}

//insert a given character in the content at the position of the cursor
void SimpleTextEditor::insertChar(char insert) {
	content.insert(cursor, insert);
}

//deletes the character at the cursor
void SimpleTextEditor::deleteChar() {
	int tempPos = content.indexOf(cursor);

	//deleting the character that the cursor is on
	content.erase(cursor);

	//reseting the cursor
	cursor = content.atIndex(tempPos);
}

//return the postion of the cursor
int SimpleTextEditor::currentPosition() {
	return content.indexOf(cursor)-1;
}

//sets the cursors position to the given one (if it is in the range)
//returning a boolean to check for failure in the menu
bool SimpleTextEditor::goToPosition(int pos) {
	//validating the position
	if (pos > content.size() || pos < 0)
		return false;

	//setting the cursors positon using the list's atIndex function
	cursor = content.atIndex(pos);
	return true;
}

//displays the content with the cursor at the correct position
void SimpleTextEditor::display() {
	//content.print();
	cout << "\"";
	//looping through the content, displaying the cursor if we reached it, and displaying each character
	for (List<char>::Iterator it = content.begin(); it != ++content.end(); ++it) {
		if (content.indexOf(it) == content.indexOf(cursor))
			cout << ">";
		cout << *it;
		
	}
	//outputting the cursor if it was after the last character in the list
	if (cursor == ++content.end())
		cout << ">";

	//outputting the length of the content
	cout << "\"" << endl << "Length: " << content.size() << endl;
	
}

//inserts a given word as a string
void SimpleTextEditor::insertWord(string word) {
	for (int i = 0; i < word.length(); i++)
		insertChar(word[i]);
	insertChar(' ');
}

//deletes the word in front of the cursor
void SimpleTextEditor::deleteWord() {
	while (*cursor != ' ')
		deleteChar();
	deleteChar();
}

//the menu - to allow the console to use all the features of the text editor
void SimpleTextEditor::menu() {
	int option;
	char inChar;
	string inStr;
	int inPos;
	bool response;

	cout << "Editing document..." << endl << endl;

	//outputting the menu
	cout << "\tEditing Menu" << endl << endl;
	cout << "1. Left" << endl
		 << "2. Right" << endl
		 << "3. Insert character" << endl
		 << "4. Delete character" << endl
		 << "5. Get current position" << endl
		 << "6. Go to position" << endl
		 << "7. Display" << endl
		 << "8. Insert Word" << endl
		 << "9. Delete Word" << endl
		 << "10. Quit" << endl << endl;


	//getting first option
	cout << "Enter an option: ";
	cin >> option;

	//while the option entered is not 10 (the option to quit)
	//we will run the appropriate function for every given option
	while(option != 10){
		if (option == 1) {
			//moving left and saving the response
			response = moveLeft();

			//outputting the appropriate result based on the response
			if (response)
				cout << "Moved cursor left." << endl;
			else
				cout << "Cursor is already at start.\n";
		}
		else if (option == 2) {
			//move right and save response
			response = moveRight();

			//outputting the appropriate result based on the response
			if (response)
				cout << "Moved cursor right." << endl;
			else
				cout << "Cursor is already at end." << endl;
		}
		else if (option == 3) {
			//getting character to be inserted
			cout << "Enter a character: ";
			cin >> inChar;

			//inserting the character
			insertChar(inChar);
			cout << "Inserted character " << inChar << "." << endl;
		}
		else if (option == 4) {
			//deleting a character
			deleteChar();
			cout << "Deleted one character." << endl;
		}
		else if (option == 5)
			//outputting the current position
			cout << "Current position: " << currentPosition() << endl;
		else if (option == 6) {
			//getting the postion to go to
			cout << "Enter position: ";
			cin >> inPos;

			//going to the position and saving the reponse
			response = goToPosition(inPos);

			//outputting the appropriate result based on the response
			if (response)
				cout << "Moved to position " << inPos << endl;
			else
				cout << "Invalid positon." << endl;
		}
		else if (option == 7) {
			//outputting the content of the text editor
			cout << "String: ";
			display();
		}
		else if (option == 8) {
			//inputting a word
			cout << "Enter a word: ";
			cin >> inStr;

			//inserting the word
			insertWord(inStr);
			cout << "Inserted " << inStr << "." << endl;
		}
		else if (option == 9) {
			//deleting a word
			deleteWord();
			cout << "Deleted word." << endl;
		}
		
		cin.ignore(10000, '\n');

		//getting the next uset input
		cout << endl << "Enter an option: ";
		cin >> option;
	}
	cout << "Thank you for using my program." << endl;
}