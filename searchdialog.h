#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H
#include <QDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QCheckBox>

class searchdialog: public QDialog{
	Q_OBJECT
private:
	QLineEdit* modelloS;
	QSpinBox* cordeS;
	QComboBox* tipologiaS;
	QDoubleSpinBox* pricelS;
	QDoubleSpinBox* pricehS;
	QCheckBox* amplS;
	QLineEdit* ponteS;
	QLineEdit* pickupS;
public:
	searchdialog(QWidget* =0);
};

#endif