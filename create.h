#ifndef CREATE_H
#define CREATE_H

#include <QDialog>

namespace Ui {
class Create;
}

class Create : public QDialog
{
    Q_OBJECT

public:
    explicit Create(QWidget *parent = 0);
    ~Create();
    QString name;
    bool success = false;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Create *ui;
};

#endif // CREATE_H
