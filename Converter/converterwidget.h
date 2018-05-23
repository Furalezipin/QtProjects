#ifndef CONVERTERWIDGET_H
#define CONVERTERWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QTabWidget>
#include <QLabel>
#include <QGridLayout>

class ConverterWidget : public QWidget
{
    Q_OBJECT
private:
    QComboBox *cb_dimension;
    QLineEdit *le_value;
    QTabWidget *tabWidget;

    QMap<QString, double> dimWeight;
    QMap<QString, double> dimDistance;
    QMap<QString, double> dimAmount;
    QMap<QString, double> dimCurrency;

    QMap<QString, QLabel*> labelWeight;
    QMap<QString, QLabel*> labelDistance;
    QMap<QString, QLabel*> labelAmount;
    QMap<QString, QLabel*> labelCurrency;

    enum TAB {WEIGHT, DISTANCE, AMOUNT, CURRENCY};

public:
    ConverterWidget(QWidget *parent = 0);
    ~ConverterWidget();
    void createUI();
    void fillComboBox(QMap<QString, double> &values);
    void calculate(QMap<QString, double> &values, QMap<QString, QLabel*> &labels);
    QWidget* createTab(QMap<QString, double> &values);
    QWidget* createTabUI(QMap<QString, double> &values, QMap<QString, QLabel*> &labels);
public slots:
    void onTabChanged(int tab);
    void convert();
};

#endif // CONVERTERWIDGET_H
