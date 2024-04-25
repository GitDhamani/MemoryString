#ifndef CHILDEDIT_H
#define CHILDEDIT_H

//Subclassing the LineEdit class so I can access the KeyEvent Functions

#include <QLineEdit>
#include <QObject>

class childEdit : public QLineEdit
{
public:
    childEdit(QWidget* parent);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // CHILDEDIT_H
