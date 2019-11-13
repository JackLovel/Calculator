#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QObject>

class Button : public QPushButton
{
    Q_OBJECT

public:
    Button(const QString &text, QWidget *parent = nullptr);
};

#endif // BUTTON_H
