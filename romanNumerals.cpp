#include <string>
#include <vector>
#include <map>
#include <iostream>

/*
 * Class: RomanNumeral
 * ----------------------
 * This class contains functions to find the values of roman numerals and 
 * convert them to their decimal value
 */
class RomanNumeral {
  // Map of roman numerals and their corresponding values
  std::map<char, int> rnm;
  
  /*
   * Method: findValue
   * --------------------
   * This method takes a reference to a key and returns the value stored at
   * the key if there is one, and 0 if there isn't
   */
  int findValue(const char & key);

public:

  /*
   * Constructor
   * -------------------
   * Initializes a RomanNumeral object, setting up the map with the roman 
   * numeral keys and decimal values
   */
  RomanNumeral();

  /*
   * Deconstructor
   * --------------
   * Empty
   */
  ~RomanNumeral(){};

  /*
   * Method: get
   * ----------------
   * This method takes a reference to a key and uses findValue to return the 
   * value at the given key
   */
  int get(const char & key);

  /*
   * Method: romanToDecimal
   * ---------------------------
   * This method takes a string representing a roman numeral and converts it
   * to its decimal value.
   */
  int romanToDecimal(const std::string & str);
};

int RomanNumeral::findValue(const char & key) {
  if (rnm.find(key) != rnm.end()) {  //key is in the map
    return this->rnm[key];
  }
  else {                             //key is not in the map
    return 0;
  }
}

RomanNumeral::RomanNumeral() {
  this->rnm = {
    {'I', 1},
    {'V', 5},
    {'X', 10},
    {'L', 50},
    {'C', 100},
    {'D', 500},
    {'M', 1000}
  };
}

int RomanNumeral::get(const char & key) {
  int value = findValue(key);
  return value;
}

int RomanNumeral::romanToDecimal(const std::string & str) {
  int decimalValue = 0;  //total value
  for (int i = str.length()-1; i >= 0; i--) {
    if (i == str.length()-1) {
      decimalValue += get(str[i]);  //add first value read to total
    }
    else {
      if (get(str[i]) == 0) {
	std::cout<<"Invalid input"<<std::endl;  //char in string not a roman numeral
	return 0;
      }
      else if (get(str[i]) < get(str[i+1])) {    //if the current letter value is less than the one after it
	decimalValue -= get(str[i]);             //subtract current letter value from total
      }
      else {
	decimalValue += get(str[i]);            //add current letter value to total
      }
    }
  }
  return decimalValue;
}

int main () {
  RomanNumeral rn;
  int decimal = rn.romanToDecimal("MCMLXIX");
  std::cout<<"MCMLXIX to decimal = "<<decimal<<std::endl;
  int decimal2 = rn.romanToDecimal("MDXLVI");
  std::cout<<"MDXLVI to decimal = "<<decimal2<<std::endl;
  int decimal3 = rn.romanToDecimal("MMCCCXLIX");
  std::cout<<"MMCCCXLIX to decimal = "<<decimal3<<std::endl;
}
