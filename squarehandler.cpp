/* SquareHandler is the class that handles the functions and values for a single chess tile.
 * each SquareHandler object has local variables like the row, pieceName, pieceColor and has static variable
 * that need to be shared across all tiles of the board like the last clicked piece, color, row, and col.*/

#include "squarehandler.h"
#include <QDebug>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include "squares.h"

SquareHandler::SquareHandler(QWidget*)
{
}

SquareHandler::SquareHandler()
{

}

//called during squares::chessBoard(). simple function that just colors in the tiles and sets the color to change when the cursor hovers over the object
void SquareHandler::squareGeneration()
{
    if(this->tileColor=='B')
        this->setStyleSheet("QLabel {background-color: rgb(255, 211, 88);}:hover{background-color: rgb(139,107,19);}");
    else
        this->setStyleSheet("QLabel {background-color: rgb(185, 136, 0);}:hover{background-color: rgb(110,84,15);}");

}

//called during squares::chessPieces(). just like squareGeneration pieceGeneration is just displaying the item.
void SquareHandler::pieceGeneration()
{
    gameIsStarted=true;
    if(this->pieceColor=='W'){
        switch(this->pieceName)
        {
            case 'p':
                this->setPixmap(QPixmap(":/white/resources/white-pawn.png"));
                break;
            case 'r':
                this->setPixmap(QPixmap(":/white/resources/white-rook.png"));
                break;
            case 'k':
                this->setPixmap(QPixmap(":/white/resources/white-knight.png"));
                break;
            case 'K':
                this->setPixmap(QPixmap(":/white/resources/white-king.png"));
                break;
            case 'q':
                this->setPixmap(QPixmap(":/white/resources/white-queen.png"));
                break;
            case 'b':
                this->setPixmap(QPixmap(":/white/resources/white-bishop.png"));
                break;
        }
    }else if(this->pieceColor=='B'){
        switch(this->pieceName)
        {
            case 'p':
                this->setPixmap(QPixmap(":/black/resources/black-pawn.png"));
                break;
            case 'r':
                this->setPixmap(QPixmap(":/black/resources/black-rook.png"));
                break;
            case 'k':
                this->setPixmap(QPixmap(":/black/resources/black-knight.png"));
                break;
            case 'K':
                this->setPixmap(QPixmap(":/black/resources/black-king.png"));
                break;
            case 'q':
                this->setPixmap(QPixmap(":/black/resources/black-queen.png"));
                break;
            case 'b':
                this->setPixmap(QPixmap(":/black/resources/black-bishop.png"));
                break;
        }
    }
    else{
        this->setPixmap(QPixmap(":/other/resources/Clear.png"));
    }
}

//called on mouse click of any of the 64 squareHandler objects. different outcomes depending on if a piece is present and whether its a valid move
void SquareHandler::mousePressEvent(QMouseEvent *event)
{
    squares sq;
    if(gameIsStarted==true){
    if(event->buttons()==Qt::LeftButton){
        if(this->pieceName!=' '){
            if(this->fClick==true){
                if(this->pieceColor=='W' && wTurn==true){
                    fClick=false;
                    LCPieceColor=this->pieceColor;
                    LCPieceName=this->pieceName;
                    LCRow=this->row;
                    LCCol=this->col;
                    pieceColor=' ';
                    pieceName=' ';
                    this->setPixmap(QPixmap(":/other/resources/Clear.png"));
                    sq.editText("White piece selected for movement during white turn",2);
                }
                else if(this->pieceColor=='B' && wTurn==false){
                    fClick=false;
                    LCPieceColor=this->pieceColor;
                    LCPieceName=this->pieceName;
                    LCRow=this->row;
                    LCCol=this->col;
                    pieceColor=' ';
                    pieceName=' ';
                    this->setPixmap(QPixmap(":/other/resources/Clear.png"));
                    sq.editText("Black piece selected for movement during black turn",2);
                }
                else{
                    sq.editText("Can't move your opponents pieces",2);
                }
            }
            else{
                if((this->pieceColor=='W'&& wTurn==false)||(this->pieceColor=='B' && wTurn==true)){
                    if(validMove()){
                        if(this->pieceName=='K'){
                            sq.messages->clear();
                            sq.moves->clear();
                            sq.editText("You Eliminated The King! You Win",2);
                            changePix(LCPieceName,LCPieceColor);
                            pieceName=LCPieceName;
                            pieceColor=LCPieceColor;
                            fClick=true;
                            if(wTurn==false)
                                wTurn=true;
                             else
                                wTurn=false;
                            sq.clearBoard();

                        }else{
                            QString text;
                            sq.editText("You eliminated an enemy piece",2);
                            changePix(LCPieceName,LCPieceColor);
                            pieceName=LCPieceName;
                            pieceColor=LCPieceColor;
                            fClick=true;
                            text=returntype(this->pieceColor)+" " + returntype(this->pieceName) + " moved to column " + QString::number(this->col) + " and row " + QString::number(this->row) + " from column " + QString::number(LCCol) + " and row " + QString::number(LCRow);
                            sq.editText(text,1);
                            if(wTurn==false)
                                wTurn=true;
                             else
                                wTurn=false;
                        }
                    }else{
                        sq.editText("Not a valid move",2);
                    }

                }else{
                    sq.editText("You can't eliminate your own pieces!",2);
                }
            }
        }
        else{
            if(this->fClick==true){
                //if this condition is true this means the player hasn't selected a piece to move and is clicking a empty tile
                sq.editText("Can't Select empty tile",2);
            }

            //(second click) now we check if the player is using their first click or not
            else{
                if(this->row==LCRow&&this->col==LCCol){
                    sq.editText("Canceling selection",2);
                    fClick=true;
                    pieceName=LCPieceName;
                    pieceColor=LCPieceColor;
                    changePix(LCPieceName,LCPieceColor);
                }
                else if(validMove()){
                    QString text;
                    sq.editText("Moving your piece to a new tile",2);
                    changePix(LCPieceName,LCPieceColor);
                    pieceName=LCPieceName;
                    pieceColor=LCPieceColor;
                    fClick=true;
                    if(LCPieceColor=='W'){
                        wTurn=false;
                    }else{
                        wTurn=true;
                    }
                    text=returntype(this->pieceColor)+" " + returntype(this->pieceName) + " moved to column " + QString::number(this->col) + " and row " + QString::number(this->row) + " from column " + QString::number(LCCol) + " and row " + QString::number(LCRow);
                    sq.editText(text,1);

                }else{
                    sq.editText("Not a valid move",2);
                }
            }

        }
    }

    if(event->buttons()==Qt::RightButton){
        fClick=true;
        pieceName=LCPieceName;
        pieceColor=LCPieceColor;
        sq.changePixmap(LCRow,LCCol,LCPieceName,LCPieceColor);
    }
    }else{
        sq.editText("Game Is Not Started!",2);
    }
}

//called during mousePressEvent when player is trying to move a tile. if the player is trying to make a valid move it retursn true
bool SquareHandler::validMove()
{
    squares sq;
    if(LCPieceColor=='W'){
        switch(LCPieceName)
        {
            case 'p':{
                if(this->row==(LCRow-1)&&col==LCCol&&this->pieceName==' '){
                    return true;
                }else if(this->pieceName==' '){
                    return false;
                }else if(this->row==(LCRow-1)&&(this->col==(LCCol-1)||this->col==(LCCol+1))){
                    return true;
                }else{
                    return false;
                }
                    break;}
            case 'b':{
            for(int x=1;x<10;x++){
                if(LCCol+x>7||LCRow-x<0||sq.checkForJump(LCRow-x,LCCol+x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol+x&&this->row==LCRow-x){
                    return true;
                }

            }for(int x=1;x<10;x++){
                if(LCCol+x>7||LCRow+x>7||sq.checkForJump(LCRow+x,LCCol+x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol+x&&this->row==LCRow+x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol-x<0||LCRow+x>7||sq.checkForJump(LCRow+x,LCCol-x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol-x&&this->row==LCRow+x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol-x<0||LCRow-x<0||sq.checkForJump(LCRow-x,LCCol-x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol-x&&this->row==LCRow-x){
                    return true;
                }
            }
            return false;

            break;}
            case 'k':{
            if((this->row==(LCRow+2)||this->row==(LCRow-2))&&(this->col==(LCCol+1)||this->col==(LCCol-1))){
                return true;
            }else if((this->col==(LCCol+2)||this->col==(LCCol-2))&&(this->row==(LCRow+1)||this->row==(LCRow-1))){
                return true;
            }else{
            return false;
            }
                break;}
            case 'K':{
                if((this->col==(LCCol+1)||this->col==(LCCol-1))&&this->row==LCRow){
                    return true;
                }else if((this->row==(LCRow+1)||this->row==(LCRow-1))&&this->col==LCCol){
                    return true;
                }
                else if((this->row==(LCRow+1)||this->col==(LCCol+1)||this->col==(LCCol-1))){
                    return true;
                }
                else{
                    return false;
                }
                break;}
            case 'q':{
            for(int x=1;x<10;x++){
                if(LCCol+x>7||LCRow-x<0||sq.checkForJump(LCRow-x,LCCol+x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol+x&&this->row==LCRow-x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol+x>7||LCRow+x>7||sq.checkForJump(LCRow+x,LCCol+x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol+x&&this->row==LCRow+x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol-x<0||LCRow+x>7||sq.checkForJump(LCRow+x,LCCol-x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol-x&&this->row==LCRow+x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol-x<0||LCRow-x<0||sq.checkForJump(LCRow-x,LCCol-x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol-x&&this->row==LCRow-x){
                    return true;
                }
            } for(int x=1;x<10;x++){
                if(LCCol+x>7||sq.checkForJump(LCRow,LCCol+x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol+x&&this->row==LCRow){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCRow+x>7||sq.checkForJump(LCRow+x,LCCol,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol&&this->row==LCRow+x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol-x<0||sq.checkForJump(LCRow,LCCol-x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol-x&&this->row==LCRow){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCRow-x<0||sq.checkForJump(LCRow-x,LCCol,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol&&this->row==LCRow-x){
                    return true;
                }
            }
            return false;

            break;
            }
            case 'r':{
            for(int x=1;x<10;x++){
                if(LCCol+x>7||sq.checkForJump(LCRow,LCCol+x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol+x&&this->row==LCRow){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCRow+x>7||sq.checkForJump(LCRow+x,LCCol,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol&&this->row==LCRow+x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol-x<0||sq.checkForJump(LCRow,LCCol-x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol-x&&this->row==LCRow){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCRow-x<0||sq.checkForJump(LCRow-x,LCCol,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol&&this->row==LCRow-x){
                    return true;
                }
            }
            return false;
            break;
            }

        }
    }else{
        switch(LCPieceName)
        {
            case 'p':{
            if(this->row==(LCRow+1)&&col==LCCol&&this->pieceName==' '){
                return true;
            }else if(this->pieceName==' '){
                return false;
            }else if(this->row==(LCRow+1)&&(this->col==(LCCol-1)||this->col==(LCCol+1))){
                return true;
            }else{
                return false;
            }
                break;}
            case 'b':{
            for(int x=1;x<10;x++){
                if(LCCol+x>7||LCRow-x<0){
                    x=50;
                }else if(sq.checkForJump(LCRow-x,LCCol+x,this->row,this->col)){
                    x=50;
                }
                else if(this->col==LCCol+x&&this->row==LCRow-x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol+x>7||LCRow+x>7){
                    x=50;
                }else if(sq.checkForJump(LCRow+x,LCCol+x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol+x&&this->row==LCRow+x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol-x<0||LCRow+x>7){
                    x=50;
                }else if(sq.checkForJump(LCRow+x,LCCol-x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol-x&&this->row==LCRow+x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol-x<0||LCRow-x<0){
                    x=50;
                }else if(sq.checkForJump(LCRow-x,LCCol-x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol-x&&this->row==LCRow-x){
                    return true;
                }
            }
            return false;

            break;}
            case 'k':{
            if((this->row==(LCRow+2)||this->row==(LCRow-2))&&(this->col==(LCCol+1)||this->col==(LCCol-1))){
                return true;
            }else if((this->col==(LCCol+2)||this->col==(LCCol-2))&&(this->row==(LCRow+1)||this->row==(LCRow-1))){
                return true;
            }else{
            return false;
            }
                break;}
            case 'K':{
            if((this->col==(LCCol+1)||this->col==(LCCol-1))&&this->row==LCRow){
                qDebug()<< "Is this happening?";
                return true;
            }else if((this->row==(LCRow+1)||this->row==(LCRow-1))&&this->col==LCCol){
                return true;
            }
            else if((this->row==(LCRow+1)||this->col==(LCCol+1)||this->col==(LCCol-1))){
                return true;
            }
            else{
                return false;
            }
                break;}
            case 'q':{
            for(int x=1;x<10;x++){
                if(LCCol+x>7||LCRow-x<0||sq.checkForJump(LCRow-x,LCCol+x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol+x&&this->row==LCRow-x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol+x>7||LCRow+x>7||sq.checkForJump(LCRow+x,LCCol+x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol+x&&this->row==LCRow+x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol-x<0||LCRow+x>7||sq.checkForJump(LCRow+x,LCCol-x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol-x&&this->row==LCRow+x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol-x<0||LCRow-x<0||sq.checkForJump(LCRow-x,LCCol-x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol-x&&this->row==LCRow-x){
                    return true;
                }
            } for(int x=1;x<10;x++){
                if(LCCol+x>7||sq.checkForJump(LCRow,LCCol+x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol+x&&this->row==LCRow){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCRow+x>7||sq.checkForJump(LCRow+x,LCCol,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol&&this->row==LCRow+x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol-x<0||sq.checkForJump(LCRow,LCCol-x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol-x&&this->row==LCRow){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCRow-x<0||sq.checkForJump(LCRow-x,LCCol,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol&&this->row==LCRow-x){
                    return true;
                }
            }
            return false;

            break;
            }
            case 'r':{
            for(int x=1;x<10;x++){
                if(LCCol+x>7||sq.checkForJump(LCRow,LCCol+x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol+x&&this->row==LCRow){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCRow+x>7||sq.checkForJump(LCRow+x,LCCol,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol&&this->row==LCRow+x){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCCol-x<0||sq.checkForJump(LCRow,LCCol-x,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol-x&&this->row==LCRow){
                    return true;
                }
            }for(int x=1;x<10;x++){
                if(LCRow-x<0||sq.checkForJump(LCRow-x,LCCol,this->row,this->col)){
                    x=50;
                }else if(this->col==LCCol&&this->row==LCRow-x){
                    return true;
                }
            }
            return false;
            break;
            }

        }
    }
}

//function to change pixmap of an object. only used when the value to change it to isnt known
void SquareHandler::changePix(char piece,char color)
{
    if(color=='W'){
        switch(piece)
        {
        case 'p':
            this->setPixmap(QPixmap(":/white/resources/white-pawn.png"));
            break;
        case 'r':
            this->setPixmap(QPixmap(":/white/resources/white-rook.png"));
            break;
        case 'k':
            this->setPixmap(QPixmap(":/white/resources/white-knight.png"));
            break;
        case 'K':
            this->setPixmap(QPixmap(":/white/resources/white-king.png"));
            break;
        case 'q':
            this->setPixmap(QPixmap(":/white/resources/white-queen.png"));
            break;
        case 'b':
            this->setPixmap(QPixmap(":/white/resources/white-bishop.png"));
            break;
        case 'x':
            this->setPixmap(QPixmap(":/other/resources/Clear.png"));
            break;

        }
    }else if(color=='B'){
        switch(piece)
        {
        case 'p':
            this->setPixmap(QPixmap(":/black/resources/black-pawn.png"));
            break;
        case 'r':
            this->setPixmap(QPixmap(":/black/resources/black-rook.png"));
            break;
        case 'k':
            this->setPixmap(QPixmap(":/black/resources/black-knight.png"));
            break;
        case 'K':
            this->setPixmap(QPixmap(":/black/resources/black-king.png"));
            break;
        case 'q':
            this->setPixmap(QPixmap(":/black/resources/black-queen.png"));
            break;
        case 'b':
            this->setPixmap(QPixmap(":/black/resources/black-bishop.png"));
            break;
        case 'x':
            this->setPixmap(QPixmap(":/other/resources/Clear.png"));
            break;
        }
    }
}

//returns name of piece in QString instead of char so we can display it in message boxes
QString SquareHandler::returntype(char c)
{
    switch(c){
        case 'B':
            return "Black";
        case 'W':
            return "White";
        case 'p':
            return "pawn";
        case 'b':
            return "bishop";
        case 'k':
            return "knight";
        case 'r':
            return "rook";
        case 'K':
            return "king";
        case 'q':
            return "queen";
    }

}


