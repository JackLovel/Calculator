#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "button.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QQueue>
#include <QStack>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digitClicked();
    void cleanSlot();

private:
    QGridLayout *m_layout;
    enum { NumDigitButtons = 10 };
    Button *numButtons[NumDigitButtons];

    Button *cleanButton;
    Button *backgroundButton;
    Button *divButton;
    Button *minusButton;
    Button *plusButton;
    Button *equalButton;
    Button *pointButton;
    Button *signButton;
    QLineEdit *lineEdit;
};
#endif // MAINWINDOW_H
