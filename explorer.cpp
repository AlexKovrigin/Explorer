#include "explorer.h"
#include "ui_explorer.h"
#include <QMessageBox>

Explorer::Explorer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Explorer)
{
    ui->setupUi(this);
    ui->explorer->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->explorer,&QTreeWidget::customContextMenuRequested,this,&Explorer::prepareMenu);
}
Explorer::~Explorer()
{
    delete ui; // деструктор
}
void Explorer::prepareMenu( const QPoint & pos )
{

    QTreeWidget *tree = ui->explorer;

    QTreeWidgetItem *nd = tree->itemAt(pos);

    //qDebug()<<pos<<nd->text(0);
    //QString par = nd->text(0);
    QMenu menu(this);
    //nd->isDisabled();
    Cnd = nd;
    if(tree->itemAt( pos ) != 0)
    {
        QAction *openAct = new QAction(QIcon(":/open.ico"), tr("&Open"), this);
        connect(openAct, SIGNAL(triggered()), this, SLOT(openDev()));
        menu.addAction(openAct);
    }
    QAction *newAct = new QAction(QIcon(":/new.ico"), tr("&New File"), this);
    connect(newAct, SIGNAL(triggered()), this, SLOT(newDev()));
    menu.addAction(newAct);
    QAction *newFAct = new QAction(QIcon(":/folderC.ico"), tr("&New Folder"), this);
    connect(newFAct, SIGNAL(triggered()), this, SLOT(newFDev()));
    menu.addAction(newFAct);
    if(tree->itemAt( pos ) != 0 && nd->text(0).contains("."))
    {
        QAction *copyAct = new QAction(QIcon(":/copy.ico"), tr("&Copy"), this);
        connect(copyAct, SIGNAL(triggered()), this, SLOT(copyDev()));
        menu.addAction(copyAct);
        QAction *cutAct = new QAction(QIcon(":/cut.ico"), tr("&Cut"), this);
        connect(cutAct, SIGNAL(triggered()), this, SLOT(cutDev()));
        menu.addAction(cutAct);
        QAction *renameAct = new QAction(QIcon(":/rename.ico"), tr("&Rename"), this);
        connect(renameAct, SIGNAL(triggered()), this, SLOT(renameDev()));
        menu.addAction(renameAct);

        QAction *deleteAct = new QAction(QIcon(":/bin.ico"), tr("&Delete"), this);
        connect(deleteAct, SIGNAL(triggered()), this, SLOT(removeDev()));
        menu.addAction(deleteAct);
    }
    QAction *pasteAct = new QAction(QIcon(":/paste.ico"), tr("&Paste"), this);
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(pasteDev()));
    menu.addAction(pasteAct);
    menu.exec( tree->mapToGlobal(pos) );
}
/*
 *
/////////////////////////////////////////////////////////////////////////////////////////


                     Great border of boring code and code made by Шурик


////////////////////////////////////////////////////////////////////////////////////////

*/
void Explorer::updateTable()
{
    ui->explorer->clear(); // обновляем папку
    openFolder(false);
}

void Explorer::newDev() // функция создания файла
{
    fail2:
    Create c; // просим имя файла
    c.exec();
    if(!c.success)
        return;
    // проверка формата: name.smth
    if(!c.name.contains(".") || c.name.at(0) == '.' || c.name.at(c.name.size() - 1) == '.'){
        QMessageBox s;
        s.setText("Invalid format!");
        s.exec(); // вывод сообщения
        goto fail2;
    }
    // создание файла
    QFile file(path + c.name);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    { }
    updateTable();
    file.close();
}
void Explorer::newFDev() // создание папки
{
    fail1:
    Create d;
    d.exec();
    if(!d.success)
        return;
    // проверка формата
    if(d.name.contains(".") || d.name == "s") {
        QMessageBox j;
        j.setText("Invalid format! No dots allowed!");
        j.exec();
        goto fail1;
    }
    QString mPath = path + d.name + "/"; // создание папки
    QDir mega = QDir::root();
    mega.mkpath(mPath);
    updateTable();
}
void Explorer::copyDev() // копирование файла
{
    copyName = Cnd->text(0);
    copyPath = path + copyName;
}
void Explorer::pasteDev() // вставка файла
{
    if(copyPath  == "")
    {
        QMessageBox a;
        a.setText("Your buffer is empty!");
        a.exec();
        return;
    }
    QFile::copy(copyPath, path + copyName);
    if(wasCut) {
        wasCut = false;
        removeFile(copyPath);
    }
    updateTable();
}
void Explorer::renameDev() // переименовать файл
{
    RenameDialog o; // просьба потверждения
    o.exec();
    if(!o.success)
        return;
    QString dpath = Cnd->text(0);
    QFile::rename(path + dpath, path + o.text);
    updateTable();
}
void Explorer::openDev() // открытие файла
{
    cPath = Cnd->text(0);
    if(cPath == ".") { // если это точка - то есть возвращение в предыдущую директорию
        longPath.pop_back();
        updateTable();
    }
    else if(cPath.contains(".")) { // если файл
        QDesktopServices::openUrl(path + cPath);
    }
    else // если папка
    {
        ui->explorer->clear();
        openFolder(true);
    }
}
void Explorer::removeDev() // удаление файла через ячейку
{
    removeFile(Cnd->text(0)); // удаление через строку
}
void Explorer::removeFile(QString dPath) // удаление через строку
{
    SureDelete i;
    i.exec();
    if(!i.success)
        return;
    QFile::remove(path + dPath); // удаление
    updateTable();
}
void Explorer::cutDev() // вырезание файла
{
    copyDev(); // копирование файла
    wasCut = true; // передача фунции pasteDev() - требуется удаление файла (вырезаниеы)
    updateTable();
}

//--------------------------------------------------------------------------------------//

void Explorer::openFolder(bool addFolder) // функция открытия директории и вывода на таблоы
{
    if(addFolder)
        longPath << cPath + "/";
    // перезапись path
    path = "";
    for(int i = 0; i < longPath.size(); i++)
        path += longPath[i];
    // если это не первая директория, то добавляем ячейку для возврата наверх
    if(longPath[0] != cPath + "/" && longPath.size() != 1) {
        QTreeWidgetItem* itmA = new QTreeWidgetItem(ui->explorer);
        itmA->setText(0, ".");
        itmA->setIcon(0, QIcon(":/back.ico"));
    }
    QDir dir(path);
    QFileInfoList dirList = dir.entryInfoList();
    if(dirList.size() == 2)
        return;
    int is = -1;
    if(path.size() == 3)
        is = 0;
    else
        is = 2;
    for(int i = is; i < dirList.size(); i++) // присвоение иконок к файлам
    {
        QTreeWidgetItem *itmC = new QTreeWidgetItem(ui->explorer);
        QString txtC = dirList.at(i).fileName();
        if(!txtC.contains("."))
            itmC->setIcon(0, QIcon(":/folder.ico"));
        else if(txtC.contains(".txt"))
            itmC->setIcon(0, QIcon(":/text.ico"));
        else if(txtC.contains(".cpp"))
            itmC->setIcon(0, QIcon(":/cpp.ico"));
        else if(txtC.contains(".mp3") || txtC.contains(".aac"))
            itmC->setIcon(0, QIcon(":/music.ico"));
        else if(txtC.contains(".mp4") || txtC.contains(".avi") || txtC.contains(".vga"))
            itmC->setIcon(0, QIcon(":/movie.ico"));
        else if(txtC.contains(".jpg") || txtC.contains(".jpeg") || txtC.contains(".png") || txtC.contains(".raw"))
            itmC->setIcon(0, QIcon(":/photo.ico"));
        else if(txtC.contains(".dll"))
            itmC->setIcon(0, QIcon(":/dll.ico"));
        else if(txtC.contains(".doc") || txtC.contains(".docx"))
            itmC->setIcon(0, QIcon(":/word.ico"));
        else if(txtC.contains(".xls") || txtC.contains(".xlsx"))
            itmC->setIcon(0, QIcon(":/excel.ico"));
        else if(txtC.contains(".ppt") || txtC.contains(".pptx"))
            itmC->setIcon(0, QIcon(":/powerpoint.ico"));
        else if(txtC.contains(".exe") || txtC.contains(".bat"))
            itmC->setIcon(0, QIcon(":/exe.ico"));
        else
            itmC->setIcon(0, QIcon(":/file.ico"));
        itmC->setText(0, txtC);
    }
    ui->statuslbl->setText("Current directory: " + path); // вывод статус бара
}
void Explorer::on_pushButton_clicked() // открытие директории
{
    ui->explorer->clear();
    path = ui->lineEdit->text(); // получение вводных данных
    // проверка формата
    if(!path.contains(":") || path.at(path.size() - 1) == '/' || path.contains(".") || path.at(0) == ':')
    {
        // вывод
        QMessageBox u;
        u.setText("Invalid Format, see example!");
        u.exec();
        ui->lineEdit->clear();
        return;
    }
    cPath = path;
    // очистка массива
    for(int i = 0; i < longPath.size(); i++)
        longPath.pop_back();
    openFolder(true);
}

void Explorer::on_actionAbout_us_triggered() // страница о нас
{
    About t;
    t.exec();
}

void Explorer::on_explorer_doubleClicked(const QModelIndex &index)
{
    cPath = index.data().toString();
    if(cPath == ".") {
        longPath.pop_back();
        updateTable();
        return;
    }
    if(cPath.contains(".")) {
        QDesktopServices::openUrl(path + cPath);
        return;
    }
    ui->explorer->clear();
    openFolder(true);
}
