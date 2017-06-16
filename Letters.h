#pragma once
#include <string.h>
#include <iostream>

class Letters {
private:
	char m_letter;
	int m_count;
	float m_interval;
	float m_lowerBound;
	float m_upperBound;
	
public:
	Letters(int count, char letter, std::string word);

	char getLetter();
	int getCount();
	float getInterval();
	float getLowerBound();
	float getUpperBound();

	void setLowerBound(float lowerBound);
	void setUpperBound(float upperBound);
};