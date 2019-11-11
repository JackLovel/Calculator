#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QWidget>

class Button : public QPushButton
{
public:
    Button(const QString &text, QWidget *parent = nullptr);
    ~Button();
};

#endif // BUTTON_H
