/*mainwindow generates the main window and has the functions that
 * gets called when user clicks on a menu bar item*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_Game_triggered();

    void on_actionReally_Bad_Chess_triggered();

    void on_actionChaos_Chess_triggered();

    void on_actionExit_triggered();

    void on_actionEnd_Game_triggered();

    void on_actionHow_To_Play_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    int mode=0;
};

#endif // MAINWINDOW_H
