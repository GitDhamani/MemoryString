#include <random>
#include <QString>
#include <QMessageBox>
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include <cstdlib>
#include <ctime>
#include <QTimer>
#include <QThread>
#include "prototypes.h"

extern Ui::MainWindow* uiCopy;
extern MainWindow* thisCopy;

struct GameValues
{
    QString randomString;
    int currentLength;
    QString enteredString;
    int enteredLength;
} gameValues;

char getRandomChar() {
    // Define a character array containing the characters a-z, A-Z, and 0-9
    char charSet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    // Generate a random index within the range of the character array
    int randomIndex = std::rand() % (sizeof(charSet) - 1); // -1 to avoid the null terminator

    // Return the character at the random index
    return charSet[randomIndex];
}

void initialise()
{


    // Seed the random number generator using current time, just once.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //Grab Current Spin box value and store it in Game Struct, it's going to be 1 initially.
    gameValues.currentLength = uiCopy->spinBox->value();

    //Clear RandomString and EnteredString Values
    gameValues.randomString.clear();
    gameValues.enteredString.clear();

    //Generate a Random String of Random Characters to Start With and store in Game Struct
    for (int i = 0; i < gameValues.currentLength; i++)
    gameValues.randomString += getRandomChar();

    //Load String into QLabel
    uiCopy->label->setText(gameValues.randomString);

    //Make Sure Spinbox is enabled
    uiCopy->spinBox->setDisabled(false);

    //Clear Line Edit
    uiCopy->lineEdit->clear();
    uiCopy->lineEdit->setFocus();
}

void connectStatements()
{
    //Connect Statement for the Spinbox
    thisCopy->connect(uiCopy->spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
    [](int index){

        if (index > gameValues.currentLength)
        {
            //Add a new Random Character to the String
            gameValues.randomString += getRandomChar();
        }
        else
        {
            //Remove the end Random Character from the String
            gameValues.randomString = gameValues.randomString.left(gameValues.randomString.length()-1);
        }

        //Update the Current Length
        gameValues.currentLength = index;

        //Update the Label
        uiCopy->label->setText(gameValues.randomString);

    });
}

void aboutBox()
{
    QTimer::singleShot(500, NULL, [](){
        QMessageBox::information(0, "Welcome", "The Memory Game.\n\nCopy the Random Letters.\nYou can change the word length\nusing the number box or by\npressing UP and DOWN.");
            });
}

void flashLabelColour(std::string colour)
{
    if (colour == "Red")
    {
        //Change label to Red to indicate wrong answer
        uiCopy->label->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(255, 0, 0);");
    }

    if (colour == "Green")
    {
        uiCopy->label->setText("Correct.");
        uiCopy->lineEdit->clear();

        //Change label to Green to indicate wrong answer
        uiCopy->label->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(85, 170, 127);");
    }

    QTimer::singleShot(1000, NULL, [colour](){
        //Restore colour palette
        uiCopy->label->setText(gameValues.randomString);
        uiCopy->lineEdit->clear();
        uiCopy->label->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0);");
        if (colour == "Green") initialise();
            });
}
