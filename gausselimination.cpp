#include<iostream>
#include<vector>
#include<cmath>
#include <iomanip>

/*void print_matrices(int columns, int rows, void*x, double b_matrix[]) {
	//typedef double arrtype[][columns];
	//arrtype & arr = *reinterpret_cast<arrtype*>(ptr);
	int (*arr)[columns] = static_cast<int (*)[m]>(x);
	
	int length = rows * columns;
	int print_row{0};
	int print_column{0};
	for (int i{0}; length > i; ++i) {	//print matrix
		if (print_column % columns == 0 && print_column != 0) {
			std::cout << '\n';
			++print_row;
			print_column = 0;
		}
		std::cout <<  std::setw(10) << arr[print_row][print_column];
		++print_column;
	}
	std::cout << '\n' << '\n';
	
	for (int i{0}; columns > i; ++i) {
			std::cout << std::setw(10) << b_matrix[i];
		}
		std::cout << '\n' << '\n';
}*/

int main () {
	std::cout << "enter the size of your matrix in the form num x num\n"; 
	int rows{0};
	int columns{0};
	char x{'x'};
	std::cin >> rows >> x >> columns;
	
	if (rows < 1 || columns < 1) {
		std::cerr << "out of range";
		return 1;
	}
	
	double a_matrix [rows][columns];		//declare size of A
	int length = rows * columns;
	
	std::cout << "Enter matrix values starting from top left. Then moving down the columns\n";
	
	int fill_row{0};
	int fill_column{0};					//create fill variables
	double a_stuffing{0};				//create stuffing for A
	
	for (int i{0}; length > i; ++i) {	//stuff A
		if (fill_column % columns == 0 && fill_column != 0) {
			++fill_row;
			fill_column = 0;
		}
		
		std::cin >> a_stuffing;
		a_matrix [fill_row][fill_column] = a_stuffing;
		++fill_column;
	}
	
					//create print variables
	
	std::cout << "\nEnter the b matrix\n";
	
	double b_matrix[rows];			
	double b_stuffing{0};
	
	for (int i{0}; rows > i; ++i) {		//create b matrix and stuff it
		std::cin >> b_stuffing;
		b_matrix[i] = b_stuffing;
	}
	
	//MATH STARTS HERE*************************************************************************************
	int eval_row{0};
	int eval_column{0};
	int track{0};
	int fail{0};
	//int fail2{0};
	int track_row{0};
	int track_column{0};
	
	while (track_row < rows && track_column < columns) {
		while (a_matrix[eval_row][track_column] != 1) {
			if (eval_row == (rows - 1)) {
				fail = 1;
				break;
				std::cout << "no lead 1\n";
			}
			++eval_row;
			++track;
		}
		
		eval_row = track_row;
		track = track + track_row; 
	
		if (fail == 0) {
			std::cout << "initiating switch to get lead 1\n";
			if (a_matrix[track_row][track_column] == 1) {
				
			}
			else {
			double save [columns - track_column];
			for (int i{track_column}; i < columns; ++i) {
				save[i] = a_matrix[track_row][i];
				a_matrix[track_row][i] = a_matrix[track][i];
				a_matrix[track][i] = save[i];
			}
			double b_save;
					b_save = b_matrix[track_row];
					b_matrix[track_row] = b_matrix[track];
					b_matrix[track] = b_save;
			}
		}
		else if (fail == 1) {
			std::cout << "initiating division to create lead 1\n";
			eval_row = track_row;
			eval_column = track_column;
			fail = 0;
			track = track_row;
			while (a_matrix[eval_row][track_column] == 0) {
				if (eval_row == (rows - 1)) {
					fail = 1;
					break;
				}
				++eval_row;
				++track;
			}
			eval_row = track_row;

			if (fail == 0) {
				double copy{a_matrix[track][track_column]};
				b_matrix[track] = b_matrix[track] / copy;
				for (int i{track_column}; i < columns; ++i) { 
					a_matrix[track][i] = a_matrix[track][i] / copy;
				}																//Dividing row
				if (track != track_row){										//If this is not the row we are working on, switch the rows
					double save [columns];
					for (int i{0}; i < columns; ++i) {
						save[i] = a_matrix[track_row][i];
						a_matrix[track_row][i] = a_matrix[track][i];
						a_matrix[track][i] = save[i];
					}
					double b_save;
					b_save = b_matrix[track_row];
					b_matrix[track_row] = b_matrix[track];
					b_matrix[track] = b_save;
				}
			}
		
			else if (fail == 1) {
				std::cerr << "\nWhy did you give me a matrix with an unused variable?\n";
				return 1;
			}
			else {
				std::cerr << "\nFail is not 1 or 0, something is wrong.\n";
				return 2;
			}
		}
		else {
			std::cerr << "\nFail is not 1 or 0, something is wrong.\n";
			return 2;
		}
	
		
		//print_matrices(columns, rows, a_matrix[][], b_matrix[]);
		
		for (int i{track_row + 1}; rows > i; ++i) {
			double copy{a_matrix[i][track_column] / a_matrix[track_row][track_column]};
			for (int j{track_column}; columns > j; ++j) {					//There is a bug here*********************************************************
				//double copy{-1 * a_matrix[i][j] / a_matrix[track_row][track_column]};
				double copy2{copy * a_matrix[track_row][j]};
				a_matrix[i][j] = a_matrix[i][j] - copy2;
			}
			
			//b_matrix[i] = b_matrix[i] + copy;
		}
		
		int print_row {0};
		int print_column{0};				//create print variables
		for (int i{0}; length > i; ++i) {	//print matrix
			if (print_column % columns == 0 && print_column != 0) {
				std::cout << '\n';
				++print_row;
				print_column = 0;
			}
			std::cout <<  std::setw(10) << a_matrix[print_row][print_column];
			++print_column;
		}
		std::cout << '\n' << '\n';
		
		for (int i{0}; columns > i; ++i) {
			std::cout << std::setw(10) << b_matrix[i];
		}
		std::cout << '\n' << '\n';
		
		++track_row;
		++track_column;
		eval_row = track_row;
		track = track_row; 
		fail = 0;
		
	}


	return 0;
}

