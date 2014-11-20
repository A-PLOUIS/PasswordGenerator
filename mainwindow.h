#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTextCodec>
#include <QMainWindow>
#include <QFile>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void readyCreatePassWordList();
private:
    Ui::MainWindow *ui;

    QStringList *makePassword_N_Character(QStringList *originalList);

private slots:
    void rechercherInfoManquantes();
    void genererListeMotDePasse();
};

#endif // MAINWINDOW_H
