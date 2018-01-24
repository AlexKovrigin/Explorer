#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class RenameDialog;
}

class RenameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenameDialog(QWidget *parent = 0);
    ~RenameDialog();
    QString text = "";
    bool success = false;
private slots:
    void on_acceptBtn_clicked();

    void on_lineName_editingFinished();

private:
    Ui::RenameDialog *ui;
};

#endif // RENAMEDIALOG_H
