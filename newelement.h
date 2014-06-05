#ifndef NEWELEMENT_H
#define NEWELEMENT_H
#include <QtGui>
#include <QWidget>

//questa classe è utilizzata per l'inserimento del nuovo dato in elementdialog

class newelement : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* modello;
    QSpinBox* corde;
    QComboBox* tipologia;
    QDoubleSpinBox* price;
    QCheckBox* ampl;
    QLineEdit* ponte;
    QLineEdit* pickup;
public:
    explicit newelement(QWidget *parent = 0);
    bool isComplete() const;
    QString getmodello()const;
    int getcorde()const;
    int gettipologia()const;
    double getprezzo()const;
    bool getampl()const;
    QString  getponte()const;
    QString getpickup()const;
signals:

public slots:
    void changeElement(int);
};

#endif // NEWELEMENT_H
