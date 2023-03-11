/*mainwindow generates the main window and has the functions that
 * gets called when user clicks on a menu bar item*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "squares.h"
#include <QMessageBox>
#include <QApplication>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Game_triggered()
{
    squares sq;
    if(mode==0){
        QMessageBox* mb= new QMessageBox();
        mb->setText("No Game Mode Selected!");
        mb->exec();
    }else{
        sq.clearBoard();
        sq.chessPieces(mode);
    }
}

void MainWindow::on_actionReally_Bad_Chess_triggered()
{
    mode=1;
}

void MainWindow::on_actionChaos_Chess_triggered()
{
    mode=2;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionEnd_Game_triggered()
{
    squares sq;
    sq.clearBoard();
}

void MainWindow::on_actionHow_To_Play_triggered()
{
    QMessageBox* mb= new QMessageBox();
    mb->setText("This game features two unique variations of chess. All the rules "
                "follow typical chess except the pieces will be placed in random orders "
                "each game. To select a piece to move click directly on the piece and "
                "then click on the tile you want to move to. To cancel a selection just "
                "put the piece back on its original tile or right click anywhere.");
    mb->exec();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox* mb= new QMessageBox();
    mb->setText("**Unique Chess Project**\nTrine Universtiy class project for CS 1123 01\n"
                "Project made by Michael Barns and Shiqi Wu\n5/5/2017");
    mb->exec();
}
