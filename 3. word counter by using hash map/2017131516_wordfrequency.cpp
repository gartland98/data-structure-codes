#include "wordfrequency.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

/** 
  * Assignment 3 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2021. 5. 9
  *
  */

WordFrequency::WordFrequency()
{
	// ToDo
	map = new WordFreqMap();
}

WordFrequency::~WordFrequency()
{
	// ToDo
	map->~WordFreqMap();
}

void WordFrequency::ReadText(const char* filename)
{
	// ToDo
	std::ifstream file(filename);
	std::string buffer;
	while(file.peek() != EOF) {
		getline(file, buffer);
		std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
		for (int i = 0; i < buffer.size(); ++i) {
			if(!std::isalpha(buffer[i]) && !std::isspace(buffer[i])) {
				buffer[i] = ' ';
			}
		}
		std::istringstream iss(buffer);
		do {
			std::string sub;
			iss >> sub;
			if(!sub.empty()) {
				IncreaseFrequency(sub);
			}
		} while(iss);
	}
}

int WordFrequency::GetFrequency(const std::string word)
{
	// ToDo
	WordFreqElem *findResult = map->find(word);
	if(findResult == NULL) {
		return 0;
	}
	return findResult->val;
}

void WordFrequency::IncreaseFrequency(const std::string word)
{
	// ToDo
	WordFreqElem *findResult = map->find(word);
	if(findResult == NULL) {
		map->insert(word, 1);
	} else {
		map->insert(word, findResult->val + 1);
	}
}
