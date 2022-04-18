#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString outputString = "";

void MainWindow::on_processBtn_clicked()
{
    outputString = ui->link->toPlainText();

    /* rename playlist & add the video index as a prefix */
    if (ui->indexedBtn->isChecked()){
        outputString+= " -o \"%(playlist_index)s-%(title)s.%(ext)s \" ";
    }

    /* Download the whole playlist or range of videos */
    if (ui->playlistBtn->isChecked()){
        outputString += " --yes-playlist ";
    }else if (ui->rangePlaylistBtn->isChecked()){
        qint32 s = ui->startIndexBtn->value();
        qint32 e = ui->endIndexBtn->value();
        outputString += " --playlist-items " + QString::number(s) + "-" + QString::number(e);
    }

    /* Quality options: audio only, 720p, 1080p */
    if (ui->q720Btn->isChecked()){
        outputString += " -f 22 ";
    }else if (ui->q1080Btn->isChecked()){
        outputString += " -f 137+140 ";
    }else if (ui->mp3Btn->isChecked()){
        outputString += " -f 140 ";
    }

    /* display the command */
    ui->output->setText( "yt-dlp " + outputString );
}


void MainWindow::on_cpyBtn_clicked()
{
    QClipboard* clpbord = QApplication::clipboard();
    clpbord->setText(ui->output->toPlainText());
}

