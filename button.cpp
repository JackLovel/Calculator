#include "button.h"

Button::Button(const QString &text, QWidget *parent)
    : QPushButton(parent)
{
    QFont font;
    font.setFamily("Consolas");//字体
    font.setPointSize(12);    // 字体大小
    setFont(font);

    setText(text);
    resize(40, 40);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

Button::~Button()
{

}
