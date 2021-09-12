#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void welcome_splash()
{
    for (int i=0;i<11;i++)
    {
        if(i==0)
        {
            printf("w         w   EEEEEEEE L           CCCC      OOO     MM     MM EEEEEEEE             TTTTTTTTTTT      OOO\n");
        }
        if(i==1)
        {
            printf("w         w   E        L         C         O     O   M   M   M E                        TT         O     O \n");
        }
        if(i==2)
        {
            printf("w         w   EEEEE    L        C         O       O  M       M EEEEE                    TT        O       O\n");
        }
		if(i==3)
        {
            printf(" w   W    w   E        L         C         O     O   M       M E                        TT         O     O\n");
        }
        if(i==4)
        {
            printf("  W     W     EEEEEEEE LLLLLLL     CCCC      OOO     M       M EEEEEEEE                 TT           OOO\n");
        }
        if(i==5)
        {
            printf("                             CCCC  H    H  EEEEEEEE    SSS     SSS\n");
        }

        if(i==6)
        {
            printf("                           C       H    H  E         S       S\n");
        }
        if(i==7)
        {
            printf("                          C        HHHHHH  EEEEE      SSSS    SSSS\n");
        }

        if(i==8)
        {
            printf("                           C       H    H  E              S       S\n");

        }
        if(i==9)
        {
            printf("                             CCCC  H    H  EEEEEEEE   SSS     SSS\n");
        }
        usleep(350000);
    }
}
void check_splash()
{
    for (int i=0;i<6;i++)
    {
        if(i==0)
        {
            printf("   CCCC  H    H  EEEEEEEE    CCCC K   KK\n");
        }
        if(i==1)
        {
            printf(" C       H    H  E         C      K KK\n");
        }
        if(i==2)
        {
            printf("C        HHHHHH  EEEEE    C       KK\n");
        }
		if(i==3)
        {
            printf(" C       H    H  E         C      K KK\n");
        }
        if(i==4)
        {
            printf("   CCCC  H    H  EEEEEEEE    CCCC K   KK  \n");
        }
        usleep(350000);
    }
}