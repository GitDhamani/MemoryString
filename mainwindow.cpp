#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "prototypes.h"

Ui::MainWindow* uiCopy;
MainWindow* thisCopy;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    uiCopy = ui;
    thisCopy = this;

    //Lock in Geometry
    setFixedSize(445,89);

    //Initialise Label with Random Char
    initialise();

    //Connect Statements for the Spinbox and Line Edit
    connectStatements();

    //Show a Welcome message after the GUI Loads
    aboutBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

