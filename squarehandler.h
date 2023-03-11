/* SquareHandler is the class that handles the functions and values for a single chess tile.
 * each SquareHandler object has local variables like the row, pieceName, pieceColor and has static variable
 * that need to be shared across all tiles of the board like the last clicked piece, color, row, and col.*/

#ifndef SQUAREHANDLER_H
#define SQUAREHANDLER_H
#include <QLabel>
#include <QPalette>
#include <QImage>

class SquareHandler : public QLabel
{
public:
    SquareHandler(QWidget*);
    SquareHandler();
    void squareGeneration();
    void pieceGeneration();
    void mousePressEvent(QMouseEvent *event);
    void changePix(char,char);
    void editText(QString,int);
    char tileColor,pieceName,pieceColor;
    int row,col,tileNum;
private:
    static bool wTurn, fClick, gameIsStarted;
    static int LCRow, LCCol;
    static char LCPieceName,LCPieceColor;
    bool validMove();
    QString returntype(char);
};

#endif // SQUAREHANDLER_H
