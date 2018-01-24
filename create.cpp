#include "create.h"
#include "ui_create.h"

Create::Create(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create)
{
    ui->setupUi(this);
    success = false;
}

Create::~Create()
{
    delete ui;
}

void Create::on_buttonBox_accepted()
{
    name = ui->lineEdit->text(); // сохранение
    success = true;
    close();
}

void Create::on_buttonBox_rejected()
{
    close();
}
