#include "autocompletetrie.h"

AutocompleteTrie::AutocompleteTrie(const char * path)
{
	root = new TrieNode();
	maxSuggestions = 10;
	size_t count = 0;

	wifstream inputFile(path);
	wchar_t buffer[2048];
	while (!inputFile.eof())
	{
		inputFile.getline(buffer, 2048);
		Insert(buffer);
		count++;
	}
	cout << count;
	inputFile.clear();
	inputFile.close();
}

AutocompleteTrie::AutocompleteTrie()
{
	root = new TrieNode();
	maxSuggestions = 10;
}

void AutocompleteTrie::Insert(const wstring& str)
{
	TrieNode * tmp = root;
	size_t wordLen = str.length();
	for (size_t i = 0; i < wordLen; i++)
	{
		size_t location = 0;
		if (!tmp->letterExists(str[i], location))
		{
			tmp->letters.push_back(make_pair(str[i], new TrieNode()));
		}
		tmp = tmp->letters[location].second;
	}
	tmp->endOfWord = true;
}

void AutocompleteTrie::Suggest(const std::wstring & str)
{
	vector<wstring> suggestions;
	size_t wstringLen = str.length();

	TrieNode * tmp = root;
	for (size_t i = 0; i < wstringLen; i++)
	{
		size_t location = 0;
		if (!tmp->letterExists(str[i], location))
		{
			cout << "There is no such word in the dictionary." << endl;
			return;
		}
		tmp = tmp->letters[location].second;
	}
	wstring tmpString = str;
	size_t counter = 0;
	addSuggestions(tmpString, suggestions, tmp, counter);
	for (auto it=suggestions.begin();it!=suggestions.end();it++)
	{
		wcout << *it << endl;
	}

	suggestions.clear();
}

void AutocompleteTrie::addSuggestions(std::wstring & str, vector<wstring>& suggestions, TrieNode * node, size_t & counter)
{
	if (node->endOfWord)
	{
		suggestions.push_back(str);
		counter++;
	}

	for (auto it = node->letters.begin(); it != node->letters.end(); it++)
	{
		if (it->second)
		{
			if (maxSuggestions <= counter)
			{
				return;
			}
			str.push_back(it->first);
			addSuggestions(str, suggestions, it->second, counter);
			str.pop_back();
		}
	}
}

bool TrieNode::letterExists(const wchar_t letter, size_t &location) const
{
	size_t sizeOfLetters = letters.size();
	for (size_t i = 0; i < sizeOfLetters; i++)
	{
		if (letter == letters[i].first)
		{
			location = i;
			return true;
		}
	}
	location = sizeOfLetters;
	return false;
}
