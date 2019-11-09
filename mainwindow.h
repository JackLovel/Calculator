#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digitClicked();

private:
    QGridLayout *m_layout;
    enum { NumDigitButtons = 10 };
    QPushButton *numButtons[NumDigitButtons];

    QPushButton *cleanButton;
    QPushButton *backgroundButton;
    QPushButton *divButton;
    QPushButton *minusButton;
    QPushButton *plusButton;
    QPushButton *equalButton;
    QPushButton *pointButton;
    QPushButton *signButton;
};
#endif // MAINWINDOW_H
