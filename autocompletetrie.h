#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct TrieNode
{
	bool endOfWord;
	vector<pair<wchar_t, TrieNode*>> letters;
	bool letterExists(const wchar_t letter, size_t& location) const;
	TrieNode()
	{
		endOfWord = false;
	}
	~TrieNode()
	{
		for (auto it = letters.begin(); it != letters.end(); it++)
		{
			delete it->second;
		}
	}
};

class AutocompleteTrie
{
public:
	AutocompleteTrie(const char * path);
	AutocompleteTrie();
	~AutocompleteTrie()
	{
		delete root;
	}
	void Insert(const wstring& str);
	void Suggest(const wstring& str);
	
	size_t getMaxSuggestions() const
	{
		return maxSuggestions;
	}
	
	void setMaxSuggestions(size_t number)
	{
		maxSuggestions = number;
	}

private:
	TrieNode * root;
	size_t maxSuggestions; 

	void addSuggestions(std::wstring & str, vector<wstring>& suggestions, TrieNode * node, size_t & counter);
};