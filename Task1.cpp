#include <iostream>
#include <cstdlib> 
#include <ctime> 
using namespace std;   

int main() {

    srand(static_cast<unsigned int>(time(0)));

    int maxAttempts;
    int randomNumber = rand() % 100 + 1;
    int guess = 0;
    string difficulty;

    
    cout << "Choose difficulty level - easy, medium, hard: ";
    cin >> difficulty;

    if (difficulty == "easy") {
        maxAttempts = 10;
    } else if (difficulty == "medium") {
        maxAttempts = 7;
    } else if (difficulty == "hard") {
        maxAttempts = 4;
    } else {
        cout << "Invalid difficulty level! Defaulting to easy." << endl;
        maxAttempts = 10;
    }

    cout << "You have " << maxAttempts << " attempts to guess the number (between 1 and 100)." << endl;

    
    for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
        cout << "Attempt " << attempt << ": ";
        cin >> guess;

        if (guess > randomNumber) {
            cout << "Too high! " << endl;
        } else if (guess < randomNumber) {
            cout << "Too low! " << endl;
        } else {
            cout << "Congratulations! You guessed the correct number: " << randomNumber << endl;
            return 0;
        }
    }

    
    cout << "Sorry, you've used all your attempts. The correct number was: " << randomNumber << endl;
    return 0;
}
