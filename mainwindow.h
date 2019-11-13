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
#include <QObject>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool calculate(double rightOperand, const QString &pendingOperator);
    Button *createButton(const QString &text, const char *member);
    void abortOperation();
    void clearAll();

private slots:
    void digitClicked();
    void clear();
    void addSlot();
    void equalSlot();
    void changeSignSlot();
    void pointSlot();
    void backspaceSlot();
    void multSlot();

private:
    Button *clearButton;
    double sumInMemory;
    double sumSoFar;
    double factorSoFar;
    bool waitingForOperand;
    QString pendingMultiplicativeOperator;
    QString pendingAdditiveOperator;
    QGridLayout *m_layout;
    enum { NumDigitButtons = 10 };
    Button *numButtons[NumDigitButtons];

    Button *backgroundButton;
    Button *divButton;
    Button *minusButton;
    Button *plusButton;
    Button *equalButton;
    Button *pointButton;
    Button *signButton;
    Button *multButton;

    QLineEdit *lineEdit;
};
#endif // MAINWINDOW_H
