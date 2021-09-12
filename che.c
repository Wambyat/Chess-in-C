#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "displ.h"

//This array represents the chess board.
//Each element represents one chess piece or an empty space.
//0=>empty space
//if a number is negitive then it is white positive is black
//second digit meanings:
//1=>Pawn
//2=>Rook
//3=>Knight
//4=>Bishop
//5=>Queen
//6=>King
//Declared as global variable to allow easy access for all function especially for move checking(Coming Soon!)

int board[8][8]=
    {
        {2,3,4,5,6,4,3,2},
        {1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {-2,-3,-4,-5,-6,-4,-3,-2}
    };

/*
int board[8][8]=
    {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,-1,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,-6,0,0,0,0},
        {0,0,-2,6,0,0,0,0},
        {0,0,0,0,0,0,0,0}
    };
*/
int mo,ij;
int ca;
int captured_piece;

//This array is used to store all moves the pieces can move to
int moves[50];

//This array stores all the indexes of moves that the user can move to that also captures a piece.
int capture_indexes[50];

//This variable is used to clean moves and capture_index
int cleaner_var;

//Capture trigger variable
int captured;

//These variables store where user moves(temporary)
int choice1,choice2,mov1,mov2,bo2,turn;

//This function sees what piece has been selected and modifies the moves array to display where the piece can move
void move_finder();

//This function is the display function.
void disp();

//This function take the user inputs and converts them in to required input according to the matrix.
void input_function(int);

//This function prints all places piece can move to and then makes it zero
int move_checker();

//These variables accept the values.
char c[2],d[2];

//These 2 functions are to find bishop and rook moves(used for queen as well)
void bishopwhite();
void bishopblack();
void rookwhite();
void rookblack();

//This is the check function
int check_checker(int);

/*to delete later
void movedisp(int a)
{
        printf("\n%d ->",a);
        int b=a/10;
        int c=a%10;
        switch(c)
        {
                case 0:
                printf("a");
                break;
                case 1:
                printf("b");
                break;
                case 2:
                printf("c");
                break;
                case 3:
                printf("d");
                break;
                case 4:
                printf("e");
                break;
                case 5:
                printf("f");
                break;
                case 6:
                printf("g");
                break;
                case 7:
                printf("h");
                break;
                default:
                printf("?");
                break;
        }
        switch(b)
        {
                case 0:
                printf("8\n");
                break;
                case 1:
                printf("7\n");
                break;
                case 2:
                printf("6\n");
                break;
                case 3:
                printf("5\n");
                break;
                case 4:
                printf("4\n");
                break;
                case 5:
                printf("3\n");
                break;
                case 6:
                printf("2\n");
                break;
                case 7:
                printf("1\n");
                break;
                default:
                printf("?\n");
                break;
        }
}
*/
void main()
{
        welcome_splash();
        int del;
        for (del=0;del<50;del++)
        {
                moves[del]=-1;
                capture_indexes[del]=-1;
        }
        //This is just some code that saves the first value because c is wierd. 
        int bo2=board[0][0];

        //choice1 accepts number for selecting piece.
        //choice2 accepts letter for selecting piece.
        //mov1 accepts number for selecting position to move to.
        //mov2 accepts letter for selecting position to move to.
        int te,valid_checker=1;

        //if turn is 1 then black moves.
        //if turn is 2 then white moves.
        turn=2;
        captured=0;
        int checking=0;
        
        while(c[0]!='Z')
        {
                system("cls");
                if(captured_piece==6)
                {
                        system("cls");
                        printf("White wins!");
                        break;
                }
                else if(captured_piece==-6)
                {
                        system("cls");
                        printf("Black wins!");
                        break;
                }
                
                checking=check_checker(turn);
                if(checking==1)
                {
                        check_splash();
                }
                for(cleaner_var=0;cleaner_var<50;cleaner_var++)
                {
                        moves[cleaner_var]=-1;
                        capture_indexes[cleaner_var]=-1;
                }
                disp(board);

                //This is just some code that saves the first value because c is wierd. Reason it being used is because
                //C was deleting the first value of the lastest array that was accessed. I have no clue why this is happening 
                //but I know it is happening because of scanf.
                bo2=board[0][0];
                valid_checker=1;
                
                while(valid_checker==1)
                {
                        move_finder(2);  
                        valid_checker=move_checker(); 
                }

                //printf(" choice1,choice2-> %d,%d\n",choice1,choice2);
                //printf(" mov1,mov2-> %d,%d\n",mov1,mov2);
                board[0][0]=bo2;

                if (turn==2)
                {
                        turn=1;
                        //Refer comment on line 51 as this serves same function.
                        te=board[choice1][choice2];

                        if (captured==0)
                        {
                                board[choice1][choice2]=board[mov1][mov2]; 
                        }
                        else
                        {
                                captured_piece=board[mov1][mov2];
                                board[choice1][choice2]=0;
                        }
                        board[mov1][mov2]=te;
                        bo2=board[0][0];
                        captured=0;
                        for(cleaner_var=0;cleaner_var<50;cleaner_var++)
                        {
                                moves[cleaner_var]=-1;
                                capture_indexes[cleaner_var]=-1;
                        }
                        continue;
                }

                if (turn==1)
                {
                        turn=2;
                        //Refer comment on line 51 as this serves same function.
                        te=board[choice1][choice2];

                        if (captured==0)
                        {
                                board[choice1][choice2]=board[mov1][mov2]; 
                        }
                        else
                        {
                                captured_piece=board[mov1][mov2];
                                board[choice1][choice2]=0;
                        }
                        board[mov1][mov2]=te;
                        bo2=board[0][0];
                        captured=0;
                        for(cleaner_var=0;cleaner_var<50;cleaner_var++)
                        {
                                moves[cleaner_var]=-1;
                                capture_indexes[cleaner_var]=-1;
                        }
                }
        }
}

//This is a basic display function that prints the board. This part of the code will be replaced by the gui.
void disp()
{
        int j=0,i=0;
        //We use switch case because it's easy.
        for (i=0;i<=7;i++)
        {
                //This is for the number on the side of the board
                switch(i)
                {
                        case 0:
                                printf("8       ");
                                break;
                        case 1:
                                printf("7       ");
                                break;
                        case 2:
                                printf("6       ");
                                break;
                        case 3:
                                printf("5       ");
                                break;
                        case 4:
                                printf("4       ");
                                break;
                        case 5:
                                printf("3       ");
                                break;
                        case 6:
                                printf("2       ");
                                break;
                        case 7:
                                printf("1       ");
                                break;
                        default:
                                printf("");
                                break;
                        
                }
                for(j=0;j<=7;j++)
                {
                        //This is for displaying the pieces.
                        switch(board[i][j])
                        {
                                case 1: 
                                        printf("BPAWN   ");
                                        break;
                                case -1: 
                                        printf("WPAWN   ");
                                        break;
                                case 2:
                                        printf("BROOK   ");
                                        break;
                                case -2:
                                        printf("WROOK   ");
                                        break;
                                case 3:
                                        printf("BKNIGHT ");
                                        break;
                                case -3:
                                        printf("WKNIGHT ");
                                        break;
                                case 4:
                                        printf("BBISHOP ");
                                        break;
                                case -4:
                                        printf("WBISHOP ");
                                        break;
                                case 5:
                                        printf("BQUEEN  ");
                                        break;
                                case -5:
                                        printf("WQUEEN  ");
                                        break;
                                case 6:
                                        printf("BKING   ");
                                        break;
                                case -6:
                                        printf("WKING   ");
                                        break;
                                default: 
                                        printf("  -     "); 
                        }
                }
                printf("\n\n");
        }
        //This is for displaying the letter on the bottom 
        printf("          A       B       C       D       E       F       G       H    \n");
}

//This fixes the inputs by the user cuz array is different.
void input_function(int inputvar)
{
        bo2=board[0][0];
        if (inputvar==0)
        {
                printf("Select piece to be move-> ");
                scanf("%s",c);

                board[0][0]=bo2;
                choice2=c[0]-65;
                choice1=c[1]-49;
                switch(choice1)
                {
                        case 0:
                                choice1=7;
                                break;
                        case 1:
                                choice1=6;
                                break;
                        case 2:
                                choice1=5;
                                break;
                        case 3:
                                choice1=4;
                                break;
                        case 4:
                                choice1=3;
                                break;
                        case 5:
                                choice1=2;
                                break;
                        case 6:
                                choice1=1;
                                break;
                        case 7:
                                choice1=0;
                                break;
                        default:
                                choice1=10;
                                break;
                }
        }
        else
        {
                printf("Move piece to-> ");
                scanf("%s",d);

                board[0][0]=bo2;
                mov2=d[0]-65;
                mov1=d[1]-49;
                switch(mov1)
                {
                        case 0:
                                mov1=7;
                                break;
                        case 1:
                                mov1=6;
                                break;
                        case 2:
                                mov1=5;
                                break;
                        case 3:
                                mov1=4;
                                break;
                        case 4:
                                mov1=3;
                                break;
                        case 5:
                                mov1=2;
                                break;
                        case 6:
                                mov1=1;
                                break;
                        case 7:
                                mov1=0;
                                break;
                        default:
                                mov1=10;
                                break;
                }
        }
}
void move_finder(int test)
{
        if (test==2)
        {
                input_function(0);
        }
        //printf("In move\n");
        mo=0;
        ca=0;
        //printf("%d %d \n",choice1,choice2);
        switch(board[choice1][choice2])
        {
                case 1:
                        if(turn!=1)
                        {
                                system("cls");
                                disp(board);
                                printf("Please choose a white piece because it is white's turn.\n");
                                move_finder(2);
                                break;
                        }
                        
                        if(board[choice1+1][choice2]==0)
                        {
                                moves[mo]=((choice1+1)*10)+choice2;
                                mo++;
                                if(choice1==1)
                                {
                                        if(board[choice1+2][choice2]==0)
                                        {
                                                moves[mo]=30+choice2;
                                                mo++;
                                        }
                                }
                        }
                        if(choice2!=7)
                        {
                                if(board[choice1+1][choice2+1]<0)
                                {
                                        moves[mo]=((choice1+1)*10)+choice2+1;
                                        capture_indexes[ca]=mo;
                                        ca++;
                                        mo++;
                                }
                        }
                        if (choice2!=0)
                        {
                                if(board[choice1+1][choice2-1]<0)
                                {
                                        moves[mo]=((choice1+1)*10)+choice2-1;
                                        capture_indexes[ca]=mo;
                                        ca++;
                                        mo++;
                                }
                        }
                        ij=mo;
                        mo=0;
                        break;
                case -1: 
                        if(turn!=2)
                        {
                                system("cls");
                                disp(board);
                                printf("Please choose a black piece because it is black's turn.\n");
                                move_finder(2);
                                break;
                        }
                        mo=0;

                        if(board[choice1-1][choice2]==0)
                        {
                                moves[mo]=((choice1-1)*10)+choice2;
                                mo++;
                                if(choice1==6)
                                {
                                        if(board[choice1-2][choice2]==0)
                                        {
                                                moves[mo]=40+choice2;
                                                mo++;
                                        }
                                }
                        }
                        if(choice2!=7)
                        {
                                if(board[choice1-1][choice2+1]>0)
                                {
                                        moves[mo]=((choice1-1)*10)+choice2+1;
                                        capture_indexes[ca]=mo;
                                        ca++;
                                        mo++;
                                }
                        }
                        if (choice2!=0)
                        {
                                if(board[choice1-1][choice2-1]>0)
                                {
                                        moves[mo]=((choice1-1)*10)+choice2-1;
                                        capture_indexes[ca]=mo;
                                        ca++;
                                        mo++;
                                }
                        }
                        ij=mo;
                        mo=0;
                        break;
                case 2:
                        if(turn!=1)
                        {
                                system("cls");
                                disp(board);
                                printf("Please choose a white piece because it is white's turn.\n");
                                move_finder(2);
                                break;
                        }
                        else
                        {
                               rookblack();
                        }
                        ij=mo;
                        mo=0;
                        break;
                case -2:
                        if(turn!=2)
                        {
                                system("cls");
                                disp(board);
                                printf("Please choose a black piece because it is black's turn.\n");
                                move_finder(2);
                                break;
                        }
                        else
                        {
                                rookwhite();
                        }
                        ij=mo;
                        mo=0;
                        break;
                case 3:
                        if(turn!=1)
                        {
                                system("cls");
                                disp(board);
                                printf("Please choose a white piece because it is white's turn.\n");
                                move_finder(2);
                                break;
                        }
                        else
                        {
                                int a[8];
                                int b[8];
                                a[0]=choice1-1;
                                b[0]=choice2-2;
                                a[1]=choice1+1;
                                b[1]=choice2+2;
                                a[2]=choice1+1;
                                b[2]=choice2-2;
                                a[3]=choice1-1;
                                b[3]=choice2+2;
                                a[4]=choice1-2;
                                b[4]=choice2-1;
                                a[5]=choice1+2;
                                b[5]=choice2+1;
                                a[6]=choice1+2;
                                b[6]=choice2-1;
                                a[7]=choice1-2;
                                b[7]=choice2+1;
                                int cho;
                                for(cho=0;cho<8;cho++)
                                {
                                        if(a[cho]<0 || a[cho]>7 || b[cho]<0 || b[cho]>7)
                                        {
                                                continue;
                                        }
                                        if (board[a[cho]][b[cho]]==0)
                                        {
                                                moves[mo]=(a[cho]*10)+b[cho];
                                                mo++;
                                        }
                                        if (board[a[cho]][b[cho]]<0)
                                        {
                                                moves[mo]=(a[cho]*10)+b[cho];
                                                capture_indexes[ca]=mo;
                                                ca++;
                                                mo++;
                                        }
                                }
                        }
                        ij=mo;
                        mo=0;
                        break;
                case -3:
                        if(turn!=2)
                        {
                                system("cls");
                                disp(board);
                                printf("Please choose a black piece because it is black's turn.\n");
                                move_finder(2);
                                break;
                        }
                        else
                        {
                                int a[8];
                                int b[8];
                                a[0]=choice1-1;
                                b[0]=choice2-2;
                                a[1]=choice1+1;
                                b[1]=choice2+2;
                                a[2]=choice1+1;
                                b[2]=choice2-2;
                                a[3]=choice1-1;
                                b[3]=choice2+2;
                                a[4]=choice1-2;
                                b[4]=choice2-1;
                                a[5]=choice1+2;
                                b[5]=choice2+1;
                                a[6]=choice1+2;
                                b[6]=choice2-1;
                                a[7]=choice1-2;
                                b[7]=choice2+1;
                                int cho;
                                for(cho=0;cho<8;cho++)
                                {
                                        if(a[cho]<0 || a[cho]>7 || b[cho]<0 || b[cho]>7)
                                        {
                                                continue;
                                        }
                                        if (board[a[cho]][b[cho]]==0)
                                        {
                                                moves[mo]=(a[cho]*10)+b[cho];
                                                mo++;
                                        }
                                        if (board[a[cho]][b[cho]]>0)
                                        {
                                                moves[mo]=(a[cho]*10)+b[cho];
                                                capture_indexes[ca]=mo;
                                                ca++;
                                                mo++;
                                        }
                                }
                        }
                        ij=mo;
                        mo=0;
                        break;
                case 4:
                        if(turn!=1)
                        {
                                system("cls");
                                disp(board);
                                printf("Please choose a white piece because it is white's turn.\n");
                                move_finder(2);
                                break;
                        }
                        else
                        {
                                bishopblack();
                        }
                        ij=mo;
                        mo=0;
                        break;
                case -4:
                        if(turn!=2)
                        {
                                system("cls");
                                disp(board);
                                printf("Please choose a black piece because it is black's turn.\n");
                                move_finder(2);
                                break;
                        }
                        else
                        {
                                bishopwhite();
                        }
                        ij=mo;
                        mo=0;
                        break;
                case 5:
                        if(turn!=1)
                        {
                                system("cls");
                                disp(board);
                                printf("Please choose a white piece because it is white's turn.\n");
                                move_finder(2);
                                break;
                        }
                        else
                        {
                                bishopblack();
                                rookblack();
                                ij=mo;
                                mo=0;
                        }
                        break;
                case -5:
                        if(turn!=2)
                        {
                                system("cls");
                                disp(board);
                                printf("Please choose a black piece because it is black's turn.\n");
                                move_finder(2);
                                break;
                        }
                        else
                        {
                                bishopwhite();
                                rookwhite();
                                ij=mo;
                                mo=0;
                        }
                        break;
                case 6:
                        if(turn!=1)
                        {
                                system("cls");
                                disp(board);
                                printf("Please choose a white piece because it is white's turn.\n");
                                move_finder(2);
                                break;
                        }
                        else
                        {
                                for(int i=-1;i<2;i++)
                                {
                                        for (int j=-1;j<2;j++)
                                        {
                                                if((choice1+i)!=-1 && (choice1+i)!=8 && (choice2+j)!=-1 && (choice2+j)!=8)
                                                {
                                                        if(board[choice1+i][choice2+j]==0)
                                                        {
                                                                moves[mo]=((choice1+i)*10)+(choice2+j);
                                                                mo++;
                                                        }
                                                        if(board[choice1+i][choice2+j]<0)
                                                        {
                                                                moves[mo]=((choice1+i)*10)+(choice2+j);
                                                                capture_indexes[ca]=mo;
                                                                ca++;
                                                                mo++;
                                                        }
                                                }
                                        }
                                }
                        }
                        ij=mo;
                        mo=0;
                        break;
                case -6:
                        if(turn!=2)
                        {
                                system("cls");
                                disp(board);
                                printf("Please choose a black piece because it is black's turn.\n");
                                move_finder(2);
                                break;
                        }
                        else
                        {
                                for(int i=-1;i<2;i++)
                                {
                                        for (int j=-1;j<2;j++)
                                        {
                                                if((choice1+i)!=-1 && (choice1+i)!=8 && (choice2+j)!=-1 && (choice2+j)!=8)
                                                {
                                                        if(board[choice1+i][choice2+j]==0)
                                                        {
                                                                moves[mo]=((choice1+i)*10)+(choice2+j);
                                                                mo++;
                                                        }
                                                        if(board[choice1+i][choice2+j]>0)
                                                        {
                                                                moves[mo]=((choice1+i)*10)+(choice2+j);
                                                                capture_indexes[ca]=mo;
                                                                ca++;
                                                                mo++;
                                                        }
                                                }
                                        }
                                }
                        }
                        ij=mo;
                        mo=0;
                        break;
                default: 
                        system("cls");
                        disp(board);
                        printf("Blank Space selected, choose valid space.\n");
                        move_finder(2);
                        break;
        }
}

int move_checker()
{
        int checker;
        input_function(1);
        if (moves[ij]==-1)
        {
                checker=(mov1*10)+mov2;
                //printf("To move-> %d\n ",checker);
                if(ij==0)
                {
                        printf("No Moves available.\n");
                        return 1;
                }
                while(ij!=0)
                {
                        //asd is used to loop thru the moves
                        int asd;
                        //printf("%d",ij);
                        for(asd=0;asd<ij;asd++)
                        {
                                //movedisp(moves[asd]);
                                if(moves[asd]==checker)
                                {
                                        //printf("?   %d , %d, %d",moves[asd],checker,asd);
                                        ij=0;
                                }
                                if(capture_indexes[asd]!=-1)
                                {
                                        if(moves[capture_indexes[asd]]==checker)
                                        {
                                                //printf("\n%d\n",moves[capture_indexes[asd]]);
                                                ij=0;
                                                //printf("\n?  %d , %d, %d",moves[capture_indexes[asd]],checker,asd);
                                                //printf("Capturing something!\n");
                                                captured=1;
                                        }
                                }
                        }
                        if(ij!=0)
                        {
                                printf("Not a valid spot, choose again\n");
                                for(cleaner_var=0;cleaner_var<50;cleaner_var++)
                                {
                                        moves[cleaner_var]=-1;
                                        capture_indexes[cleaner_var]=-1;
                                }
                                return 1;
                        }
                }
                return 0;
        }
        return 0;
}

void bishopwhite()
{
        int re;
        for(re=1;re<8;re++)
        {
                if(re+choice1==8 || re+choice2==8)
                {
                        break;
                }
                if(board[re+choice1][re+choice2]==0)
                {
                        moves[mo]=((re+choice1)*10)+(re+choice2);
                        mo++;
                }
                if(board[re+choice1][re+choice2]>0)
                {
                        moves[mo]=((re+choice1)*10)+(re+choice2);
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[re+choice1][re+choice2]<0)
                {
                        break;
                }
        }
        for(re=1;re<8;re++)
        {
                if(re+choice1==8 || choice2-re==-1)
                {
                        break;
                }
                if(board[re+choice1][choice2-re]==0)
                {
                        moves[mo]=((re+choice1)*10)+(choice2-re);
                        mo++;
                }
                if(board[re+choice1][choice2-re]>0)
                {
                        moves[mo]=((re+choice1)*10)+(choice2-re);
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[re+choice1][choice2-re]<0)
                {
                        break;
                }
        }
        for(re=1;re<8;re++)
        {
                if(choice1-re==-1 || choice2-re==-1)
                {
                        break;
                }
                if(board[choice1-re][choice2-re]==0)
                {
                        moves[mo]=((choice1-re)*10)+(choice2-re);
                        mo++;
                }
                if(board[choice1-re][choice2-re]>0)
                {
                        moves[mo]=((choice1-re)*10)+(choice2-re);
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[choice1-re][choice2-re]<0)
                {
                        break;
                }
        }
        for(re=1;re<8;re++)
        {
                if(choice1-re==-1 || re+choice2==8)
                {
                        break;
                }
                if(board[choice1-re][re+choice2]==0)
                {
                        moves[mo]=((choice1-re)*10)+(re+choice2);
                        mo++;
                }
                if(board[choice1-re][re+choice2]>0)
                {
                        moves[mo]=((choice1-re)*10)+(re+choice2);
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[choice1-re][re+choice2]<0)
                {
                        break;
                }
        }
}
void bishopblack()
{
        int re;
        for(re=1;re<8;re++)
        {
                if(re+choice1==8 || re+choice2==8)
                {
                        break;
                }
                if(board[re+choice1][re+choice2]==0)
                {
                        moves[mo]=((re+choice1)*10)+(re+choice2);
                        mo++;
                }
                if(board[re+choice1][re+choice2]<0)
                {
                        moves[mo]=((re+choice1)*10)+(re+choice2);
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[re+choice1][re+choice2]>0)
                {
                        break;
                }
        }
        for(re=1;re<8;re++)
        {
                if(re+choice1==8 || choice2-re==-1)
                {
                        break;
                }
                if(board[re+choice1][choice2-re]==0)
                {
                        moves[mo]=((re+choice1)*10)+(choice2-re);
                        mo++;
                }
                if(board[re+choice1][choice2-re]<0)
                {
                        moves[mo]=((re+choice1)*10)+(choice2-re);
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[re+choice1][choice2-re]>0)
                {
                        break;
                }
        }
        for(re=1;re<8;re++)
        {
                if(choice1-re==-1 || choice2-re==-1)
                {
                        break;
                }
                if(board[choice1-re][choice2-re]==0)
                {
                        moves[mo]=((choice1-re)*10)+(choice2-re);
                        mo++;
                }
                if(board[choice1-re][choice2-re]<0)
                {
                        moves[mo]=((choice1-re)*10)+(choice2-re);
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[choice1-re][choice2-re]>0)
                {
                        break;
                }
        }
        for(re=1;re<8;re++)
        {
                if(choice1-re==-1 || re+choice2==8)
                {
                        break;
                }
                if(board[choice1-re][re+choice2]==0)
                {
                        moves[mo]=((choice1-re)*10)+(re+choice2);
                        mo++;
                }
                if(board[choice1-re][re+choice2]<0)
                {
                        moves[mo]=((choice1-re)*10)+(re+choice2);
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[choice1-re][re+choice2]>0)
                {
                        break;
                }
        }
}
void rookwhite()
{
int re;
        for(re=choice1+1;re<8;re++)
        {
                if(board[re][choice2]==0)
                {
                        moves[mo]=(re*10)+choice2;
                        mo++;
                }
                if(board[re][choice2]>0)
                {
                        moves[mo]=(re*10)+choice2;
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[re][choice2]<0)
                {
                        break;
                }
        }
        for(re=choice1-1;re>-1;re--)
        {
                if(board[re][choice2]==0)
                {
                        moves[mo]=(re*10)+choice2;
                        mo++;
                }
                if(board[re][choice2]>0)
                {
                        moves[mo]=(re*10)+choice2;
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[re][choice2]<0)
                {
                        break;
                }
        }
        for(re=choice2+1;re<8;re++)
        {
                if(board[choice1][re]==0)
                {
                        moves[mo]=(choice1*10)+re;
                        mo++;
                }
                if(board[choice1][re]>0)
                {
                        moves[mo]=(choice1*10)+re;
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[choice1][re]<0)
                {
                        break;
                }
        }
        for(re=choice2-1;re>-1;re--)
        {
                if(board[choice1][re]==0)
                {
                        moves[mo]=(choice1*10)+re;
                        mo++;
                }
                if(board[choice1][re]>0)
                {
                        moves[mo]=(choice1*10)+re;
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[choice1][re]<0)
                {
                        break;
                }
        }
}

void rookblack()
{
        int re;
        for(re=choice1+1;re<8;re++)
        {
                if(board[re][choice2]==0)
                {
                        moves[mo]=(re*10)+choice2;
                        mo++;
                }
                if(board[re][choice2]<0)
                {
                        moves[mo]=(re*10)+choice2;
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[re][choice2]>0)
                {
                        break;
                }
        }
        for(re=choice1-1;re>-1;re--)
        {
                if(board[re][choice2]==0)
                {
                        moves[mo]=(re*10)+choice2;
                        mo++;
                }
                if(board[re][choice2]<0)
                {
                        moves[mo]=(re*10)+choice2;
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[re][choice2]>0)
                {
                        break;
                }
        }
        for(re=choice2+1;re<8;re++)
        {
                if(board[choice1][re]==0)
                {
                        moves[mo]=(choice1*10)+re;
                        mo++;
                }
                if(board[choice1][re]<0)
                {
                        moves[mo]=(choice1*10)+re;
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[choice1][re]>0)
                {
                        break;
                }
        }
        for(re=choice2-1;re>-1;re--)
        {
                if(board[choice1][re]==0)
                {
                        moves[mo]=(choice1*10)+re;
                        mo++;
                }
                if(board[choice1][re]<0)
                {
                        moves[mo]=(choice1*10)+re;
                        capture_indexes[ca]=mo;
                        ca++;
                        mo++;
                        break;
                }
                if(board[choice1][re]>0)
                {
                        break;
                }
        }
}

int check_checker(int cond)
{
        if(turn==1)
        {     
                int imp,i2,j2;
                for(int i=0;i<8;i++)
                {
                        for(int j=0;j<8;j++)
                        {
                                if(board[i][j]==6)
                                {
                                        imp=(i*10)+j;
                                        board[i][j]=5;
                                        i2=i;
                                        j2=j;
                                        break;
                                }
                        }
                }
                choice1=i2;
                choice2=j2;
                move_finder(1);
                if(capture_indexes[0]!=-1)
                {
                        board[i2][j2]=6;
                        return 1;
                }
                board[i2][j2]=3;
                move_finder(1);
                if(capture_indexes[0]!=-1)
                {
                        board[i2][j2]=6;
                        return 1;
                }
                board[i2][j2]=6;
                return 0;
        }
        else
        {     
                int imp,i2,j2;
                for(int i=0;i<8;i++)
                {
                        for(int j=0;j<8;j++)
                        {
                                if(board[i][j]==-6)
                                {
                                        imp=(i*10)+j;
                                        board[i][j]=-5;
                                        i2=i;
                                        j2=j;
                                        break;
                                }
                        }
                }
                choice1=i2;
                choice2=j2;
                move_finder(1);
                if(capture_indexes[0]!=-1)
                {
                        board[i2][j2]=-6;
                        return 1;
                }
                board[i2][j2]=-3;
                move_finder(1);
                if(capture_indexes[0]!=-1)
                {
                        board[i2][j2]=-6;
                        return 1;
                }
                board[i2][j2]=-6;
                return 0;
        }
}
