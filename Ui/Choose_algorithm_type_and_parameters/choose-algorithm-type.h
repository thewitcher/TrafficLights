#ifndef CHOOSEALGORITHMTYPE_H
#define CHOOSEALGORITHMTYPE_H

#include <QDialog>

namespace Ui {
    class ChooseAlgorithmType;
}

class QRadioButton;

class ChooseAlgorithmType : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseAlgorithmType(QWidget *parent = 0);
    ~ChooseAlgorithmType();
    static bool S_CAN_RUN;

private:
    Ui::ChooseAlgorithmType *ui;
    void involvementForRadioButtons();
    void involvementForBackButtons();
    void involvementForOkOrNextOrDefaultButtons();
    void setNamesForRadioButtons();
    QList<QString> defaultValuesForAllSubcycleAlgorithm();
    QList<QString> defaultValuesForOneSubcycleAlgorithm();
    void customParametersForGA( const int& position, const QList<QRadioButton*> &list );
    void customParametersForGeneral( const int& position, const QList<QRadioButton*> &list );
    QList<QString> defaultValuesForGeneral();
    void setAutoExclusiveForRadioButtons();
    void clearAll();

private slots:
    void nextPage();
    void setParametersForAlgorithm();
    void backToMainPage();
    void routeToPreviousPage();
    void routeToNextPage();
    void setdefaultValuesForGA();
    void setDefaultValuesForGeneral();
};

#endif // CHOOSEALGORITHMTYPE_H
