#include "Letters.h"
#include "Range.h"
#include <sstream>
#include <vector>
#include <iomanip>
#include <math.h>

/*
Ben Arterton 14046916
Arithmetic Coding implementation
*/

/*
	getProb 
*/
double getProb(std::string input, std::vector<Letters> prob) {

	//Set up return variable
	double result = 1.0;
	//Calculation letter loop
	for (int i = 0; i < input.length(); i++) {
		//Calculation probability loop
		for (int l = 0; l < prob.size(); l++) {
			//Times probability values
			if (input[i] == prob[l].getLetter()) {
				result = result *  prob[l].getInterval();
			}
		}
	}
	//Return result
	return result;
}

/*
	getRange 
*/
Range encode(std::string input, std::vector<Letters> prob) {

	double a = 0.0f;
	double b = 1.0f;

	std::string inputEOF = input + '#';
	std::string past;
	std::vector <std::string> parts; 

	//For each letter in input
	for (int i = 0; i < inputEOF.length(); i++) {
		//Check for each letter in the probablilty
		for (int l = 0; l < prob.size(); l++) {
			//Check if the next letter is found
			if (inputEOF[i] == prob[l].getLetter()) {
				std::cout << past << prob[l].getLetter()  << " (VALUE FOUND: " << a << ")"<< std::endl;
				past += prob[l].getLetter();
				break;
			}
			else {
				a += getProb(past + prob[l].getLetter(), prob);
				
				std::cout << past << prob[l].getLetter() << std::endl;
			}
		}
	}
	//Do b calc
	b = a + getProb(inputEOF, prob);
	//Return the full range value
	return Range(a,b);
}
/*
	Decode the inputted string from the a value of the range
*/
std::string decode(double a, std::vector<Letters> prob) {

	std::string result;
	double aVal = 0;
	aVal = a;
	bool running = true;

	while (running) {

		for (int i = 0; i < prob.size(); i++) {
			//If a is greater than a letters lower bound and less than upper bound
			if (aVal >= prob[i].getLowerBound() && aVal < prob[i].getUpperBound()) {
				//Output the value of a for debugging
				std::cout << "Value: " << aVal << " Letter: " << prob[i].getLetter() << std::endl;
				//Calculate a new val of a
				aVal = (aVal - prob[i].getLowerBound()) / prob[i].getInterval();
				//add the letter to the decoded string
				result += prob[i].getLetter();

				//If at the eof symbol stop decoding
				if (prob[i].getLetter() == '#') {
					running = false;
				}
			}
		}
	}
	return result;
}

int main(){

	std::vector<Letters> lettersVector;

	std::string str;
	std::string exit;
	char ch;
	int count = 0;
	double upperBound = 1.0;
	double lowerBound = 0.0;

	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "ALGORITHMS AND ADVANCED DATA STRUCTURES COURSEWORK 2" << std::endl;
	std::cout << "Arithmetic Coding" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;

	bool running = true;
	bool stringCheck = true;

	
	while (stringCheck) {

		std::cout << "Enter 3 character string to encode" << std::endl;
		std::getline(std::cin, str);
		//Restrict to 3 character strings as implementation is inaccurate
		if (str.length() <= 3) {
			stringCheck = false;
		}
		else {
			stringCheck = true;
		}
	}



	//Go through ASCII values 32 - 122
	for (ch = (char)32; ch <= 122; ch++) {
		count = 0;
		//Accept specific ASCII values (space, uppercase, lowercase)
		if (ch == (char)32 || ch >= (char)65) {

			//Count character apperences
			for (int n = 0; n < str.length(); n++) {
				if (ch == str[n]) {
					count++;
				}
			}
			//Create object of known letters
			if (count > 0) {
				//Create object
				Letters l = Letters(count, ch, str);
				lettersVector.push_back(l);

			}
		}
	}
	//Adding EOF symbol #
	Letters l = Letters(1, '#', str);
	lettersVector.push_back(l);

	lettersVector[0].setLowerBound(0);
	lettersVector[0].setUpperBound(lettersVector[0].getInterval());

	for (int n = 1; n < lettersVector.size(); n++) {
		//Add calculate lower and upper bounds
		if (lettersVector.size() > 0) {
			//Set lower bound
			lettersVector[n].setLowerBound(lettersVector[n - 1].getUpperBound());
			//Set upper bound
			lettersVector[n].setUpperBound(lettersVector[n].getLowerBound() + lettersVector[n].getInterval());
		}
	}

	//Printing results
	for (int i = 0; i < lettersVector.size(); i++) {
		std::cout << lettersVector[i].getLetter() << " : " << lettersVector[i].getCount() << " Interval: ";
		std::cout << std::fixed << std::setprecision(3) << lettersVector[i].getInterval() << std::endl;
		std::cout << lettersVector[i].getLetter() << " Lower Bound : " << lettersVector[i].getLowerBound() << " Upper Bound : " << lettersVector[i].getUpperBound() << "\n" << std::endl;
	}
	//create a range object for the encoded value
	Range result = encode(str, lettersVector);

	//print A and B values
	std::cout << std::setprecision(16) << std::endl << "Encoded value: A: " << result.getA() << " B: " << result.getB() << std::endl;

	//Decode the a value
	std::cout << "Decoded value: " << decode(result.getA(), lettersVector) << std::endl << std::endl;

	system("PAUSE");
	
}


