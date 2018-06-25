#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <stdio.h>
#include <QTextStream>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->barPw->setHidden(true);
    //this->centralWidget()->setStyleSheet("background-image: url(./bg.jpg);");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCancel_clicked()
{
    QApplication::quit();
}

void MainWindow::on_btnBrowse_clicked()
{
    QString input;
    QString browsePath = QFileDialog::getOpenFileName(this, "Select file...", QDir::homePath(), tr("Text Files (*.txt)"));
    QFile infile(browsePath);

    if (!infile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    while (!infile.atEnd()) {
        QByteArray line = infile.readLine();
        input+=line;
    }

    ui->input_Textedit->setPlainText(input);
}

void MainWindow::on_btnEncryp_clicked()
{
    QString input;
    QString output;
    int schluessel;
    char x;
    input = ui->input_Textedit->toPlainText();
    schluessel = ui->sboxKey->value();
    for(int i=0;i<input.length();i++)
    {
        x = input.at(i).toLatin1();
        char y;
        if(int(x)>=65 && int(x)<=90)
        {
            y=int(x);
            for(int i=0;i<schluessel;i++)
            {
                if(y<90)
                {
                    y++;
                }
                else if(y==90)
                {
                    y=65;
                }
            }
            output+=y;
        }
        else if((int(x)>=97) && (int(x)<=122))
        {
            y=int(x);
            for(int i=0;i<schluessel;i++)
            {
                if(y<122)
                {
                    y++;
                }
                else if(y==122)
                {
                    y=97;
                }
            }
            output+= y;
        }
        else
        {
            output+= x;
        }
    }
    ui->output_Textedit->setPlainText(output);
}

void MainWindow::on_btnDecrypt_clicked()
{
    QString input;
    QString output;
    int schluessel;
    char x;
    input = ui->input_Textedit->toPlainText();
    schluessel = ui->sboxKey->value();
    for(int i=0;i<input.length();i++)
    {
        x = input.at(i).toLatin1();
        char y;
        if(int(x)>=65 && int(x)<=90)
        {
            y=int(x);
            for(int i=0;i<schluessel;i++)
            {
                if(y>65)
                {
                    y--;
                }
                else if(y==65)
                {
                    y=90;
                }
            }
            output+=y;
        }
        else if((int(x)>=97) && (int(x)<=122))
        {
            y=int(x);
            for(int i=0;i<schluessel;i++)
            {
                if(y>97)
                {
                    y--;
                }
                else if(y==97)
                {
                    y=122;
                }
            }
            output+=y;
        }
        else
        {
            output+=x;
        }
    }
    ui->output_Textedit->setPlainText(output);
}

void MainWindow::on_btnSave_clicked()
{
    QString savePath;
    savePath = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "",
                               tr("Text Files (*.txt)"));
    QFile outputfile(savePath);
    if (outputfile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream stream(&outputfile);
        stream << ui->output_Textedit->toPlainText();
        QMessageBox msgBox;
        msgBox.setText("File has been saved!");
        msgBox.setWindowTitle("File saved!");
        //msgBox.setInformativeText(browsePath);
        msgBox.exec();
    }
}


void MainWindow::on_checkPw_toggled(bool checked)
{
    ui->barPw->setHidden(!checked);
}

void MainWindow::on_input_Textedit_textChanged()
{
    QString pw;
    QString wort;
    QString verboten="hund;katze;maus;";
    int level=0;
    int digitcount=0;
    int specialcount=0;
    int uppercount=0;
    int lowercount=0;
    int posSemikolon;
    bool trivial=false;

    pw = ui->input_Textedit->toPlainText();
    /*posSemikolon = verboten.toStdString().find(";");
    while (posSemikolon !=-1)
    {
        wort = verboten.mid(0,posSemikolon);
        verboten.toStdString().erase(0,posSemikolon+1);
        posSemikolon = verboten.toStdString().find(";");
        if(pw.toStdString().find(wort.toStdString())!=-1)
        {
            trivial=true;
            break;
        }
    }
    if(trivial==false)
    {
        level++;
    }*/

    if (pw.length()>=8)
    {
        level++;
    }

    for(int i=0;i<pw.length();i++)
    {
        if(isdigit(pw.at(i).toLatin1()) == true)
        {
            digitcount++;
        }
    }
    if(digitcount >= 2)
    {
        level++;
    }

    for(int i=0;i<pw.length();i++)
    {
        if((isdigit(pw.at(i).toLatin1()) == false) && (isalpha(pw.at(i).toLatin1()) == false))
        {
            specialcount++;
        }
    }
    if(specialcount >= 2)
    {
        level++;
    }

    for(int i=0;i<pw.length();i++)
    {
        if(isupper(pw.at(i).toLatin1()) == true && (isalpha(pw.at(i).toLatin1()) == true))
        {
            uppercount++;
        }
    }
    if(uppercount >= 1)
    {
        level++;
    }

    for(int i=0;i<pw.length();i++)
    {
        if(islower(pw.at(i).toLatin1()) == true && (isalpha(pw.at(i).toLatin1()) == true))
        {
            lowercount++;
        }
    }
    if(lowercount >= 1)
    {
        level++;
    }
    ui->barPw->setValue(level);

    if (level == 1)
    {
        ui->barPw->setStyleSheet("::chunk {background-color: red}");
    }
    if (level == 2)
    {
        ui->barPw->setStyleSheet("::chunk {background-color: orange}");
    }
    if (level == 3)
    {
        ui->barPw->setStyleSheet("::chunk {background-color: yellow}");
    }
    if (level == 4)
    {
        ui->barPw->setStyleSheet("::chunk {background-color: green}");
    }
}

