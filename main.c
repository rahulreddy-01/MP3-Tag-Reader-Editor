#include<stdio.h>
#include<string.h>
#include "functions.h"

int main(int argc, char** argv)
{
    if(argc == 2 && (!(strcmp(argv[1], "--help"))))
    {
        Print_helpMenu_or_Err(1);
    }
    else if(argc == 3 && !strcmp(argv[1], "-v") && substring(argv[2], ".mp3"))
    {
        Mp3_View(argv[2]);
    }
    else if(argc == 5 && !strcmp(argv[1], "-e") && strstr(argv[4], ".mp3"))
    {
        switch(argv[2][0])
        {
            case '-' :
            {
                switch(argv[2][1])
                {
                    case 't' :
                    {
                        Mp3_Edit(argv[4], argv[3], "TIT2");
                        break;
                    }
                    case 'a' :
                    {
                        Mp3_Edit(argv[4], argv[3], "TPE1");
                        break;
                    }
                    case 'A' :
                    {
                        Mp3_Edit(argv[4], argv[3], "TALB");
                        break;
                    }
                    case 'm' :
                    {
                        Mp3_Edit(argv[4], argv[3], "COMM");
                        break;
                    }
                    case 'y' :
                    {
                        Mp3_Edit(argv[4], argv[3], "TYER");
                        break;
                    }
                    case 'c' :
                    {
                        Mp3_Edit(argv[4], argv[3], "TCON");
                        break;
                    }
                    default :
                        Print_helpMenu_or_Err(2);
                }
                break;
            }
            default :
                Print_helpMenu_or_Err(2);
        }
    }
    else
    {
        Print_helpMenu_or_Err(2);
    }
    return 0;
}