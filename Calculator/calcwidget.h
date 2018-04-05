#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QStack>


class CalcWidget : public QWidget
{
    Q_OBJECT
private:
    QLCDNumber *display;
    QStack<QString> opStack;
    QString curOperand = "";

public:
    CalcWidget(QWidget *parent = 0);
    ~CalcWidget();
    QPushButton* createButton(QString text);
    void calculate();
public slots:
    void buttonClicked();
};

#endif // CALCWIDGET_H
