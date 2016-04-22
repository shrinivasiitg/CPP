/*
 *
 *  Created on: Apr 14, 2016
 *      Author: Shrinivas
 *
 *
  */

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

/*
 * Displays the error message according to the error code and exits from program
 *
 * @param error code number
 * @return exits from program
 */
void errorCode(int errorCode) {

	switch(errorCode){
	case 1:
		cout << "Error : Invalid number of arguments" << endl;
		cout << "Please enter only one argument and that should be input file name" << endl;
		break;
	case 2:
		cout << "Error : Invalid input file" << endl;
		cout << "Please enter correct input file" << endl;
		break;
	case 3:
		cout << "Error : Empty input file" << endl;
		cout << "Please provide a file having correct input" << endl;
		break;
	default:
		exit(1);
	}
	exit(1);
}

/*
 * Validates command line arguments
 *
 * @param number of command line arguments
 */
void checkCommandLineArguments(int argc) {
	if(argc != 2) {
		cout << argc << endl;
		errorCode(1);
	}
	return;
}

/*
 * Validates if file is correct and has valid use cases
 *
 * @param fileName
 */
void validateInputFile(char* fileName){

	ifstream fin(fileName);
	if (!fin.good()) {
		errorCode(2);
	}
	if (fin.peek() == std::ifstream::traits_type::eof()) {
		errorCode(3);
	}
	return;
}

/*
 * Checks if there is a valid path
 *
 * @param board
 * @param array x
 * @param array y
 * @param current row
 * @param current column
 * @param current path number for knight
 * @param endnum to check path number
 *
 * @return bool
 * returns true if there is a valid path
 */
bool gotpath(int** &board, int* x, int* y,int row, int col, int path, int endnum) {
	if (board[row][col] != 0)
		return false;

	cout << path << endl;
	board[row][col] = path;

	if (path == endnum)
		return true;

	if (path > endnum)
		return false;

	// Checking recursively for the next possible move
	for (int i = 0; i < 8; i++) {
		if (gotpath(board, x, y, row + x[i], col + y[i], path + 1, endnum))
			return true;
	}

	board[row][col] = 0;

	return false;

}

/*
 * Generating output board in output file
 *
 * @param board
 * @param boardSize
 * @param outputFileWriter
 */
void printInFile(int** &board, int boardSize, ofstream &writeFile) {

	for (int i = 2; i < boardSize + 2; i++) {
		for (int j = 2; j < boardSize + 2; j++) {
			writeFile << board[i][j] << "\t" ;
		}
		writeFile << endl;
	}
	writeFile << endl;
}

/*
 * Allocating memory dynamically to board
 *
 * @param board
 * @param boardSize
 */
void allocateMemoryToBoard(int** &board, int boardSize) {
	board = new int*[boardSize];
	for(int i=0; i<boardSize; i++) {
		board[i] = new int[boardSize];
	}
}

/*
 * Freeing memory allocated to board
 *
 * @param board
 * @param boardSize
 */
void freeBoardMemory(int** &board, int boardSize) {
	for(int i=0; i<boardSize; i++) {
		free(board[i]);
	}
	free(board);
}

/*
 * Initializing board with -1
 *
 * @param board
 * @param boardSize
 */
void initializeBoard(int** &board, int boardSize) {
	for (int i = 0; i < boardSize + 4; i++) {
		for (int j = 0; j < boardSize + 4; j++) {
			board[i][j] = -1;
		}
	}
	for (int i = 2; i < boardSize + 2; i++){
		for (int j = 2; j < boardSize + 2; j++) {
			board[i][j] = 0;
		}
	}

}

/*
 * Printing current board
 *
 * @param board
 * @param boardSize
 */
void printBoard(int** &board, int boardSize) {
	for (int i = 2; i < boardSize + 2; i++){
		for (int j = 2; j < boardSize + 2; j++) {
			cout << board[i][j] << "\t";
		}
		cout << endl;
	}

}
int main(int argc, char*argv[]) {

	// Checking command line arguments
	checkCommandLineArguments(argc);

	// Validating file name
	validateInputFile(argv[1]);

	// Generating output file name from input
	int n, st_x, st_y;
	string inputFileName(argv[1]);
	string outputFileName = "";
	for (int i = 0; i < strlen(argv[1]); i++) {
		if (argv[1][i] == '.')
			break;
		outputFileName.push_back(argv[1][i]);
	}
	outputFileName = outputFileName + "out.txt";

	// File reader for reading file
	ifstream readFile;
	readFile.open(argv[1]);

	// File writer for writing output
	ofstream writeFile;
	writeFile.open(outputFileName);

	int puzzleNumber = 1;

	// Reading line from file
	readFile >> n >> st_x >> st_y ;

	do {
		writeFile << "Case: " << puzzleNumber << " - " << n << "x" << n << endl;
		writeFile << "Start row: " << st_x <<" Start column: " << st_y << endl;

		int** board;
		// Allocating memory dynamically
		allocateMemoryToBoard(board, n+4);

		// Initializing board
		initializeBoard(board, n);

		int x[8] = { -2, -2, -1, 1, 2, 2, 1, -1 };
		int y[8] = { -1, 1, 2, 2, 1, -1, -2, -2 };

		//checking the correct solution recursively
		if (gotpath(board, x, y, st_x + 2, st_y + 2, 1, n * n))
			printInFile(board, n,writeFile);
		else
			writeFile << "No Solutions for this case" << endl << endl;

		// Freeing memory before next puzzle;
		freeBoardMemory(board, n);

		puzzleNumber++;

		// Reading next line
		readFile >> n >> st_x >> st_y ;
	} while(!readFile.eof()); // Checking until End Of File

	// Closing file reader and writer
	readFile.close();
	writeFile.close();

	return 0;
}
