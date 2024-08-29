#include <iostream>

using namespace std;

int main() {
    double number1, number2;
    char operation;

    // Input two numbers
    cout << "Enter first number: ";
    cin >> number1;
    cout << "Enter second number: ";
    cin >> number2;

    // Input operation
    cout << "Enter the operation (+, -, *, /): ";
    cin >> operation;

    // Calculation
    switch (operation) {
        case '+':
            cout << "Result: " << number1 + number2 << endl;
            break;
        case '-':
            cout << "Result: " << number1 - number2 << endl;
            break;
        case '*':
            cout << "Result: " << number1 * number2 << endl;
            break;
        case '/':
            if (number2 != 0) {
                cout << "Result: " << number1 / number2 << endl;
            } else {
                cout << "Invalid: Division by zero is not allowed." << endl;
            }
            break;
        default:
            cout << "Choose appropriate operation" << endl;
            break;
    }

    return 0;
}
