#include "widget.h"

#include <QMouseEvent>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setGeometry(500, 50, 200*width+130, 200*height+130);

    QLabel *ticTacToe = new QLabel(this);
    ticTacToe->setText("Tic-Tac-Toe");
    ticTacToe->setStyleSheet("font-weight: bold; font: 30pt");
    ticTacToe->setGeometry(10, 10, width*200, 50);
    ticTacToe->setAlignment(Qt::AlignCenter);

    output = new QLabel(this);
    output->setText("Player 1's Turn");
    output->setStyleSheet("font-weight: bold; font: 20pt");
    output->setGeometry(10, 60, width*200, 50);
    output->setAlignment(Qt::AlignCenter);

    newGame = new QPushButton(this);
    newGame->setGeometry(200*width+20, 120, 100, 40);
    newGame->setText("New Game");
    newGame->setStyleSheet("font: 9pt; font-weight: bold");

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            BoardObject *o = new BoardObject(this);
            o->move(200*x+10, 200*y+120);
            o->show();
            connect(o, SIGNAL(iwaschanged(ObjectState)), this, SLOT(objectChanged(ObjectState)));
            connect(newGame, SIGNAL(clicked()), o, SLOT(clear()));
            connect(this, SIGNAL(nextState(ObjectState)), o, SLOT(nextState(ObjectState)));
            connect(this, SIGNAL(gameOver()), o, SLOT(makeGameOver()));
            board[x][y] = o;
        }
    }

    connect(newGame, SIGNAL(clicked()), this, SLOT(clear()));

    setMinimumSize(200*width+130, 200*height+130);
}

Widget::~Widget()
{
}

void Widget::objectChanged(ObjectState prevState)
{
    ObjectState winner;
    bool win = false;

    for (int y = 0; y < height; ++y)
    {
        bool fullRow = true;
        for (int x = 1; x < width; ++x)
        {
            if (board[x-1][y]->state() != board[x][y]->state())
            {
                fullRow = false;
                break;
            }
        }
        if (fullRow && (board[0][y]->state() != blank))
        {
            win = true;
            winner = board[0][y]->state();
            break;
        }
    }

    for (int x = 0; x < width; ++x)
    {
        bool fullColumn = true;
        for (int y = 1; y < height; ++y)
        {
            if (board[x][y-1]->state() != board[x][y]->state())
            {
                fullColumn = false;
                break;
            }
        }
        if (fullColumn && (board[x][0]->state() != blank))
        {
            win = true;
            winner = board[x][0]->state();
            break;
        }
    }

    bool fullDiagonal1 = true;
    for (int y = 1; y < height; ++y)
    {
        if (board[y-1][y-1]->state() != board[y][y]->state())
        {
            fullDiagonal1 = false;
            break;
        }
    }
    if (fullDiagonal1 && (board[0][0]->state() != blank))
    {
        win = true;
        winner = board[0][0]->state();
    }

    bool fullDiagonal2 = true;
    for (int y = 1; y < height; ++y)
    {
        if (board[width-y][y-1]->state() != board[width-y-1][y]->state())
        {
            fullDiagonal2 = false;
            break;
        }
    }
    if (fullDiagonal2 && (board[width-1][0]->state() != blank))
    {
        win = true;
        winner = board[width-1][0]->state();
    }

    if (prevState == O)
    {
        emit nextState(X);
        output->setText("Player 1's Turn");
    }
    else if (prevState == X)
    {
        emit nextState(O);
        output->setText("Player 2's Turn");
    }
    else
    {
        emit nextState(X);
        output->setText("Player 1's Turn");
    }


    if (win)
    {
        if (winner == 1)
            output->setText("Player 1 Wins!!");

        else if (winner == 2)
            output->setText("Player 2 Wins!!");

        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
                gameOver();
    }

    bool tie = true;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (board[x][y]->state() == blank)
            {
                tie = false;
                break;
            }
        }
        if (!tie)
            break;
    }

    if (tie && !win)
        output->setText("It's a Tie!!");
}

void Widget::clear()
{
    output->setText("Player 1's Turn");

}
