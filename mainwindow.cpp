#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->boutonGenerer,SIGNAL(clicked()),this,SLOT(rechercherInfoManquantes()));
    connect(this,SIGNAL(readyCreatePassWordList()),this,SLOT(genererListeMotDePasse()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList* MainWindow::makePassword_N_Character(QStringList *originalList)
{
    int originalListLenght = originalList->length();
    int static minimumChar=33;
    int static maximumChar=126;

    if(originalList->isEmpty()){
        for(int currentChar(minimumChar);currentChar<(maximumChar+1);currentChar++){
            originalList->append(QChar(currentChar));
        }

        for(int i =0;i<originalList->length();i++){
            qDebug() << "Element " << (33+i) << " : " << originalList->at(i);
        }
        qDebug() <<QTextCodec::codecForLocale()->name();

        return originalList;
    }else{

        QStringList *newPasswordList = new QStringList();

        for(int i=0;i<originalListLenght;i++){
            QString baseString = originalList->at(i);

            for(int currentChar(minimumChar);currentChar<(maximumChar+1);currentChar++){
                if(currentChar!=127 || currentChar!=169 || currentChar!=170){
                    QString ligne = baseString + QChar(currentChar);
                    newPasswordList->append(ligne);
                }

            }


        }
        originalList->clear();
        delete originalList;
        return newPasswordList;
    }
}


void MainWindow::rechercherInfoManquantes()
{
    if(this->ui->cheminDossier->text()==""){
        this->ui->cheminDossier->setStyleSheet("border:1px solid red");
        this->ui->statusBar->showMessage(tr("Manque le dossier de sauvegarde"));
    }else{
        this->ui->cheminDossier->setStyleSheet("border:1px solid black");
    }
    if(this->ui->MinLettres->text()==""){
            this->ui->MinLettres->setStyleSheet("border:1px solid red");
            this->ui->statusBar->showMessage(tr("Minimum de lettres ?"));
    }else{
        this->ui->MinLettres->setStyleSheet("border:1px solid black");
    }
    if(this->ui->MaxLettres->text()==""){
        this->ui->MaxLettres->setStyleSheet("border:1px solid red");
        this->ui->statusBar->showMessage(tr("Maximum de lettres ?"));
    }
    else {
        this->ui->MaxLettres->setStyleSheet("border:1px solid black");
    }
    if(this->ui->nomFichier->text()==""){
        this->ui->nomFichier->setStyleSheet("border:1px solid red");
        this->ui->statusBar->showMessage(tr("Manque le nom du fichier"));
    }else{
        this->ui->nomFichier->setStyleSheet("border:1px solid black");
    }
    emit readyCreatePassWordList();
}

void MainWindow::genererListeMotDePasse()
{
    QString filePath = this->ui->cheminDossier->text() + this->ui->nomFichier->text();
    QFile fichierListeMdp(filePath);
    //if(fichierListeMdp.exists())
    //    fichierListeMdp.remove();

    /*qDebug() << fichierListeMdp.fileName();
    fichierListeMdp.open(QFile::WriteOnly);
    int minimum = this->ui->MinLettres->text().toInt();
    int maximum = this->ui->MaxLettres->text().toInt();
    for (int i = minimum; i < maximum; ++i) {
        for (int asciicode=33;asciicode<127; ++asciicode){

            qDebug() << QChar::fromLatin1(asciicode);
            QString ligne; ligne.append(QChar::fromLatin1(asciicode));
            fichierListeMdp.write(ligne.toLatin1());
            fichierListeMdp.waitForBytesWritten(100);
            fichierListeMdp.write("\n");

        }            qDebug() <<  "Test " << QChar('µ').unicode();

    }*/

    //Algorythme de cgénération de mot de passe

QStringList* testListe= new QStringList;
this->makePassword_N_Character(testListe);
qDebug() << "Begin Liste : ";
for(int t=0;t<testListe->length();t++)
    qDebug() << "Element " << t << " : " << testListe->at(t);

testListe = this->makePassword_N_Character(testListe);
qDebug() << "New Liste : ";
for(int t=0;t<testListe->length();t++)
    qDebug() << "Element " << t << " : " << testListe->at(t);
delete testListe;

    fichierListeMdp.close();
    this->ui->statusBar->showMessage("Terminé");
}
