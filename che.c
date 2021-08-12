#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//This array represents the chess board.
//Each element represents one chess piece or an empty space.
//0=>empty space
//if a number starts with one then it is black if it starts with 2 then white
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
        {12,13,14,15,16,14,13,12},
        {0,11,11,11,11,11,11,11},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,12,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {21,21,21,21,21,21,21,21},
        {22,23,24,25,26,24,23,22}
    };

//This array is used to store all moves the pieces can move to
int moves[50];

//This array stores all the indexes of moves that the user can move to that also captures a piece.
int capture_indexes[50];

//Capture trigger variable
int captured;

//These variables store where user moves(temporary)
int choice1,choice2,mov1,mov2,bo2,turn;

//This function sees what piece has been selected and modifies the moves array to display where the piece can move
void move_finder();

//This function is a stand-in for the gui. It will be replaced by the gui part of the project.
void disp();

//This function take the user inputs and converts them in to required input according to the matrix.
void input_function(int);

//This function prints all places piece can move to and then makes it zero
int move_checker();

//These variables accept the values.
char c[2],d[2];

void main()
{
        int del;
        for (del=0;del<50;del++)
        {
                moves[del]=0;
                capture_indexes[del]=0;
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
        while(c[0]!='Z')
        {
                disp(board);
                //This is just some code that saves the first value because c is wierd. Reason it being used is because
                //C was deleting the first value of the lastest array that was accessed. I have no clue why this is happening 
                //but I know it is happening because of scanf.
                bo2=board[0][0];
                valid_checker=1;
                
                while(valid_checker==1)
                {
                        move_finder();  
                        valid_checker=move_checker(); 
                }

                printf(" choice1,choice2-> %d,%d\n",choice1,choice2);
                printf(" mov1,mov2-> %d,%d\n",mov1,mov2);
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
                                board[choice1][choice2]=0;
                        }
                        board[mov1][mov2]=te;
                        bo2=board[0][0];
                        captured=0;
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
                                board[choice1][choice2]=0;
                        }
                        board[mov1][mov2]=te;
                        bo2=board[0][0];
                        captured=0;
                }
        }
        
        //ignore code from line 96 to 105 it is there for easy debugging
        /*
        int i2=0,j2=0;
        for(i2=0;i2<=7;i2++)
        {
                for (j2=0;j2<=7;j2++)
                {
                        printf("%d",board[i2][j2]);
                }
                printf("\n");
        }
        disp(board);
        */
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
                                case 11: 
                                        printf("BPAWN   ");
                                        break;
                                case 21: 
                                        printf("WPAWN   ");
                                        break;
                                case 12:
                                        printf("BROOK   ");
                                        break;
                                case 22:
                                        printf("WROOK   ");
                                        break;
                                case 13:
                                        printf("BKNIGHT ");
                                        break;
                                case 23:
                                        printf("WKNIGHT ");
                                        break;
                                case 14:
                                        printf("BBISHOP ");
                                        break;
                                case 24:
                                        printf("WBISHOP ");
                                        break;
                                case 15:
                                        printf("BQUEEN  ");
                                        break;
                                case 25:
                                        printf("WQUEEN  ");
                                        break;
                                case 16:
                                        printf("BKING   ");
                                        break;
                                case 26:
                                        printf("WKING   ");
                                        break;
                                default: 
                                        printf("  -     "); 
                        }
                }
                printf("\n");
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
                printf("Select piece to be move? :");
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
                printf("Move selected piece to ? :");
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
void move_finder()
{
        input_function(0);
        printf("In move\n");
        int mo,c;
        mo=0;
        c=0;
        printf("%d %d \n",choice1,choice2);
        switch(board[choice1][choice2])
        {
                case 11:
                        if(turn!=1)
                        {
                                printf("Please choose a white piece because it is white's turn.\n");
                                move_finder();
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
                                if(board[choice1+1][choice2+1]>20)
                                {
                                        moves[mo]=((choice1+1)*10)+choice2+1;
                                        capture_indexes[c]=mo;
                                        printf("CAP\n");
                                        c++;
                                        mo++;
                                }
                        }
                        if (choice2!=0)
                        {
                                if(board[choice1+1][choice2-1]>20)
                                {
                                        moves[mo]=((choice1+1)*10)+choice2-1;
                                        capture_indexes[c]=mo;
                                        printf("CAP\n");
                                        c++;
                                        mo++;
                                }
                        }
                        mo=0;
                        break;
                case 21: 
                        if(turn!=2)
                        {
                                printf("Please choose a black piece because it is black's turn.\n");
                                move_finder();
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
                                if(board[choice1-1][choice2+1]<20 && board[choice1-1][choice2+1]!=0)
                                {
                                        moves[mo]=((choice1-1)*10)+choice2+1;
                                        capture_indexes[c]=mo;
                                        printf("CAP\n");
                                        c++;
                                        mo++;
                                }
                        }
                        if (choice2!=0)
                        {
                                if(board[choice1-1][choice2-1]<20 && board[choice1-1][choice2-1]!=0)
                                {
                                        moves[mo]=((choice1-1)*10)+choice2-1;
                                        capture_indexes[c]=mo;
                                        printf("CAP\n");
                                        c++;
                                        mo++;
                                }
                        }
                        mo=0;
                        break;
                case 12:
                        if(turn!=1)
                        {
                                printf("Please choose a white piece because it is white's turn.\n");
                                move_finder();
                                break;
                        }
                        else
                        {
                               int re;
                               for(re=choice1+1;re<8;re++)
                               {
                                       if(board[re][choice2]==0)
                                       {
                                               printf("ED ");
                                               moves[mo]=(re*10)+choice2;
                                               mo++;
                                       }
                                       if(board[re][choice2]>20)
                                       {
                                               printf("WD ");
                                               moves[mo]=(re*10)+choice2;
                                               capture_indexes[c]=mo;
                                               c++;
                                               mo++;
                                               break;
                                       }
                                       if(board[re][choice2]<20 && board[re][choice2]!=0)
                                       {
                                               printf("BD ");
                                               break;
                                       }
                               }
                               for(re=choice1-1;re>-1;re--)
                               {
                                       if(board[re][choice2]==0)
                                       {
                                               printf("EU ");
                                               moves[mo]=(re*10)+choice2;
                                               mo++;
                                       }
                                       if(board[re][choice2]>20)
                                       {
                                               printf("WU ");
                                               moves[mo]=(re*10)+choice2;
                                               capture_indexes[c]=mo;
                                               c++;
                                               mo++;
                                               break;
                                       }
                                       if(board[re][choice2]<20 && board[re][choice2]!=0)
                                       {
                                               printf("BU ");
                                               break;
                                       }
                               }
                               for(re=choice2+1;re<8;re++)
                               {
                                       if(board[choice1][re]==0)
                                       {
                                               
                                               printf("ER ");
                                               moves[mo]=(choice1*10)+re;
                                               mo++;
                                       }
                                       if(board[choice1][re]>20)
                                       {
                                               printf("WR ");
                                               moves[mo]=(choice1*10)+re;
                                               capture_indexes[c]=mo;
                                               c++;
                                               mo++;
                                               break;
                                       }
                                       if(board[choice1][re]<20 && board[choice1][re]!=0)
                                       {
                                               printf("BR ");
                                               break;
                                       }
                               }
                               for(re=choice2-1;re>-1;re--)
                               {
                                       if(board[choice1][re]==0)
                                       {
                                               printf("EL ");
                                               moves[mo]=(choice1*10)+re;
                                               mo++;
                                       }
                                       if(board[choice1][re]>20)
                                       {
                                               printf("WL ");
                                               moves[mo]=(choice1*10)+re;
                                               capture_indexes[c]=mo;
                                               c++;
                                               mo++;
                                               break;
                                       }
                                       if(board[choice1][re]<20 && board[choice1][re]!=0)
                                       {
                                               printf("BL ");
                                               break;
                                       }
                               }
                        }
                        mo=0;
                        break;
                case 22:
                        if(turn!=2)
                        {
                                printf("Please choose a black piece because it is black's turn.\n");
                                move_finder();
                                break;
                        }
                        else
                        {
                               int re;
                               for(re=choice1+1;re<8;re++)
                               {
                                       if(board[re][choice2]==0)
                                       {
                                               printf("ED ");
                                               moves[mo]=(re*10)+choice2;
                                               mo++;
                                       }
                                       if(board[re][choice2]<20 && board[re][choice2]!=0)
                                       {
                                               printf("BD ");
                                               moves[mo]=(re*10)+choice2;
                                               capture_indexes[c]=mo;
                                               c++;
                                               mo++;
                                               break;
                                       }
                                       if(board[re][choice2]>20)
                                       {
                                               printf("WD ");
                                               break;
                                       }
                               }
                               for(re=choice1-1;re>-1;re--)
                               {
                                       if(board[re][choice2]==0)
                                       {
                                               printf("EU ");
                                               moves[mo]=(re*10)+choice2;
                                               mo++;
                                       }
                                       if(board[re][choice2]<20 && board[re][choice2]!=0)
                                       {
                                               printf("BU ");
                                               moves[mo]=(re*10)+choice2;
                                               capture_indexes[c]=mo;
                                               c++;
                                               mo++;
                                               break;
                                       }
                                       if(board[re][choice2]>20)
                                       {
                                               printf("WU ");
                                               break;
                                       }
                               }
                               for(re=choice2+1;re<8;re++)
                               {
                                       if(board[choice1][re]==0)
                                       {
                                               
                                               printf("ER ");
                                               moves[mo]=(choice1*10)+re;
                                               mo++;
                                       }
                                       if(board[choice1][re]<20 && board[choice1][re]!=0)
                                       {
                                               printf("BR ");
                                               moves[mo]=(choice1*10)+re;
                                               capture_indexes[c]=mo;
                                               c++;
                                               mo++;
                                               break;
                                       }
                                       if(board[choice1][re]>20)
                                       {
                                               printf("WR ");
                                               break;
                                       }
                               }
                               for(re=choice2-1;re>-1;re--)
                               {
                                       if(board[choice1][re]==0)
                                       {
                                               printf("EL ");
                                               moves[mo]=(choice1*10)+re;
                                               mo++;
                                       }
                                       if(board[choice1][re]<20 && board[choice1][re]!=0)
                                       {
                                               printf("BL ");
                                               moves[mo]=(choice1*10)+re;
                                               capture_indexes[c]=mo;
                                               c++;
                                               mo++;
                                               break;
                                       }
                                       if(board[choice1][re]>20)
                                       {
                                               printf("WL ");
                                               break;
                                       }
                               }
                        }
                        mo=0;
                        break;
                case 13:
                        if(turn!=1)
                        {
                                printf("Please choose a white piece because it is white's turn.\n");
                                move_finder();
                                break;
                        }
                        break;
                case 23:
                        if(turn!=2)
                        {
                                printf("Please choose a black piece because it is black's turn.\n");
                                move_finder();
                                break;
                        }
                        break;
                case 14:
                        if(turn!=1)
                        {
                                printf("Please choose a white piece because it is white's turn.\n");
                                move_finder();
                                break;
                        }
                        break;
                case 24:
                        if(turn!=2)
                        {
                                printf("Please choose a black piece because it is black's turn.\n");
                                move_finder();
                                break;
                        }
                        break;
                case 15:
                        if(turn!=1)
                        {
                                printf("Please choose a white piece because it is white's turn.\n");
                                move_finder();
                                break;
                        }
                        break;
                case 25:
                        if(turn!=2)
                        {
                                printf("Please choose a black piece because it is black's turn.\n");
                                move_finder();
                                break;
                        }
                        break;
                case 16:
                        if(turn!=1)
                        {
                                printf("Please choose a white piece because it is white's turn.\n");
                                move_finder();
                                break;
                        }
                        break;
                case 26:
                        if(turn!=2)
                        {
                                printf("Please choose a black piece because it is black's turn.\n");
                                move_finder();
                                break;
                        }
                        break;
                default: 
                        printf("Blank Space selected, choose valid space.\n");
                        move_finder();
                        break;

        }
}

int move_checker()
{
        int ij=0,checker;
        input_function(1);
        for(ij=0;ij<50;ij++)
        {
                if (moves[ij]==0)
                {
                        checker=(mov1*10)+mov2;
                        printf("%d ",checker);
                        if(ij==0)
                        {
                                printf("No Moves available.\n");
                        }
                        while(ij!=0)
                        {
                                //asd is used to loop thru the moves
                                int asd;
                                for(asd=0;asd<=ij;asd++)
                                {
                                        printf("%d ",moves[asd]);
                                        if(moves[asd]==checker)
                                        {
                                                ij=0;
                                        }
                                        if(moves[capture_indexes[asd]]!=0)
                                        {
                                                if(moves[capture_indexes[asd]]==checker)
                                                {
                                                        ij=0;
                                                        printf("Capturing something!\n");
                                                        captured=1;
                                                }
                                        }
                                }
                                if(ij!=0)
                                {
                                        printf("Not a valid spot, choose again\n");
                                        int cleaner_var;
                                        for(cleaner_var=0;cleaner_var<50;cleaner_var++)
                                        {
                                                moves[cleaner_var]=0;
                                                capture_indexes[cleaner_var]=0;
                                        }
                                        return 1;
                                }
                        }
                        return 0;
                }
        }
        return 0;
}