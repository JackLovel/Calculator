#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    for (int i = 0; i < NumDigitButtons; ++i) {
        numButtons[i] = new QPushButton(QString::number(i));
        connect(numButtons[i], &QPushButton::clicked, this, &MainWindow::digitClicked);
    }

    QFont font;
    font.setFamily("Consolas");//字体
    font.setPointSize(20);    // 字体大小

    QLineEdit *lineEdit = new QLineEdit("0");
    lineEdit->setAlignment(Qt::AlignRight);
    lineEdit->setFont(font);
    lineEdit->setReadOnly(true);

    cleanButton = new QPushButton(tr("CE"));
    backgroundButton = new QPushButton(tr("background"));
    divButton = new QPushButton(tr("\303\267"));
    minusButton = new QPushButton(tr("-"));
    plusButton = new QPushButton(tr("+"));
    equalButton = new QPushButton(tr("="));
    pointButton = new QPushButton(tr("."));
    signButton = new QPushButton(tr("+/-"));
    QPushButton *multButton = new QPushButton("*");

    QGridLayout *m_layout = new QGridLayout();
    QWidget *m_widget = new QWidget();

    m_layout->addWidget(lineEdit, 0, 0, 1, 4);
    m_layout->addWidget(cleanButton, 1, 0);
    m_layout->addWidget(backgroundButton, 1, 1);
    m_layout->addWidget(divButton, 1, 2);
    m_layout->addWidget(signButton, 5, 0);
    m_layout->addWidget(numButtons[0], 5, 1);
    m_layout->addWidget(pointButton, 5, 2);
    m_layout->addWidget(equalButton, 5, 3);
    m_layout->addWidget(minusButton, 3, 3);
    m_layout->addWidget(plusButton, 4, 3);
    m_layout->addWidget(multButton, 2, 3);

    for (int i = 1; i < NumDigitButtons; i++) {
        int row = ((9 - i) / 3) + 2;
        int col = ((i - 1) % 3);
        m_layout->addWidget(numButtons[i], row, col);
    }

    m_widget->setLayout(m_layout);
    setCentralWidget(m_widget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::digitClicked()
{

}

