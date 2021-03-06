#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;
#include <fstream>
#include <string>
extern int const SIZE = 9;
extern char const UNKNOWN = '0';
extern char const xuehao = '7';  // ID: 1120161751
string const NOSUCHFILE = "No such file: ";
string const OUTFILE = "sudoku.txt";
int const SQR = int(sqrt(SIZE));
string const USAGE = "USAGE: sudoku.exe -c N(1 <= N <= 100,0000)\n       sudoku.exe -s absolute_path_of_puzzlefile";
class sudo
{

public:
	sudo(int n);
	int sudoge(int pos, long& count, bool solve);  // solve = true <==> solve sudoku puzzle
	int sudoso(char* path);
private:
	char grid[SIZE][SIZE];
	int n;
	std::ofstream output;
	char buf[163];
	bool IsValid(int pos, bool solve);
	void PrintSudo();
};

void PrintUsage()

{

	cout << USAGE << endl;

}

int main(int argc, char* argv[])

{
	if (argc == 3)

	{

		// 输入-c
		if (argv[1][0] == '-' && argv[1][1] == 'c')

		{

			long n = 0;
			for (unsigned i = 0; i < string(argv[2]).length(); i++)

			{

				if (argv[2][i] < '0' || argv[2][i] > '9')

				{

					PrintUsage();

					return 0;

				}

				n = n * 10 + argv[2][i] - '0';

			}

			//错误情况
			if (n < 1 || n > 1000000) {

				PrintUsage();
				return 0;

			}
			else
			{

				sudo su(n);
				long count = 0;
				su.sudoge(1, count, false);

			}

		}

		// 输入-s
		else if (argv[1][0] == '-' && argv[1][1] == 's')

		{

			sudo su(1);
			su.sudoso(argv[2]);

		}

		//错误情况
		else

		{

			PrintUsage();

		}

	}
	// //错误情况
	else

	{

		PrintUsage();

	}
	return 0;

}

sudo::sudo(int n)

{

	for (int i = 0; i < SIZE; i++)

	{

		for (int j = 0; j < SIZE; j++)

		{

			grid[i][j] = UNKNOWN;

		}

	}
	grid[0][0] = xuehao;
	this->n = n;
	output.open(OUTFILE);
	for (int i = 0; i < SIZE * SIZE; i++)

	{

		if ((i + 1) % 9 == 0)

		{

			buf[2 * i + 1] = '\n';
			continue;

		}

		buf[2 * i + 1] = ' ';

	}

	buf[162] = '\n';

}

int sudo::sudoge(int pos, long& count, bool solve)

{

	if (pos == SIZE * SIZE)

	{

		PrintSudo();

		count++;

		if (count == n)

		{

			return 1;

		}

	}

	else

	{

		int x = pos / SIZE;
		int y = pos % SIZE;
		if (grid[x][y] == UNKNOWN)

		{

			int base = x / 3 * 3;

			for (int i = 0; i < SIZE; i++)         // try to fill the pos from 1-9

			{

				grid[x][y] = (i + base) % SIZE + 1 + '0';

				if (IsValid(pos, solve))               // if the number is valid

				{

					if (sudoge(pos + 1, count, solve) == 1)       // try to fill next pos

					{

						return 1;

					}

				}
				grid[x][y] = UNKNOWN;

			}

		}

		else

		{

			if (sudoge(pos + 1, count, solve) == 1)

			{

				return 1;

			}

		}

	}

	return 0;

}

int sudo::sudoso(char* path)

{

	ifstream input;

	input.open(path);

	if (input)

	{

		int total = 0;
		string temp[SIZE];
		string str;
		int line = 0;
		bool exc = false;     

		while (total < 1000000 && getline(input, str))

		{

			temp[line] = str;

			line++;

			if (line == SIZE)

			{

				for (int i = 0; i < SIZE; i++)

				{

					for (int j = 0; j < SIZE; j++)

					{

						grid[i][j] = temp[i][2 * j];

						if (grid[i][j] < '0' || grid[i][j] > '9')

						{

							exc = true;

							break;

						}

					}

				}

				getline(input, str);

				line = 0;

				if (exc)

				{

					exc = false;

					continue;

				}

				total++;


				long count = 0;

				sudoge(0, count, true);

			}

		}


	}

	else

	{

		cout << NOSUCHFILE << string(path) << endl;

		return 0;

	}

	return 1;

}



bool sudo::IsValid(int pos, bool solve)

{

	int x = pos / SIZE;
	int y = pos % SIZE;
	int z = x / SQR * SQR + y / SQR;
	int leftTop = z / SQR * SIZE * SQR + (z % SQR) * SQR;
	int rightDown = leftTop + (2 * SIZE + SQR - 1);
	int bound = solve ? SIZE : y;

	for (int i = 0; i < bound; i++)

	{

		if (i == y)

		{

			continue;

		}

		if (grid[x][i] == grid[x][y])

		{

			return false;

		}

	}

	bound = solve ? SIZE : x;

	for (int i = 0; i < bound; i++)

	{

		if (i == x)

		{

			continue;

		}

		if (grid[i][y] == grid[x][y])

		{

			return false;

		}

	}

	int bound_x = leftTop / SIZE;
	int bound_y = leftTop % SIZE;
	if (bound_x % 3 != 0 || bound_y % 3 != 0 || bound_x > SIZE - 3 || bound_y > SIZE - 3)

	{

		cout << "error" << endl;

		exit(0);

	}

	for (int i = bound_x; i < (bound_x + 3); i++)

	{

		for (int j = bound_y; j < (bound_y + 3); j++)

		{

			if (i == x && j == y)

			{

				if (solve)

				{

					continue;

				}

				else

				{

					return true;

				}

			}

			if (grid[i][j] == grid[x][y])

			{

				return false;

			}

		}

	}

	return true;

}

void sudo::PrintSudo()

{

	for (int i = 0; i < SIZE; i++)

	{

		for (int j = 0; j < SIZE; j++)

		{

			buf[18 * i + 2 * j] = grid[i][j];

		}

	}

	output << buf;

}
