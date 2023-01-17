#include <iostream>
#ifdef _WIN32
	#include <windows.h>
	#include <conio.h>
#elif __linux
	#include <termios.h>
#endif

#define nullchar ' '
#define nullstr ""

using std::cout;
using std::cin;
using std::string;
using std::endl;

inline void main_menu_input(int& input_choice_variable)
{
	cout << "�������� 1 ��� ����� ���� ��������\n"
		    "�������� 2 ��� ����� ��������� ����� ��������\n"
		    "�������� 3 ��� ����� ���������� ���� ��������\n"
		    "�������� 4 ��� ����� ���������� ���� ��������\n"
		    "-> ";
	cin >> input_choice_variable;
}

void process_menu_input(string& character_list)
{
	string text = nullstr;
	char   input_character = nullchar;
	
#ifdef _WIN32

	system("CLS");
	cout << "��� ��������� �������� ����� �������� ������ esc\n";
	while ((input_character = _getch()) != 27)
	{
		if (input_character == 13)
			input_character = '\n';
		else
		{
			for (auto& i : character_list)
				if (input_character == i)
					input_character = nullchar;
		}
		text += input_character;
		cout << input_character;
	}
	cout << endl << "�� ����� �����:" << endl << text << endl;
	system("PAUSE");
	system("CLS");

#elif __linux

	struct termios Old, New;

	system("clear");
	cout << "��� ��������� �������� ����� �������� ������ esc\n";

	tcgetattr(0, &Old);
	New = Old;
	New.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &New);

	while ((input_character = getchar()) != 27)
	{
		for (auto& i : character_list)
			if (input_character == i)
				input_character = nullchar;

		text += input_character;
		cout << input_character;
	}

	tcsetattr(0, TCSANOW, &Old);

	cout << endl << "�� ����� �����:" << endl << text << endl;

#endif
}

int main()
{
#ifdef _WIN32
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif

	string numbers = "0123456789",
		   symbols = "`~!@#$%^&*()_+}{|\":<>?/.,\\';][=-�",
		   english_letters = "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM",
		   ukrainian_letters = "���������������������������������������������������������޴�������";

	int    choice = NULL;
	bool   menu_run = true;

	while (menu_run)
	{
		main_menu_input(choice);
		switch (choice)
		{
		case 1: process_menu_input(numbers);
		break;

		case 2: process_menu_input(symbols);
		break;

		case 3: process_menu_input(english_letters);
		break;

		case 4: process_menu_input(ukrainian_letters);
		break;

		default: menu_run = false;
		break;
		}
	}
}