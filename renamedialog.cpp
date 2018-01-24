#include "renamedialog.h"
#include "ui_renamedialog.h"

RenameDialog::RenameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenameDialog)
{
    ui->setupUi(this);
    success = false;
}

RenameDialog::~RenameDialog()
{
    delete ui;
}

void RenameDialog::on_acceptBtn_clicked()
{
    QString ptext = ui->lineName->text();
    if(!ptext.contains(".") || ptext.at(0) == '.' || ptext.at(ptext.size() - 1) == '.')
    {
        QMessageBox p;
        p.setText("Incorrect Format!");
        p.exec();
        ui->lineName->clear();
        return;
    }
    text = ptext;
    success = true;
    close();
}
void RenameDialog::on_lineName_editingFinished()
{

}
