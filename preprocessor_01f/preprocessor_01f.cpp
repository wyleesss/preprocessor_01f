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
	cout << "Ќатисн≥ть 1 дл€ зам≥ни цифр проб≥лами\n"
		    "Ќатисн≥ть 2 дл€ зам≥ни розд≥лових знак≥в проб≥лами\n"
		    "Ќатисн≥ть 3 дл€ зам≥ни англ≥йських букв проб≥лами\n"
		    "Ќатисн≥ть 4 дл€ зам≥ни украњнських букв проб≥лами\n"
		    "-> ";
	cin >> input_choice_variable;
}

void process_menu_input(string& character_list)
{
	string text = nullstr;
	char   input_character = nullchar;
	
#ifdef _WIN32

	system("CLS");
	cout << "ƒл€ зак≥нченн€ введенн€ даних натисн≥ть клав≥шу esc\n";
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
	cout << endl << "¬и ввели текст:" << endl << text << endl;
	system("PAUSE");
	system("CLS");

#elif __linux

	struct termios Old, New;

	system("clear");
	cout << "ƒл€ зак≥нченн€ введенн€ даних натисн≥ть клав≥шу esc\n";

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

	cout << endl << "¬и ввели текст:" << endl << text << endl;

#endif
}

int main()
{
#ifdef _WIN32
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif

	string numbers = "0123456789",
		   symbols = "`~!@#$%^&*()_+}{|\":<>?/.,\\';][=-є",
		   english_letters = "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM",
		   ukrainian_letters = "йцукенгшщзхждлорпавф€чсмитьбю…÷” ≈Ќ√Ўў«’∆ƒЋќ–ѕј¬‘я„—ћ»“№Ѕёі•≤≥™Їѓњ";

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