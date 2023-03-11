#include "squares.h"
#include "squarehandler.h"
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QPlainTextEdit>
#include <QString>
/*squares is the class that creates 64 squareHandler objects. SquareHandler handles a single square while
 * Squares handles all the single squares together.*/

#include <stdlib.h>

int SquareHandler::LCRow=0;
int SquareHandler::LCCol=0;
char SquareHandler::LCPieceColor=' ';
char SquareHandler::LCPieceName=' ';
bool SquareHandler::wTurn=true;
bool SquareHandler::fClick=true;
bool SquareHandler::gameIsStarted=false;
SquareHandler *squares::tiles[8][8]={NULL};
QPlainTextEdit *squares::moves;
QPlainTextEdit *squares::messages;

//constructor for when the square class is used outside of main
squares::squares()
{

}

//constructor used in main. the parameter of baseWidget is passed into formatting and chessBoard so that the widgets being created like the message boxes can get a parent widget
squares::squares(QWidget* baseWidget)
{

    formatting(baseWidget);
    chessBoard(baseWidget);
}

//formatting is the function that creates the message boxes on either side of the board
void squares::formatting(QWidget* baseWidget)
{
    messages = new QPlainTextEdit(baseWidget);
    moves = new QPlainTextEdit(baseWidget);

    messages->setReadOnly(true);
    moves->setReadOnly(true);

    messages->setGeometry(24,40,150,512);
    moves->setGeometry(730,40,150,512);
}

//chessBoard is the function that creates the chessboard inbetween the two message boxes
void squares::chessBoard(QWidget* baseWidget)
{
    int ver,hor;
    ver=40;
    for(int i=0;i<8;i++)
    {
        hor=194;
        for(int j=0;j<8;j++)
        {
            tiles[i][j]= new SquareHandler(baseWidget);
            tiles[i][j]->setParent(baseWidget);
            tiles[i][j]->row=i;
            tiles[i][j]->col=j;
            tiles[i][j]->pieceName=' ';
            if((i+j)%2==0)
                tiles[i][j]->tileColor ='B';
            else
                tiles[i][j]->tileColor='W';
            tiles[i][j]->squareGeneration();
            tiles[i][j]->setGeometry(hor,ver,64,64);
            tiles[i][j]->setParent(baseWidget);
            hor+=64;
        }
        ver+=64;
    }
}

//chessPieces is the function that creates the chesspieces, unlike the first two creation functions chessPiecs isn't called until "New Game" is clicked in the menu bar
void squares::chessPieces(int mode)
{
    if(mode==1){
        bool kingIsSpawned = false;
        for(int y = 0; y < 8;y++){
            if(y==2)
                y=6;
            for(int x = 0; x < 8;x++){
               if(x==0&&y==6)
                   kingIsSpawned = false;

               int numb;
               if(kingIsSpawned==true)
               {

                   numb = 1 + rand() % 5;

                   switch(numb){
                   case 1:
                   {
                       tiles[y][x]->pieceName='b';
                       if(y<4)
                           tiles[y][x]->pieceColor='B';
                       else
                           tiles[y][x]->pieceColor='W';
                       break;
                   }
                   case 2:
                   {
                       tiles[y][x]->pieceName='k';
                       if(y<4)
                           tiles[y][x]->pieceColor='B';
                       else
                           tiles[y][x]->pieceColor='W';
                       break;
                   }
                   case 3:
                   {
                       tiles[y][x]->pieceName='p';
                       if(y<4)
                           tiles[y][x]->pieceColor='B';
                       else
                           tiles[y][x]->pieceColor='W';
                       break;
                   }
                   case 4:
                   {
                       tiles[y][x]->pieceName='q';
                       if(y<4)
                           tiles[y][x]->pieceColor='B';
                       else
                           tiles[y][x]->pieceColor='W';
                       break;
                   }
                   case 5:
                   {
                       tiles[y][x]->pieceName='r';
                       if(y<4)
                           tiles[y][x]->pieceColor='B';
                       else
                           tiles[y][x]->pieceColor='W';
                       break;
                   }
                   }

               }else if(kingIsSpawned==false && x==7 && (y==7 || y==1)){
                   tiles[y][x]->pieceName='K';
                   if(y<4)
                       tiles[y][x]->pieceColor='B';
                   else
                       tiles[y][x]->pieceColor='W';
               }else{
                   numb = 1 + rand() % 6;
                   switch(numb){
                   case 1:
                   {
                       tiles[y][x]->pieceName='b';
                       if(y<4)
                           tiles[y][x]->pieceColor='B';
                       else
                           tiles[y][x]->pieceColor='W';
                       break;
                   }
                   case 2:
                   {
                       tiles[y][x]->pieceName='k';
                       if(y<4)
                           tiles[y][x]->pieceColor='B';
                       else
                           tiles[y][x]->pieceColor='W';
                       break;
                   }
                   case 3:
                   {
                       tiles[y][x]->pieceName='p';
                       if(y<4)
                           tiles[y][x]->pieceColor='B';
                       else
                           tiles[y][x]->pieceColor='W';
                       break;
                   }
                   case 4:
                   {
                       tiles[y][x]->pieceName='q';
                       if(y<4)
                           tiles[y][x]->pieceColor='B';
                       else
                           tiles[y][x]->pieceColor='W';
                       break;
                   }
                   case 5:
                   {
                       tiles[y][x]->pieceName='r';
                       if(y<4)
                           tiles[y][x]->pieceColor='B';
                       else
                           tiles[y][x]->pieceColor='W';
                       break;
                   }
                   case 6:
                   {
                       tiles[y][x]->pieceName='K';
                       if(y<4)
                           tiles[y][x]->pieceColor='B';
                       else
                           tiles[y][x]->pieceColor='W';
                       kingIsSpawned=true;
                       break;
                   }
                   }
               }
            }

        }
    }

    if(mode==2){
        int BP = 0; //variable for number of black chess pieces spawned
        int WP = 0; //variable for number of white chess pieces spawned
        while(BP < 8 && WP < 8){
            bool wKingIsSpawned = false;
            bool bKingIsSpawned = false;
            bool allBPSpawned=false;
            bool allWPSpawned=false;
            int Pnumb;  //randomized int to determine type of chess piece
            int WBnumb; //randomized int for color of piece
            for(int x = 0; x < 8; x++){
                for(int y = 0; y < 8; y++){
                    if((BP==16 && bKingIsSpawned==true)||(WP==16 && wKingIsSpawned==true)){
                        if(BP==16){
                            allBPSpawned=true;
                        }else{
                            allWPSpawned=true;

                        }
                    }
                    //both kings are already spawned
                    if(wKingIsSpawned==true && bKingIsSpawned==true){
                        Pnumb= 1+rand()%10;
                        WBnumb= 1+rand()%2;
                        switch(Pnumb){
                        case 1:
                        {
                            tiles[y][x]->pieceName='b';
                            if(WBnumb==1&&allBPSpawned==false){
                                tiles[y][x]->pieceColor='B';
                                BP++;}
                            else if(WBnumb==2&&allWPSpawned==false){
                                tiles[y][x]->pieceColor='W';
                                WP++;
                            }
                            break;
                        }
                        case 2:
                        {
                            tiles[y][x]->pieceName='k';
                            if(WBnumb==1&&allBPSpawned==false){
                                tiles[y][x]->pieceColor='B';
                                BP++;}
                            else if (WBnumb==2&&allWPSpawned==false){
                                tiles[y][x]->pieceColor='W';
                                WP++;}
                            break;
                        }
                        case 3:
                        {
                            tiles[y][x]->pieceName='p';
                            if(WBnumb==1&&allBPSpawned==false){
                                tiles[y][x]->pieceColor='B';
                                BP++;}
                            else if(WBnumb==2&&allWPSpawned==false){
                                tiles[y][x]->pieceColor='W';
                                WP++;
                            }

                            break;
                        }
                        case 4:
                        {
                            tiles[y][x]->pieceName='q';
                            if(WBnumb==1 && allBPSpawned==false){
                                tiles[y][x]->pieceColor='B';
                                BP++;}
                            else if(WBnumb==2&&allWPSpawned==false){
                                tiles[y][x]->pieceColor='W';
                                WP++;}
                            break;
                        }
                        case 5:
                        {
                            tiles[y][x]->pieceName='r';
                            if(WBnumb==1 && allBPSpawned==false){
                                tiles[y][x]->pieceColor='B';
                                BP++;}
                            else if(WBnumb==2&&allWPSpawned==false){
                                tiles[y][x]->pieceColor='W';
                                WP++;}
                            break;
                        }
                        }

                    }

                    //emergency case if on last two spaces and neither king is spawned
                    else if(wKingIsSpawned==false && bKingIsSpawned==false && x==7 && y==6){
                        tiles[y][x]->pieceName='K';
                        tiles[y][x]->pieceColor='B';
                        bKingIsSpawned = true;
                        tiles[y+1][x]->pieceName='K';
                        tiles[y+1][x]->pieceColor='W';
                        wKingIsSpawned = true;
                        x++;
                        y++;
                    }
                    //if on last two spaces and one of kings is not spawned
                    else if((wKingIsSpawned==false || bKingIsSpawned==false) && x==7 && y==6){
                        if(wKingIsSpawned==false){
                            tiles[y][x]->pieceName='K';
                            tiles[y][x]->pieceColor='W';
                            wKingIsSpawned=true;
                        }else{
                            tiles[y][x]->pieceName='K';
                            tiles[y][x]->pieceColor='B';
                            bKingIsSpawned=true;
                        }
                    }

                    //not both kings are spawned and its not the last two spaces
                    else{
                        Pnumb= 1+rand()%10;
                        WBnumb= 1+rand()%2;
                        switch(Pnumb){
                        case 1:
                        {
                            tiles[y][x]->pieceName='b';
                            if(WBnumb==1 && allBPSpawned==false){
                                tiles[y][x]->pieceColor='B';
                                BP++;}
                            else if(WBnumb==2&&allWPSpawned==false){
                                tiles[y][x]->pieceColor='W';
                                WP++;
                            }
                            break;
                        }
                        case 2:
                        {
                            tiles[y][x]->pieceName='k';
                            if(WBnumb==1&&allBPSpawned==false){
                                tiles[y][x]->pieceColor='B';
                                BP++;}
                            else if(WBnumb==2&&allWPSpawned==false){
                                tiles[y][x]->pieceColor='W';
                                WP++;}
                            break;
                        }
                        case 3:
                        {
                            tiles[y][x]->pieceName='p';
                            if(WBnumb==1 && allBPSpawned==false){
                                tiles[y][x]->pieceColor='B';
                                BP++;}
                            else if(WBnumb==2&&allWPSpawned==false){
                                tiles[y][x]->pieceColor='W';
                                WP++;
                            }

                            break;
                        }
                        case 4:
                        {
                            tiles[y][x]->pieceName='q';
                            if(WBnumb==1&&allBPSpawned==false){
                                tiles[y][x]->pieceColor='B';
                                BP++;}
                            else if(WBnumb==2&&allWPSpawned==false){
                                tiles[y][x]->pieceColor='W';
                                WP++;}
                            break;
                        }
                        case 5:
                        {
                            tiles[y][x]->pieceName='r';
                            if(WBnumb==1&&allBPSpawned==false){
                                tiles[y][x]->pieceColor='B';
                                BP++;}
                            else if(WBnumb==2&&allWPSpawned==false){
                                tiles[y][x]->pieceColor='W';
                                WP++;}
                            break;
                        }
                        case 6:
                        {
                            tiles[y][x]->pieceName='K';
                            if(WBnumb==1 && allBPSpawned==false && bKingIsSpawned==false){
                                tiles[y][x]->pieceColor='B';
                                BP++;
                                bKingIsSpawned=true;}
                            else if(WBnumb==2&&allWPSpawned==false && wKingIsSpawned==false){
                                tiles[y][x]->pieceColor='W';
                                wKingIsSpawned=true;
                                WP++;}
                            break;
                        }
                    }

                }}
            }
        }
    }

    for(int y = 0; y < 8;y++){
        for(int x = 0; x < 8;x++){
            tiles[x][y]->pieceGeneration();

        }
    }
}

//changePixmap changes the pixmap of an element in tiles[][]. Usually this->setPixmap can be used but in certain circumstances it wouldn't work so changePixmap was created.
void squares::changePixmap(int row, int col, char piece, char color)
{
    tiles[row][col]->changePix(piece,color);
}

//function that takes a string and outputs it to either the first or second text box
void squares::editText(QString s, int m)
{
    if(m==1){
        moves->appendPlainText(s);
    }else if(m==2){
        messages->appendPlainText(s);
    }
}

//called repeatedly in the for loops of SquareHandler::validMove() to make sure the player isn't trying to jump over a piece
bool squares::checkForJump(int rows, int columns,int trow,int tcolumn)
{
    if(tiles[rows][columns]->pieceName!=' '){
        if(tiles[rows][columns]->row==trow&&tiles[rows][columns]->col==tcolumn){
            return false;
        }
        return true;
    }else{
        return false;
    }
}

//clears board of all pieces and sets all 8x8 squarehandler objects back to their defaults.
void squares::clearBoard()
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            tiles[i][j]->pieceName=' ';
            tiles[i][j]->pieceColor=' ';
            tiles[i][j]->setPixmap(QPixmap(":/other/resources/Clear.png"));
        }
    }
}


