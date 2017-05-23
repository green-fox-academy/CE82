/*
Try to write a console program which is similar to the classig game "snake".
You will need consol related special library functions.
On windows use conio.h
On linux use curses.h
You can use the getch() function to get the code of the button which was pressed
by the user.
At first try to make a snake which goes straight on the screen.
After that try to change the direction of the movement with the arrow keys.
*/
#include<ncurses.h>
#include<curses.h>
int x=10, y=10;
int dir=0; //left, right, up, down
long count=0;
long maxcount=10000;
void init(){
	initscr();
	cbreak(); 
	noecho();
	keypad(stdscr, TRUE);

}

int main(){
	init();
	move(y, x);
	int ch ;
	nodelay(stdscr, TRUE);
	while(1){
		if ((ch = getch()) != ERR) {
			switch (ch) {
				case KEY_LEFT: 
					if(dir==3){
						dir=0;
					}else dir++;
				
					break;
				case KEY_RIGHT: 
					if(dir==0){
						dir=3;
					}else dir--;
					break;
			 default : 
				break;
			};			
    	}
    	if(count==50000){
				count=0;
				if(dir==0)x--;
				else if(dir==1) if(i>0)y--;else 
				else if(dir==2) x++;
				else if(dir==3) y++;
				move(y, x);
				//printw("%d",dir);
				//refresh();
		}else count++;
		move(y, x);
	    printw("@");	   
		refresh();			/* Print it on to the real screen */	
	}
	
	endwin();			/* End curses mode		  */

	return 0;
	
}
