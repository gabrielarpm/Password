/****************************
 * Program 3: Password Checker
 * Course: CS 141, Fall 2022
 * System: MacOS using Clion
 * Starter Code Author: Dr. Sara Riazi
 * Student Author: Gabriela Ramirez
 ***************************/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


const string rule_msg_1 = "The selected password must be at least eight characters long.";
const string rule_msg_2 = "The selected password must have at least one uppercase letter.";
const string rule_msg_3 = "The selected password must have at least one lowercase letter.";
const string rule_msg_4 = "The selected password must have at least one digit.";
const string rule_msg_5 = "The selected password must have at least one of special characters: [@,!,#,^,&,*,$]";
const string rule_msg_6 = "The selected password has been leaked.";
const string rule_msg_7 = "The selected password cannot contain a dictionary word.";


int binarySearch(vector<string>words, int low, int high, string password2){
    string temp = "";
    int mid = (high + low)/2;
    for(int i=0; i<words[mid].size(); i++){
        if(isalnum(words[mid].at(i))){
            temp += words[mid].at(i);
        }
    }
    /* We keep checking the condition while the high is greater than or equal to low, but eventually if we don't fin it,
    the high is going to be less than the low. So that is how we know it's not even in the file. Therefore, that is
    why we would return the -1.*/
    if(high >= low){
        if(temp==password2) {
            return mid;
        }
        else if (temp>password2){
            return binarySearch(words, low, mid-1, password2);
        }
        else{
            return binarySearch(words, mid+1, high, password2);
        }
    }
    return -1;
}
//Reading in the leaked password file
bool checksLeaked(string leaked_password_file, string password) {
    ifstream inFs;
    vector<string> leaked;
    inFs.open(leaked_password_file);
    if (inFs.is_open()){
        string tempData = "";
        while(getline(inFs, tempData)){
            leaked.push_back(tempData);
        }
        inFs.close();
    }
    //Updating password to exclude digits
    string password2 = "";
    for(int i=0; i<password.size(); i++){
        password[i] = tolower(password[i]);
        if(isalnum(password[i])){
            password2 += password[i];
        }
    }
    //Checks if password contains a dictionary word and if there is, it returns true, otherwise, false.
    int low = 0;
    int high = leaked.size() - 1;
    int result = binarySearch(leaked, low, high, password2);
    if(result != -1) {
        cout << rule_msg_6 << endl;
        cout << "Password rejected!" << endl;
        return true;}
    return false;
}
//Reading in English word file
bool checksEnglish (string english_word_file, string password){
    ifstream inFs;
    vector<string> english;
    inFs.open(english_word_file);
    if (inFs.is_open()){
    string tempData = "";
    while(getline(inFs, tempData)){
    english.push_back(tempData);
    }
    inFs.close();
    }
//Updating password to exclude special characters
    string password2 = "";
    for(int i=0; i<password.size(); i++){
    password[i] = tolower(password[i]);
    if(isalpha(password[i])){
    password2 += password[i];
    }
    }
//Checks if password has been leaked and if it is, it returns true, otherwise, false.
    int low = 0;
    int high = english.size() - 1;
    int result = binarySearch(english, low, high, password2);
    if(result != -1){
        cout << rule_msg_7 << endl;
    cout << "Password rejected!" << endl;
    return true;}
return false;
}

//This function checks rule messages 1-5 and takes in the password.
 bool checksMessages(string password){
 int uppercase = 0;
 int lowercase = 0;
 int findDigit = 0;
 int specialChar = 0;
 int length = 0;

//The code loops through the password to check if length is at least 8 characters long.
     if(password.length()<8) {
         length ++;
         cout << rule_msg_1 << endl;
     }

 /*The code loops through the password to check if there exists at least one uppercase letter, lowercase letter, digit, and
 one of special characters: [@,!,#,^,&,*,$].*/
    for(int i= 0; i<password.size(); i++){
    if(password[i] >= 65 && password[i] <= 90)
    uppercase++;
    if(password[i] >= 97 && password[i] <= 122)
    lowercase++;
    if(password[i] >= 48 && password[i] <= 57)
    findDigit++;
    if(password[i] == '@'|| password[i] =='!'|| password[i] =='#'|| password[i] =='^'||password[i] =='&'||password[i] =='*'||password[i] =='$')
    specialChar++;
   }

//If a rule message(s) is equal to 0, then its rule message(s) gets printed out.
  if(uppercase == 0)
      cout << rule_msg_2 << endl;
  if(lowercase == 0)
      cout << rule_msg_3 << endl;
  if(findDigit == 0)
      cout << rule_msg_4 << endl;
  if(specialChar == 0)
      cout << rule_msg_5 << endl;

  //Password is rejected if the password contains at least one uppercase letter, lowercase letter, digit, and one of special characters: [@,!,#,^,&,*,$]
  if(uppercase ==0 || lowercase ==0 || findDigit ==0 || specialChar ==0 || length != 0){
      cout << "Password rejected!" << endl;
      return false;
  }
  return true;

 }
/****
 * Runs the main part of the program
 ****/
void run(string leaked_password_file, string english_word_file)
//User enters a password.
{
    string password;
    cout << "Enter password: ";
    cin >> password;

//The functions below for messages 1-6get called in the main part of the program.
    if (checksMessages(password)) {
        if(!checksLeaked(leaked_password_file,password)){
          if(!checksEnglish (english_word_file,password)){
              cout << "Password accepted!" << endl;
          }
        }

    }


}


int main() {
    /** Change the address of the files appropriately based on your local machine.
     * This main function will be replaced during testing. Do not add any line of code to the main function
     **/
    string leaked_password_file = "alleged-gmail-passwords.txt"; //change this based on the location of the file on your machine
    string english_word_file = "words_5.txt"; //change this based on the location of the file on your machine
    run(leaked_password_file, english_word_file);
    return 0;
}

