#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

 int quit = 0, it = 0, offset = 0;
 char c;

 initscr();
 start_color();
 cbreak();
 noecho();
 keypad(stdscr, TRUE);

 // GOOD
 init_pair(1,COLOR_WHITE,COLOR_BLACK);
 // BAD
 init_pair(2,COLOR_WHITE,COLOR_RED);
 WINDOW *at_text = newwin(72,110,1,3);

 
 
 struct stat st;
 if(stat(argv[1],&st) != 0){
  perror("error reading file.\n");
  endwin();
  return 1;
 }
 FILE *file = fopen(argv[1],"r");
 char *text = malloc(st.st_size * sizeof(char));
 char *comp = malloc(st.st_size * sizeof(char*));

 for(int i = 0; i < st.st_size-offset; i++){
   fseek(file,i+offset,SEEK_SET);
   comp[i] = fgetc(file);
   if(comp[i] == '\n'){
       comp[i] = ' ';
   }
 }
 int comp_size = st.st_size-offset-1;
 offset = 0;
 text[0] = '\0';

 while(!quit){
   clear();
   use_default_colors();
   mvwprintw(at_text,0,0,comp);
   refresh();
   for(int i = 0; i < it; i++){
     if(comp[i] == text[i]){
       wattron(at_text,COLOR_PAIR(1));
       mvwaddch(at_text,i/110,i%110,text[i]);
       wattroff(at_text,COLOR_PAIR(1));
     } else {
       wattron(at_text,COLOR_PAIR(2));
       mvwaddch(at_text,i/110,i%110,text[i]);
       wattroff(at_text,COLOR_PAIR(2));
     }
   }
   wrefresh(at_text);
   c = getch();
   if(c == 8){
     if(it>0){
       it = it-1;
       text[it] = '\0';
     }
   } else {
     text[it] = c;
     it++;
     text[it] = '\0';
   }
   if(it == comp_size){
     quit = 1;
   }
 }

 free(text);
 free(comp);
 fclose(file);
 endwin();
 return 0;
}
