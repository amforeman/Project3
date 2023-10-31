#define NDEBUG
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cassert>


/*
 * Class: PirateTranslation
 * ----------------------------------
 * This class contains variables and functions to translate the user's input
 * from English to Pirate.
 * The dictionary of pirate words is a constant vector defined in the 
 * initialization of the class.
 */
class PirateTranslation {

  /* Dictionary of possible pirate words. The index of each word corresponds to
   * the matching english translation. This is a const vector, as the dictionary
   * will not change
   */
  const std::vector<std::string> pirateWords {"ahoy", "arrr", "matey", "matey", "matey", "proud beauty", "foul blaggart", "th'", "me", "yer", "be", "be", "head", "galley", "fleabag inn", "doubloons", "buccaneer", "mate", "ye"};
  // Constant dictionary of English words that have a pirate translation
  const std::vector<std::string> englishWords {"hello", "excuse", "sir", "boy", "man", "madame", "officer", "the", "my", "your", "is", "are", "restroom", "restaurant", "hotel", "coins", "pirate", "friend", "you"};
  // String for raw input
  std::string input;
  // Vector to hold iterate through the user's input
  std::vector<std::string> englishInput;
  // String for translated output
  std::string pirateOutput;

  /*
   * Method: handleInput
   * ------------------------
   * This method handles the user's input, formatting it for translation
   */
  void handleInput();

  /*
   * Method: capitalize
   * ----------------------
   * This method capitalizes the first letter of the word given
   */
  std::string capitalize(const std::string str) const;

  /*
   * Method: punctuate
   * ----------------------
   * This method handles punctuation in the string, returning a pair of strings
   * representing the word and the following punctuation. If there is none, 
   * the function will return a space for the punctuation.
   */
  std::pair<std::string, std::string> punctuate(const std::string str) const;

  /*
   * Method: toPirate
   * ----------------------
   * This method creates the output string in pirate, ensuring that each word
   * is formatted like the input.
   */
  std::string toPirate();

  public:

  /*
   * Constructor
   * ---------------
   * Initializes a PirateTranslation object, setting the input and output
   * variable to empty vectors. No input is taken.
   */
  PirateTranslation();

  /*
   * Deconstructor
   * ---------------
   * Empty
   */
  ~PirateTranslation(){};

  /*
   * Method: translate
   * ---------------------
   * If called with no input, this method welcomes the user to the translator 
   * and prompts the user for input. The input is then handled in a private 
   * method.
   * If given a string, this method handles the string as input.
   */
  std::string translate(const std::string str);
  std::string translate();

  void assertions();
};

PirateTranslation::PirateTranslation() {
  this->englishInput = {};
  this->pirateOutput = {};
}

std::string PirateTranslation::translate(const std::string str){
  this->input = str;
  handleInput();
  std::string pirate = toPirate();
  return pirate;
}


std::string PirateTranslation::translate(){
  std::cout<<"What would you like me to translate?"<<std::endl;
  std::getline(std::cin, input);
  handleInput();
  std::string pirate = toPirate();
  return pirate;
} 

void PirateTranslation::handleInput() {
  //separating the input string by spaces
  std::string temp;
  std::vector<std::string> tempInput;
  std::stringstream ss(input);
  while (getline(ss, temp, ' ')) {
    tempInput.push_back(temp);
  }

  //separating the words from the punctuation and adding them separately to input vector
  for (int i = 0; i < tempInput.size(); i++) {
    std::pair<std::string, std::string> tempPair = punctuate(tempInput[i]);
    englishInput.push_back(tempPair.first);
    englishInput.push_back(tempPair.second);
  }
}

std::string PirateTranslation::capitalize(const std::string str) const{
  std::string capitalized = str;
  capitalized[0] = capitalized[0]-32;
  return capitalized;
}

std::pair<std::string, std::string> PirateTranslation::punctuate(const std::string str) const {
  std::string word = "";
  std::string punctuation = "";
  for (int i = 0; i < str.length(); i++) {
    char c = str[i];
    switch(c) {
      case '.':
      case ',':
      case '!':
      case '?':
      case ':':
      case ';': {
        punctuation += str[i];
      } break;
      default: {
        word += str[i];
      } break;
    }
  }
  std::pair<std::string, std::string> wordPunct;
  wordPunct.first = word;
  wordPunct.second = punctuation + " ";
  return wordPunct;
}

std::string PirateTranslation::toPirate() {
  for (int i = 0; i < englishInput.size(); i++) {
    std::string current = englishInput[i];
    std::vector<std::string> englishFormatted = {};
    std::vector<std::string> pirateFormatted = {};
    /*Check for capitalization, capitalize all possible words if yes.
     *This formatting ensures that the word being searched for and the
     *dictionary word will return as a match.
     */
    if (isupper(current[0])) {
      for (int j = 0; j < englishWords.size(); j++) {
	englishFormatted.push_back(capitalize(englishWords[j]));
	pirateFormatted.push_back(capitalize(pirateWords[j]));
      }
    }
    //Maintain lowercase format if no capitalization
    else {
      englishFormatted = englishWords;
      pirateFormatted = pirateWords;
    }
    for (int k = 0; k < englishFormatted.size(); k++) {
      if (current == englishFormatted[k]) {
	// special case for "excuse me" to "arrr"
	if (k == 1) {
	  if (englishInput[i+2] == "me") {  //matches "excuse me"
	    pirateOutput+=pirateFormatted[k];
	    i+=2;     //skip next word, "me", as they are equal to one pirate word
	    break;    //match found, stop loop
	  }
	  else {
	    continue; //does not match "excuse me", continues as normal
	  }
	}
	else {
	  pirateOutput+=pirateFormatted[k];
	  break;      //match found, stop loop
	}
      }
      else {
	if (k == englishFormatted.size()-1) {  //match not found in dictionary
	  pirateOutput+=current;               //add english word to output
	}
        continue;
      }
    }
  }
  return pirateOutput;
}

void PirateTranslation::assertions() {
  std::cout<<"Testing for capitalize function"<<std::endl;
  assert(capitalize("hello") == "Hello");
  assert(capitalize("proud beauty") == "Proud beauty");
  assert(capitalize("pirate") != "PIRATE");
  std::cout<<"Capitalize function passes"<<std::endl;

  std::cout<<"Testing for punctuate function"<<std::endl;
  std::pair<std::string, std::string> punc1 = punctuate("madame!");
  assert(punc1.first == "madame");
  assert(punc1.second == "! ");
  std::pair<std::string, std::string> punc2 = punctuate("restaurant");
  assert(punc2.first == "restaurant");
  assert(punc2.second == " ");
  std::pair<std::string, std::string> punc3 = punctuate("friend?");
  assert(punc3.first != "friends");
  assert(punc3.second != "!");
  std::cout<<"Punctuate function passes"<<std::endl;
}

int main() {
  
  std::cout<<"Welcome to the pirate translator! I translate sentences from English to Pirate."<<std::endl;
  PirateTranslation pt1;
  PirateTranslation pt2;
  PirateTranslation pt3;
  std::cout<<pt1.translate()<<std::endl;
  std::cout<<pt2.translate("Excuse me, boy, have you seen my fellow pirate in the hotel?")<<std::endl;

  //std::cout<<"Testing for translate function"<<std::endl;
  std::string test1 = pt1.translate("Excuse me, boy, have you seen my fellow pirate in the hotel?");
  assert(test1 == "Arrr, matey, have ye seen me fellow buccaneer in th' fleabag inn? ");
  std::string test2 = pt2.translate("Hello madame, my friend will pay you five coins if you tell us where the officer is!");
  assert(test2 == "Ahoy proud beauty, me mate will pay ye five doubloons if ye tell us where th' foul blaggart be! ");
  std::string test3 = pt3.translate("Where are your coins");
  assert(test3 != "Where be your coins?");
  //std::cout<<"Translate function passes"<<std::endl;
  
  //pt1.assertions();
}
