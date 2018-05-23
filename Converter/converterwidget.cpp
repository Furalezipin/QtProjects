#include "converterwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

ConverterWidget::ConverterWidget(QWidget *parent)
    : QWidget(parent) {

    dimWeight["грамм"] = 1;
    dimWeight["килограмм"] = 1000;
    dimWeight["тонна"] = 1000000;
    dimWeight["фунт"] = 453.6;

    dimDistance["миллиметр"] = 1;
    dimDistance["сантиметр"] = 10;
    dimDistance["метр"] = 1000;
    dimDistance["километр"] = 1000000;
    dimDistance["ярд"] = 914.4;

    dimAmount["см3"] = 1;
    dimAmount["литр"] = 1000;
    dimAmount["км3"] = 1000000000000000;
    dimAmount["галлон"] = 3785;

    dimCurrency["рубль"] = 1;
    dimCurrency["доллар"] = 55;
    dimCurrency["евро"] = 65;
    dimCurrency["гривна"] = 4;

    createUI();
    setWindowTitle("Конвертор величин");

    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onTabChanged(int)));
    connect(le_value, SIGNAL(textChanged(QString)), SLOT(convert()));
    connect (cb_dimension, SIGNAL(currentIndexChanged(int)), SLOT(convert()));

}

ConverterWidget::~ConverterWidget() {

}

void ConverterWidget::createUI() {

    cb_dimension = new QComboBox();
    fillComboBox(dimWeight);

    le_value = new QLineEdit("0");
    tabWidget = new QTabWidget();

    QHBoxLayout *hl1 = new QHBoxLayout;
    hl1->addWidget(le_value);
    hl1->addWidget(cb_dimension);

    tabWidget = new QTabWidget();
    tabWidget->addTab(createTabUI(dimWeight, labelWeight), "Вес");
    tabWidget->addTab(createTabUI(dimDistance, labelDistance), "Расстояние");
    tabWidget->addTab(createTabUI(dimAmount, labelAmount), "Объем");
    tabWidget->addTab(createTabUI(dimCurrency, labelCurrency), "Валюта");

    QVBoxLayout *vl1 = new QVBoxLayout;
    vl1->addLayout(hl1);
    vl1->addWidget(tabWidget);
    setLayout(vl1);
    setFixedSize(350, 300);

}


void ConverterWidget::onTabChanged(int tab) {

    switch (tab) {
    case TAB::WEIGHT:
        fillComboBox(dimWeight);
        calculate(dimWeight, labelWeight);
        break;
    case TAB::AMOUNT:
        fillComboBox(dimAmount);
        calculate(dimAmount, labelAmount);
        break;
    case TAB::DISTANCE:
        fillComboBox(dimDistance);
        calculate(dimDistance, labelDistance);
        break;
    case TAB::CURRENCY:
        fillComboBox(dimCurrency);
        calculate(dimCurrency, labelCurrency);
        break;
    default:
        break;
    }

}


void ConverterWidget::convert() {
    switch (tabWidget->currentIndex()) {
    case TAB::WEIGHT:
        calculate(dimWeight, labelWeight);
        break;
    case TAB::DISTANCE:
        calculate(dimDistance, labelDistance);
        break;
    case TAB::AMOUNT:
        calculate(dimAmount, labelAmount);
        break;
    case TAB::CURRENCY:
        calculate(dimCurrency, labelCurrency);
        break;
    default:
        break;
    }

}

QWidget* ConverterWidget::createTabUI(QMap<QString, double> &values, QMap<QString, QLabel*> &labels) {
    QWidget *widget = new QWidget;
    QLabel *lbl_name, *lbl_value;
    QGridLayout *layout = new QGridLayout;
    int row = 0;

    QMap<QString, double>::iterator it = values.begin();
    for(; it != values.end(); ++it) {
        lbl_name = new QLabel(it.key());
        lbl_value = new QLabel ("0");
        layout->addWidget(lbl_value, row, 0);
        layout->addWidget(lbl_name, row, 1);
        labels[it.key()] = lbl_value;
        ++row;
    }
    widget->setLayout(layout);
    return widget;
}

void ConverterWidget::fillComboBox(QMap<QString, double> &values) {
    cb_dimension->clear();
    QMap<QString, double>::iterator it = values.begin();
    for(; it != values.end(); ++it) {
        cb_dimension->addItem(it.key());
    }
}


void ConverterWidget::calculate(QMap<QString, double> &values, QMap<QString, QLabel *> &labels) {
    if (cb_dimension->currentText() == "") return;
    double value = le_value->text().toDouble();
    double kf = values[cb_dimension->currentText()];

    QMap<QString, double>::iterator it = values.begin();
    for(; it != values.end(); ++it) {
        QString dimen = it.key();
        double kf2 = it.value();
        double result = value * (kf/kf2);
        QLabel* label = labels[dimen];
        label->setText(QString::number(result));
    }
}
