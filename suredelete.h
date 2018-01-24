#ifndef SUREDELETE_H
#define SUREDELETE_H

#include <QDialog>

namespace Ui {
class SureDelete;
}

class SureDelete : public QDialog
{
    Q_OBJECT

public:
    explicit SureDelete(QWidget *parent = 0);
    ~SureDelete();
    bool success = false;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SureDelete *ui;
};

#endif // SUREDELETE_H
