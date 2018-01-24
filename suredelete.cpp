#include "suredelete.h"
#include "ui_suredelete.h"

SureDelete::SureDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SureDelete)
{
    ui->setupUi(this);
    success = false;
}

SureDelete::~SureDelete()
{
    delete ui;
}

void SureDelete::on_buttonBox_accepted()
{
    success = true;
    close();
}

void SureDelete::on_buttonBox_rejected()
{
    close();
}
