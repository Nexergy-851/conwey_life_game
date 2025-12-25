#include<bits/stdc++.h>
#include<Windows.h>
using namespace std;
int state_check(int x, int y);
int cell_state(int current, int neighbors);
void initialize_random_cell();
void print_cell();
void change_pattern(string x);
void run();
void step_generation();
void gilder_gun();
int a[51][51];
string pattern = "nothing";
bool paused = false;
int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	cout << "Enter initial pattern (glider, small_exploder, lightweight_spaceship, random, nothing, custom，Gosper_Glider_Gun, fifteen):" << endl;
	cin >> pattern;
	change_pattern(pattern);
	print_cell();
	while (true)
	{
		run();
		if (GetAsyncKeyState('Q') & 0x8000)
		{
			break; // 按 Q 退出
		}
	}
}
int state_check(int x, int y)
{
	int count = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
			{
				continue;
			}
			if (x + i >= 1 && x + i <= 50 && y + j >= 1 && y + j <= 50)
			{
				if (a[x + i][y + j] == 1)
				{
					count++;
				}
			}
		}
	}
	return count;
}
int cell_state(int current, int neighbors)
{
	if (current == 1)
	{
		return (neighbors == 2 || neighbors == 3) ? 1 : 0;
	}
	else
	{
		return (neighbors == 3) ? 1 : 0;
	}
}
void initialize_random_cell()
{
	for (int i = 1; i <= 50; i++)
	{

		for (int j = 1; j <= 50; j++)
		{
            a[i][j] = rand() % 2;
		}
			
	}
		
}
void print_cell()
{
	system("cls");
	for (int i = 1; i <= 50; i++)
	{
		for (int j = 1; j <= 50; j++)
		{
			cout << (a[i][j] ? "■ " : "□ ");
		}
		cout << endl;
	}
}
void change_pattern(string x)
{
	pattern = x;
	memset(a, 0, sizeof(a));
	if (x == "glider") //glider
	{
		a[2][3] = 1;
		a[3][4] = 1;
		a[4][2] = 1;
		a[4][3] = 1;
		a[4][4] = 1;
	}
	else if (x == "small_exploder") //small exploder
	{
		a[10][10] = 1;
		a[9][10] = 1;
		a[11][10] = 1;
		a[10][9] = 1;
		a[10][11] = 1;
		a[9][9] = 1;
		a[11][9] = 1;
		a[10][8] = 1;
	}
	else if (x == "random") //random
	{
		initialize_random_cell();
	}
	else if (x == "nothing") //clear
	{
		memset(a, 0, sizeof(a));
	}
	else if (x == "lightweight_spaceship") //lightweight spaceship
	{
		a[5][6] = 1;
		a[5][9] = 1;
		a[6][5] = 1;
		a[7][5] = 1;
		a[8][5] = 1;
		a[9][5] = 1;
		a[9][6] = 1;
		a[9][7] = 1;
		a[8][8] = 1;
		a[6][7] = 1;
	}
	else if (x == "custom")
	{
		cout << "Enter your custom pattern (cell_sum and row and column):" << endl;
		int r, c, sum;
		cin >> sum;
		while (sum <= 0 || sum > 2500)
		{
			cout << "Error to cell_sum! Please enter again:" << endl;
			cin >> sum;
		}
		for(int i = 1; i <= sum; i++)
		{
			cout << "Enter row " << ":" << endl;
			cin >> r;
			if(r < 1 || r > 50)
			{
				cout << "Error to row! Please enter again:" << endl;
				i--;
				continue;
			}
			cout << "Enter column " << ":" << endl;
			cin >> c;
			if(c < 1 || c > 50)
			{
				cout << "Error to column! Please enter again:" << endl;
				i--;
				continue;
			}
			a[r][c] = 1;
			cout << "Current pattern:" << endl;
			print_cell();
		}
	}
	else if (x == "Gosper_Glider_Gun")
	{
		gilder_gun();
	}
	else if (x == "fifteen")
	{
		a[25][20] = 1;
		a[25][21] = 1;
		a[26][22] = 1;
		a[24][22] = 1;
		a[25][23] = 1;
		a[25][24] = 1;
		a[25][25] = 1;
		a[25][26] = 1;
		a[26][27] = 1;
		a[24][27] = 1;
		a[25][28] = 1;
		a[25][29] = 1;
	}
}
void run()
{
	if (GetAsyncKeyState('P') & 0x8000)
	{
		paused = !paused;
		while (GetAsyncKeyState('P') & 0x8000) Sleep(10);
	}
	if (GetAsyncKeyState('R') & 0x8000)
	{
		change_pattern("random");
		print_cell();
		while (GetAsyncKeyState('R') & 0x8000) Sleep(10);
		return;
	}
	if (!paused)
	{
		step_generation();
	}
	print_cell();
}
void step_generation()
{
	int b[51][51];
	memset(b, 0, sizeof(b));
	for (int i = 1; i <= 50; i++)
	{
		for (int j = 1; j <= 50; j++)
		{
			int sum = state_check(i, j);
			b[i][j] = cell_state(a[i][j], sum);
		}
	}
	for (int i = 1; i <= 50; i++)
	{
		for (int j = 1; j <= 50; j++)
		{
			a[i][j] = b[i][j];
		}
	}
}
void gilder_gun()
{
	a[5][1] = 1;
	a[5][2] = 1;
	a[6][1] = 1;
	a[6][2] = 1;
	a[5][11] = 1;
	a[6][11] = 1;
	a[7][11] = 1;
	a[4][12] = 1;
	a[8][12] = 1;
	a[3][13] = 1;
	a[9][13] = 1;
	a[3][14] = 1;
	a[9][14] = 1;
	a[6][15] = 1;
	a[4][16] = 1;
	a[8][16] = 1;
	a[5][17] = 1;
	a[6][17] = 1;
	a[7][17] = 1;
	a[6][18] = 1;
	a[3][21] = 1;
	a[4][21] = 1;
	a[5][21] = 1;
	a[3][22] = 1;
	a[4][22] = 1;
	a[5][22] = 1;
	a[2][23] = 1;
	a[6][23] = 1;
	a[1][25] = 1;
	a[2][25] = 1;
	a[6][25] = 1;
	a[7][25] = 1;
	a[3][35] = 1;
	a[4][35] = 1;
	a[3][36] = 1;
	a[4][36] = 1;
}