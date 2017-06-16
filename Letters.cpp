#include "Letters.h"

Letters::Letters(int count, char letter, std::string word) {
	//Set basic infomation
	m_count = count;
	m_letter = letter;
	//interval between two bounds
	m_interval = (float)m_count / ((float)word.length()+1);// +1 for eof symbol

	//Set bounds
	m_lowerBound = 0;
	m_upperBound = m_interval;

}

int Letters::getCount() {
	return m_count;
}

char Letters::getLetter() {
	return m_letter;
}

float Letters::getInterval() {
	return m_interval;
}

float Letters::getLowerBound(){
	return m_lowerBound;
}

float Letters::getUpperBound(){
	return m_upperBound;
}

void Letters::setLowerBound(float lowerBound){
	m_lowerBound = lowerBound;
}

void Letters::setUpperBound(float upperBound){
	m_upperBound = upperBound;
}