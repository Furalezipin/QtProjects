#include "calcwidget.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QtDebug>

CalcWidget::CalcWidget(QWidget *parent)
    : QWidget(parent)
{
    display = new QLCDNumber(10, this);
    display->display(0);
    display->setSegmentStyle(QLCDNumber::Flat);
    display->setMinimumSize(300, 40);

    QString mass_button[4][4] = {{"7", "8", "9", "+"},
                                {"4", "5", "6", "-"},
                                {"1", "2", "3", "X"},
                                {".", "0", "=", "/"}};

    QGridLayout *layout = new QGridLayout;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            layout->addWidget(createButton(mass_button[i][j]), i+1, j);
        }
    }

    QHBoxLayout *hl = new QHBoxLayout();
    QPushButton *btn_me = createButton("ME");
    hl->addStretch(1);
    hl->addWidget(btn_me);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(display);
    mainLayout->addLayout(hl);
    mainLayout->addLayout(layout);

    setLayout(mainLayout);
}

CalcWidget::~CalcWidget()
{

}


QPushButton* CalcWidget::createButton(QString text) {
    QPushButton *btn = new QPushButton(text);
    btn->setMinimumSize(40, 40);
    connect(btn, SIGNAL(clicked(bool)), SLOT(buttonClicked()));
    return btn;
}


void CalcWidget::buttonClicked() {
    QPushButton *button = (QPushButton*)sender();
    QString operand = button->text();

    if (operand == "ME") {
        curOperand = "";
        display->display(0);
        opStack.clear();
    }
    else if (operand.contains(QRegExp("[0-9]"))) {
        curOperand.append(operand);
        display->display(curOperand);
    }
    else if (operand ==".") {
        if (curOperand.contains(".")) return;
        curOperand.append(operand);
        display->display(curOperand);
    }
    else {
        if (opStack.count() >=2) {
            opStack.push(curOperand);
            calculate();
            opStack.clear();
            opStack.push(QString().setNum(display->value()));
            if (operand != "=") {
                opStack.push(operand);
            }
        }
        else {
            opStack.push(curOperand);
            curOperand = "";
            opStack.push(operand);
            //display->display("0");
        }
    }
}


void CalcWidget::calculate() {
    double operand2 = opStack.pop().toDouble();
    QString operation = opStack.pop();
    double operand1 = opStack.pop().toDouble();
    double result = 0;

    if (operation == "+") {
        result = operand1 + operand2;
    }
    if (operation == "/") {
        result = operand1 / operand2;
    }
    if (operation == "-") {
        result = operand1 - operand2;
    }
    if (operation == "X") {
        result = operand1 * operand2;
    }

    display->display(result);
}
