/*squares is the class that creates 64 squareHandler objects. SquareHandler handles a single square while
 * Squares handles all the single squares together.*/

#ifndef SQUARES_H
#define SQUARES_H
#include <QLabel>
#include <QPlainTextEdit>
#include "squarehandler.h"
#include <QString>

class squares : public QLabel
{
public:
    squares();
    squares(QWidget*);
    void formatting(QWidget*);
    void chessBoard(QWidget*);
    void chessPieces(int);
    void changePixmap(int row,int col,char piece,char color);
    void editText(QString,int);
    static SquareHandler *tiles[8][8];
    static QPlainTextEdit *messages;
    static QPlainTextEdit *moves;
    bool checkForJump(int,int,int,int);
    void clearBoard();
};

#endif // SQUARES_H
