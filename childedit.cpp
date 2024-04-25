#include "childedit.h"
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include <QKeyEvent>
#include <QDebug>
#include "prototypes.h"

extern Ui::MainWindow* uiCopy;
extern MainWindow* thisCopy;

extern struct GameValues
{
    QString randomString;
    int currentLength;
    QString enteredString;
    int enteredLength;
} gameValues;

childEdit::childEdit(QWidget* parent)
    :QLineEdit(parent)
{ }

void showValues()
{
    uiCopy->label->setText(gameValues.randomString);
    uiCopy->spinBox->setDisabled(false);
}

void hideValues()
{
    uiCopy->label->setText("");
    uiCopy->spinBox->setDisabled(true);
}

void childEdit::keyPressEvent(QKeyEvent *event)
{
    //Pass All Key Event back to Parent to Handle (So Characters become Visible in the field)
    QLineEdit::keyPressEvent(event);

    //Store Entered Text and Length, this only works if we've passed the character on to the parent
    gameValues.enteredString = uiCopy->lineEdit->text();
    gameValues.enteredLength = uiCopy->lineEdit->text().length();

    if (gameValues.enteredLength == 0) showValues();
    else hideValues();

    //Up and Down Arrows change the length of the strings, only if Spinbox Enabled
    if(event->key() == Qt::Key_Up)
    {
        if(uiCopy->spinBox->isEnabled())
        uiCopy->spinBox->setValue(uiCopy->spinBox->value()+1);
        return;
    }

    //Up and Down Arrows change the length of the strings, Only if Spinbox Enabled
    if(event->key() == Qt::Key_Down)
    {
        if(uiCopy->spinBox->isEnabled())
        uiCopy->spinBox->setValue(uiCopy->spinBox->value()-1);
        return;
    }

    //Process Enter-Key, is String is being Submitted
    if(event->key() == Qt::Key_Return)
    {
        //Clear Line Edit Field
        //uiCopy->lineEdit->clear();

        //Show the Label Value
        showValues();

        //If String Comparison Fails
        if ((gameValues.currentLength != gameValues.enteredLength)
            || (gameValues.randomString != gameValues.enteredString))
        {
            //Indicate Wrong answer by changing the colour of the label
            flashLabelColour("Red");
            return;
        }
        else
        flashLabelColour("Green");

        //If Strings match, re-initialise()
        //initialise();
    }
}

