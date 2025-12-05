#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define ALLOCATE 30

#define BLACK  "\033[0;30m"
#define RED    "\033[0;31m"
#define GREEN  "\033[0;32m"
#define BOLD_GREEN  "\033[1;32m"
#define YELLOW  "\033[0;33m"
#define BOLD_YELLOW  "\033[1;33m"
#define BLUE   "\033[0;34m"
#define MAGENT "\033[0;35m"
#define CYAN   "\033[0;36m"
#define WHITE  "\033[0;37m"
#define BOLD_WHITE  "\033[1;37m"
#define DIM_GRAY  "\033[2;37m"
#define RESET  "\033[0m"

void Print_helpMenu_or_Err(int);
int Mp3_View(char *);
int substring(char *hay, char *nee);
void Mp3_Edit(char *FileName, char *NewName, char *FrameId);

#endif