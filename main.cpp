#include "autocompletetrie.h"
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>

int main()
{
	cout << "Enter path to a text file: ";
	char path[1024];
	cin >> path;
	AutocompleteTrie autocomplete(path);

	string command;
	wstring sentence;

	do
	{
		cout << "Enter Insert || Suggest || Change || Check || Quit : ";
		cin >> command;
		if (command == "Insert")
		{
			wcin.clear();
			wcin.ignore(5,'\n');
			cout << "Insert a new word/sentence: ";
			
			getline(std::wcin, sentence);
			autocomplete.Insert(sentence);
		}
		else if (command == "Suggest")
		{
			wcin.clear();
			wcin.ignore(5, '\n');
			cout << "Enter a prefix to suggest from : ";

			getline(std::wcin, sentence);
			autocomplete.Suggest(sentence);
		}
		else if (command == "Change")
		{
			cout << "Changing Max Suggestions from " << autocomplete.getMaxSuggestions() << " to: ";
			size_t newMaxSuggestions;
			cin >> newMaxSuggestions;
			autocomplete.setMaxSuggestions(newMaxSuggestions);
		}
		else if (command == "Check")
		{
			cout << "Current Max Suggestions = " << autocomplete.getMaxSuggestions() << endl;
		}
		else if (command == "Quit")
		{
			cout << "Exitting Auto Complete." << endl;
			break;
		}
		else
		{
			cout << "Wrong command." << endl;
		}
	} while (true);

	return 0;
}