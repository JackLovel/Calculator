#include "mainwindow.h"

#include <QtMath>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    sumInMemory = 0.0;
    waitingForOperand = true;
    factorSoFar = 0.0;
    sumSoFar = 0.0;

    for (int i = 0; i < NumDigitButtons; ++i) {
        numButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }

    QFont font;
    font.setFamily("Consolas");//字体
    font.setPointSize(20);    // 字体大小

    lineEdit = new QLineEdit("0");
    lineEdit->setAlignment(Qt::AlignRight);
    lineEdit->setFont(font);
    lineEdit->setReadOnly(true);

    clearButton = createButton(tr("clear"), SLOT(clear()));
    backgroundButton = createButton(tr("backspace"), SLOT(backspaceSlot()));
    divButton = createButton(tr("\303\267"), SLOT(multSlot()));
    minusButton = createButton(tr("-"), SLOT(addSlot()));
    plusButton = createButton(tr("+"), SLOT(addSlot()));
    equalButton = createButton(tr("="), SLOT(equalSlot()));

    pointButton = createButton(tr("."), SLOT(pointSlot()));
    signButton = createButton(tr("-/+"), SLOT(changeSignSlot()));
    multButton = createButton(tr("*"), SLOT(multSlot()));

    QGridLayout *m_layout = new QGridLayout();
    QWidget *m_widget = new QWidget();

    m_layout->addWidget(lineEdit, 0, 0, 1, 4);
    m_layout->addWidget(clearButton, 1, 0);
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
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (lineEdit->text() == "0" && digitValue == 0.0)
        return;

    if (waitingForOperand) {
        lineEdit->clear();
        waitingForOperand = false;
    }

    lineEdit->setText(lineEdit->text() + QString::number(digitValue));
}

void MainWindow::clear()
{
//    if (waitingForOperand)
//        return;

    lineEdit->setText("0");
    waitingForOperand = true;
}

Button *MainWindow::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void MainWindow::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    lineEdit->setText("0");
    waitingForOperand = true;

}
void MainWindow::abortOperation()
{
    clearAll();
    lineEdit->setText(tr("###"));
}

void MainWindow::addSlot()
{
    Button *clickButton = qobject_cast<Button *>(sender());
    QString clickOperator = clickButton->text();
    double operand = lineEdit->text().toDouble();
//    qDebug() << "operand" << operand;

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        lineEdit->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        lineEdit->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }

    pendingAdditiveOperator = clickOperator;
    waitingForOperand = true;
}

void MainWindow::multSlot()
{
    Button *clickButton = qobject_cast<Button *>(sender());
    QString clickOperator = clickButton->text();
    double operand = lineEdit->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }

        lineEdit->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickOperator;
    waitingForOperand = true;
}

bool MainWindow::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
//        qDebug() << sumSoFar << rightOperand << pendingOperator;
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("*")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0) {
            return false;
        }

        factorSoFar /= rightOperand;
    }

    return true;
}

void MainWindow::equalSlot()
{
    double operand = lineEdit->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }

        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }

        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    lineEdit->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}

void MainWindow::changeSignSlot()
{
    QString text = lineEdit->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }

    lineEdit->setText(text);
}

void MainWindow::pointSlot()
{
    if (waitingForOperand) {
        lineEdit->setText("0");
    }

    if (!lineEdit->text().contains('.')) {
        lineEdit->setText(lineEdit->text() + tr("."));
    }

    waitingForOperand = false;
}

void MainWindow::backspaceSlot()
{
    if (waitingForOperand)
    {
        return;
    }

    QString text = lineEdit->text();
    text.chop(1);

    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }

    lineEdit->setText(text);
}
