#ifndef EXPLORER_H
#define EXPLORER_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QTreeView>
#include <QDir>
#include <QFileInfoList>
#include <QMessageBox>
#include <QFileDialog>
#include <about.h>
#include <QObject>
#include <QVector>
#include <QDesktopServices>
#include <QFile>
#include <QAction>
#include <create.h>
#include <renamedialog.h>
#include <suredelete.h>
namespace Ui {
class Explorer;
}

class Explorer : public QMainWindow
{
    Q_OBJECT
public slots:
    void newDev(); // создание файла
    void newFDev(); // создание папки
    void copyDev(); // копирование
    void pasteDev(); // вставить
    void renameDev(); // переименовать
    void openDev(); // открыть
    void removeDev(); // удалить
    void cutDev(); // вырезать
public:
    explicit Explorer(QWidget *parent = 0);
    ~Explorer();

private slots:
    void on_pushButton_clicked();

    void on_actionAbout_us_triggered();

    void on_explorer_doubleClicked(const QModelIndex &index);

private:
    void openFolder(bool addFolder); // функция вывода на экран директории path
    Ui::Explorer *ui;
    QString path; // открытая директория
    QString cPath; // название открытой папки
    void prepareMenu(const QPoint & pos); // "стыренная" функция открывающая меню по нажатии правой кнопки
    QVector <QString> longPath; // массив с названиями папок, для возможности возвращатся в обратную папку
    QString copyPath; // путь папки файла копирования
    QString copyName; // название файла копирования
    QTreeWidgetItem* Cnd; // ячейка на которую навели при нажатии правой кнопки
    bool wasCut; // нужно ли удаление файла при вставке
    void updateTable();
    void removeFile(QString dPath);
};

#endif // EXPLORER_H
