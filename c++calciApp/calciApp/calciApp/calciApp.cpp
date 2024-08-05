
#include "calciLibrary.h"
using namespace std;

// this is console app to show how my calculator will work
// declared some function that will take only intergers and only that characters that were mentions in calculator only


int getInteger(string numStr) {
    int number;
    while (true) {
        cout << numStr;
        cin >> number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }
    }
}
char getCharacter() {
    set<char> validChars = { '.','-','*','/', '+','A', 'B', 'C', 'D', 'E', 'F','G','H','I','J','K' };
    char input;
    while (true) {
        cout << "OPERATION given above only: ";
        cin >> input;
        if (validChars.find(input) != validChars.end()) {
            return input;
        }
        else {
            cout << "Invalid input. Please enter only above mentioned OPERATION: " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
int main()
{
    //defining the class objects
    calci trail;
    int number1 = 0, number2 = 0;
    char operationChar = '\n';
    trail.showCalci();
    while (operationChar != '.') {
        cout << "Enter in captial only"<<endl;
        cout << "Enter the "; 
        char operationChar= getCharacter();
        if (operationChar == '.') { break; }
        cout << operationChar << endl;

        if (operationChar == '+' || operationChar == '-' || operationChar == '*' || operationChar == '/') {
            int number1= getInteger("Enter the number1: ");
            int number2 = getInteger("Enter the number2: ");
            trail.commonFunc(number1, number2, operationChar);

        }
        else if (operationChar == 'A') {
            int number1 = getInteger("Enter the number: ");
            trail.logFunc(number1, 10);
        }
        else if (operationChar == 'B') {
            int number1 = getInteger("Enter the number: ");
            trail.logFunc(number1, 2);
        }
        else if (operationChar == 'C') {
            int number1 = getInteger("Enter the number: ");
            trail.powFunc(number1, 2, 'p');
        }
        else if (operationChar == 'D') {
            int number1 = getInteger("Enter the number: ");
            int number2 = getInteger("Enter the power: ");
            trail.powFunc(number1, number2, 'p');
        }
        else if (operationChar == 'E') {
            int number1 = getInteger("Enter the number: ");
            trail.powFunc(number1,2, 'e');
        }
        else if (operationChar == 'F') {
            int number1 = getInteger("Enter the degree: ");
            trail.trinoFunc(number1, "sine");
        }
        else if (operationChar == 'G') {
            int number1 = getInteger("Enter the degree: ");
            trail.trinoFunc(number1, "cos");
        }
        else if (operationChar == 'H') {
            int number1 = getInteger("Enter the degree: ");
            trail.trinoFunc(number1, "tan");
        }
        else if (operationChar == 'I') {
            int number1 = getInteger("Enter the total elements: ");
            vector<int>arr(number1);
            cout << "while entering the elements for every element press 'Enter' and enter each element" << endl;
            for (int i = 0; i < number1; ++i) {
                arr[i]=getInteger("");
            }
            trail.meanFunc(arr, "mean");
     
        }
        else if (operationChar == 'J') {
            int number1 = getInteger("Enter the total elements: ");
            vector<int>arr(number1);
            cout << "while entering the elements for every element press 'Enter' and each element" << endl;
            for (int i = 0; i < number1; ++i) {
                arr[i] = getInteger("");
            }
            trail.meanFunc(arr, "median");
        }
        else if (operationChar == 'K') {
            int number1 = getInteger("Enter the total elements: ");
            vector<int>arr(number1);
            cout << "while entering the elements for every element press enter and each element" << endl;
            for (int i = 0; i < number1; ++i) {
                arr[i] = getInteger("");
            }
            trail.stdDeviation(arr);
        }
    }
     
    return 0;
}

