#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct {
	char *szoveg;
	void *next;
	char *ischecked;
	char  pri;
}t_task;
typedef struct {
	t_task *start;	
	t_task *end;
}t_tasklist;
t_tasklist *tlist;

void list();
//---------------------------------------------------------
void startup()
{
	printf("\nTodo application\n====================\nCommands:\n");            
	printf(" -a   Adds a new task\n");
	printf(" -wr  Write current todos to file\n");	
	printf(" -rd  Read todos from a file\n");	
	printf(" -l   Lists all the tasks\n");	
	printf(" -e   Empty the list\n");
	printf(" -r   Removes a task\n");
	printf(" -c   Completes a task\n");
	printf(" -p   Adds priority to a task\n");
	printf(" -lp  Lists all the tasks by priority\n\n");
}
//----------------------------------------------------------
int is_digit (char c){
	if (c>47 && c<58)
		return 1;
	return 0;
}
//---------------------------------------------------------
void list ()
{
	if (tlist->start == NULL) {
		printf("empty list\n");
		return;
	}
	int i = 0;
	t_task *tp;
	tp = tlist->start;
	char *c, ch;
	printf("List by number\n================\nNum    priority [ ] Tasks\n\n");
	while (tp != NULL) {
		c = tp->ischecked;
		if (*c == '0')
			ch = ' ';
		else if (*c == '1')
			ch = 'x';
		
		printf("%d\t%c\t[%c] %s\n",i,tp->pri,ch,tp->szoveg );
		tp = tp->next;
		i++;
	}
}

//---------------------------------------------------------

int add (char *p)
{
	char *str, *tmp1;
	int cnt=0;
	while (*p != '"' && *p != '\0') { 	 			
		p++;
		if (*p == '\0') {
			printf("Unable to add: No task is provided 1\n");fflush(stdout);
			return 1;
		}
	}//megvan az elso macskakorom
	p++;
	tmp1 = p;
	while (*p != '"' && *p != '\0') { 
		p++;
		cnt++;
		if (*p == '\0') {
			printf("Unable to add: No task is provided 2\n");fflush(stdout);
			return 1;
		}
	}//megvan a masodik macskakorom
	if (cnt==0) {
		printf("task shouldn't be empty \n");
		return 1;
	}
	p = tmp1; //az elso nem macskakorom karira mutat
	str = malloc (cnt * sizeof (char));
	tmp1 = str;
	while (*p != '"') {
		*str = *p;
		p++;
		str++;
	}
	*str ='\0';
	t_task *tmpt;
	tmpt = malloc(sizeof (t_task));
	char *ic;
	ic = malloc(sizeof(char));
	*ic = '0';
	
	if (tlist->start == NULL) {//ha ez az első elem
		tlist->start = tmpt;
		tlist->start->szoveg = tmp1;
		tlist->start->ischecked = ic;
		tlist->start->pri = 0;
		tlist->start->next = NULL;
		tlist->end = tlist->start;		
		printf("added first\n");
	} else {//ha nem első elem
		tlist->end->next = tmpt; //az utolsó írott struct next-je mutasson az új elemre
		tlist->end = tmpt; //ez után az uccsó vektora mutasson rá
		tlist->end->szoveg = tmp1;
		tlist->end->ischecked = ic;
		tlist->end->pri = '0';
		tlist->end->next = NULL;
		printf("added\n");
	}
}
//--------------------------------------------------------
void sort_pr() 
{
	t_task *j, *elozo_max, *i, *max, *elozo_j, *elozo_i, *tmp;
	i = tlist->start;
	max = tlist->start;
	j = tlist->start;
	
	elozo_j = tlist->start;
	elozo_max = tlist->start;
	
	elozo_i = malloc (sizeof (t_task));
	elozo_i->next = malloc (1);
	elozo_i->next = tlist->start;
	if (j == NULL) {
		printf ("tasklist is empty, there is nothing to sort\n");
		return;
	} else if (j->next == NULL) {
		printf ("tasklist has one element, there is nothing to sort\n");
		return;
	} else {//legalább két elem van	
		int maxpri;		
		while (i->next != NULL) { //ha i az utolsó, biztos nincs utána nagyobb
			int cnt = 0;
			maxpri = i->pri;	
			printf("i pri: %c \n",i->pri);
			max = i; //ha talál nagyobbat, arra lép
			elozo_max = elozo_i;
			j = i->next;
			elozo_j = i;
			while (j != NULL) { //i-től végig megy
				cnt++;
				printf("  j pri: %c elo_j pri %c ",j->pri, elozo_j->pri);
				
				if (maxpri < j->pri) {
					maxpri = j->pri;
					elozo_max = elozo_j;
					max = j; 
					printf (" max ");
				}
				printf ("\n");
				elozo_j = j;
				j = j->next;			
			}
			if (i != max) {	
				printf("csere: %c %c  \n",i->pri, max->pri);	
				if (i == tlist->start){						
					tlist->start = max;
				} 
				elozo_max->next = max->next;//ezzel a max előttit a max utánihoz linkelem, max kikerül	a sorból
				max->next = i; //max i elé megy közvetlenül, rá mutat
				elozo_i->next = max;//ami i-re mutatott, az mutasson max-ra
				elozo_i = max;	//mivel max van i előtt, mostantól ez legyen az előzménye
				if (cnt ==1) { //ha az utolsó elemmel cseréltem, i az utolsó
					i->next = NULL;
				}				
			} else {
				elozo_i = i; //i léptetése, ha nincs előtte nála nagyobb
				i = i->next;
			}	
		}
	}
	list();
}
//---------------------------------------------------------
int padd (char *p)
{
	char *str, *tmp1;
	int cnt=0;
	while (*p != '"' && *p != '\0') { 	 			
		p++;
		if (*p == '\0') {
			printf("Unable to add: No task is provided 1\n");fflush(stdout);
			return 1;
		}
	}//megvan az elso macskakorom
	p++;
	tmp1 = p;
	while (*p != '"' && *p != '\0') { 
		p++;
		cnt++;
		if (*p == '\0') {
			printf("Unable to add: No task is provided 2\n");fflush(stdout);
			return 1;
		}
	}//megvan a masodik macskakorom
	if (cnt==0) {
		printf("task shouldn't be empty \n");
		return 1;
	}
	p = tmp1; //az elso nem macskakorom karira mutat
	str = malloc (cnt * sizeof (char));
	tmp1 = str;
	while (*p != '"') {
		*str = *p;
		p++;
		str++;
	}
	*str ='\0';
	t_task *tmpt;
	tmpt = malloc(sizeof (t_task));
	char *ic;
	ic = malloc(sizeof(char));
	*ic = '0';
	char pri = '0';
	 //most megkeresi az első számot
	 while (*p != '\0' && !is_digit(*p)) {
	 	p++;
	 	if (*p == '\0') {
	 		printf("No priority is provided, priority is set to 0\n");
	 		pri = '0';
	 	}	else {
	 		pri = *p;
	 	} 	
	 }
		
	if (tlist->start == NULL) {//ha ez az első elem
		tlist->start = tmpt;
		tlist->start->szoveg = tmp1;
		tlist->start->ischecked = ic;
		tlist->start->pri = pri;
		tlist->start->next = NULL;
		tlist->end = tlist->start;		
		printf("added first\n");
	} else {//ha nem első elem
		tlist->end->next = tmpt; //az utolsó írott struct next-je mutasson az új elemre
		tlist->end = tmpt; //ez után az uccsó vektora mutasson rá
		tlist->end->szoveg = tmp1;
		tlist->end->ischecked = ic;
		tlist->end->pri = pri;
		tlist->end->next = NULL;
		printf("added\n");
	}
}

//---------------------------------------------------------
void empty () 
{
	if (tlist->start!=NULL){
		t_task *tp, *tp2;
		tp = tlist->start;
		tlist->start = NULL;
		while (tp != NULL) {
			tp2 = tp->next;
			free(tp->szoveg);
			free(tp->ischecked);
			tp->ischecked = NULL;
			tp->szoveg = NULL;
			tp->next = NULL;
			free(tp);
			tp = tp2;
		}		
	}
}

//---------------------------------------------------------
void emptylist () 
{
	empty();
	printf("No todos for today! :)\n");
}
//---------------------------------------------------------
char *clrstr(char *str)
{
	char *ch;
	ch=str;
	while (*ch != '\0') {
		if (*ch == '\n') {
			*ch = '\0';
		}
		ch++;
	}
	return str;

}

//----------------------------------------------------------
void check(char *p)
{
	//p az első ' '-re mutat
	int no = 0; 
	char *p2;
	//megkeresem az első számot, vagy a szöveg végét
	while (!is_digit(*p) && *p != '\0') {
		p++;
		if (*p != ' ' && !is_digit(*p)){
			//számot keresek, előtte csak space lehet, egyéb kari nem
			printf("Unable to check: Index is not a number\n");
			return;
		}
	}
	//megvan az első számjegy, p arra mutat
	//olvasunk végjelig, az eredményt számmá alakítjuk
	int power = strlen(p)-1;
	int elsojegy = 1;
	while (*p != '\0') {
		if (!is_digit(*p)) { //csak számjegy lehet benne
			printf("Unable to check: Index is not a number\n");
			return;
		}
		if (*p == '0' && (*(p+1) != '\0') && elsojegy) {
			printf("Unable to check: Index is not a number\n");
			elsojegy = 0;
			return;
		}
		//erre biztosan van jó beépített függvény, de most így
		no += (*p - 48) * pow(10, power);
		p++;
		power--;	
	}	
	t_task *t1;
	t1 = tlist->start;
	for (int i = 0; i < no; i++) {		
		if (t1->next!=NULL) {
			t1 = t1->next;
		} else {
			printf ("Unable to check: Index is out of bound \n");
			return;
		}		
	}//most t1 a checkelendő elemre mutat
	char *ic;
	ic = t1->ischecked;
	if (*ic == '0') *ic = '1';
		else *ic = '0';
		
}
//----------------------------------------------------------
void rm(char *p)
{
	//p az első ' '-re mutat
	int no = 0; 
	char *p2;
	//megkeresem az első számot, vagy a szöveg végét
	while (!is_digit(*p) && *p != '\0') {
		p++;
		if (*p != ' ' && !is_digit(*p)){
			//számot keresek, előtte csak space lehet, egyéb kari nem
			printf("Unable to remove: Index is not a number\n");
			return;
		}
	}
	//megvan az első számjegy, p arra mutat
	//olvasunk végjelig, az eredményt számmá alakítjuk
	int power = strlen(p)-1;
	int elsojegy = 1;
	while (*p != '\0') {
		if (!is_digit(*p)) { //csak stámjegy lehet benne
			printf("Unable to remove: Index is not a number\n");
			return;
		}
		if (*p == '0' && (*(p+1) != '\0') && elsojegy) {
			printf("Unable to remove: Index is not a number\n");
			elsojegy = 0;
			return;
		}
		//erre biztosan van jó beépített függvény, de most így
		no += (*p - 48) * pow(10, power);
		p++;
		power--;	
	}	
	t_task *t1;
	if (no == 0) { //start eltávolítása		
		t1 = tlist->start->next;
		free(tlist->start->szoveg);
		free(tlist->start);
		tlist->start = t1;
	}else {
		t1=tlist->start;
		t_task *t2;
		t2 = malloc (sizeof (t_task));
		for (int i = 0; i < no; i++) {
			t2 = t1;
			if (t1->next!=NULL) {
				t1 = t1->next;
			} else {
				printf ("Unable to remove: Index is out of bound \n");
				return;
			}
			
		}//most t1 az eltávolítandó elemre mutat, t2 az egyel előttire
		if (t1 == tlist->end) {
			t2->next = NULL; //az előző nem mutat semmire, mert ez az uccsó elem
			tlist->end = t2;
		} else {
			t2->next = t1->next; //az előző a következőre mutasson
		}
		free(t1->szoveg);
		free(t1->ischecked);
		free(t1);
	}	
}

//----------------------------------------------------------

int read (char *p) 
{
	char *str, *tmp1;
	int cnt=0;
	while (*p != '"' && *p != '\0') { 	 			
		p++;
		if (*p == '\0') {
			printf("No valid filename\n");fflush(stdout);
			return 1;
		}
	}//megvan az elso macskakorom
	p++;
	tmp1=p;
	while (*p != '"' && *p != '\0') { 
		p++;
		cnt++;
		if (*p == '\0') {
			printf("No valid filename\n");fflush(stdout);
			return 1;
		}
	}//megvan a masodik macskakorom
	if (cnt==0) {
		printf("filename shouldn't be empty \n");
		return 1;
	}
	p = tmp1; //az elso nem macskakorom karira mutat
	str = malloc (cnt+1 * sizeof (char)); //nulla végű lesz
	tmp1 = str;
	while (*p != '"') {
		*str = *p;
		p++;
		str++;
	}
	*str = '\0';
	//es akkor nyitok egy filét ezen a néven
	FILE *fp;
	fp = fopen(tmp1, "r");
	if(fp != NULL){
		//mielőtt olvasok, felszabadítom a lefoglalt memóriát
		empty();
		//olvasok:
		char buf[255], *tmp2, *ic;
		memset (buf,'\0',255);		
		t_task *ttask;
		ttask = malloc(sizeof (t_task));
		int r = 0;
		while (fgets(buf, 255, (FILE*)fp) != NULL){ 	
			if (r == 0) { 		
				if (tlist->start != NULL){
					ttask = tlist->end;
					tlist->end = tlist->end->next;
				}		
				tlist->end = malloc(sizeof (t_task));
				if (tlist->start != NULL)
					ttask->next = tlist->end;			
			
				tmp2 =  malloc(255* sizeof(char));
				strcpy(tmp2, buf);
				memset (buf,'\0',255);		
				tmp2 = clrstr(tmp2);
				tlist->end->szoveg = tmp2;		
				tlist->end->next = NULL;	
				if (tlist->start == NULL) {						
					tlist->start = tlist->end;				
				}
				r = 1;
				printf(" 0 ");
			} else if (r == 1) {
				
				ic =  malloc(1);
				*ic = buf[0];
				tlist->end->ischecked = ic;
				r = 2;
				printf(" 1 ");
			} else if (r == 2) {
				tlist->end->pri =  buf[0];
				r = 0;
				printf(" 2 ");
			}			
			
			memset (buf,'\0',255);		
		}
		fclose(fp);
	} else {
		printf("no file like this\n");
		return 1;
	}
	printf("red\n");

}

//---------------------------------------------------------

int write(char *p)
{
	char *str, *tmp1;
	int cnt=0;
	while (*p != '"' && *p != '\0') { 	 			
		p++;
		if (*p == '\0') {
			printf("No valid filename\n");
			return 1;
		}
	}//megvan az elso macskakorom
	p++;
	tmp1=p;
	while (*p != '"' && *p != '\0') { 
		p++;
		cnt++;
		if (*p == '\0') {
			printf("No valid filename\n");fflush(stdout);
			return 1;
		}
	}//megvan a masodik macskakorom
	if (cnt==0) {
		printf("filename shouldn't be empty \n");
		return 1;
	}
	p = tmp1; //az elso nem macskakorom karira mutat
	str = malloc (cnt+1 * sizeof (char)); //nulla végű lesz
	tmp1 = str;
	while (*p != '"') {
		*str = *p;
		p++;
		str++;
	}
	*str = '\0';
	//es akkor nyitok egy filét ezen a néven
	FILE *fp;
	fp = fopen(tmp1, "w+");
	
	if (tlist->start == NULL) {
		printf("empty list, nothing to  write out\n");
		return 1;
	}
	int i = 0;
	t_task *tp;
	tp = tlist->start;
	char *string, *c;

	while (tp != NULL) {
		string = tp->szoveg;
		fprintf(fp,"%s\n",string);
		c = tp->ischecked;
		fprintf(fp,"%c\n%c\n",*c,tp->pri);
		tp = tp->next;
		i++;
	}
	
	fclose(fp);
	printf("file written\n");
}

//---------------------------------------------------------
int parancsertelmezo (char *parancs)
{
	 char *p, *str, *tmp1;
	 int cnt=0;
	 p = parancs;
	 if (*p == '-') {
	 	p++;
	 	if (*p == 'a') {
	 		add(p);
	 	} else if (*p == 'p') {
	 		padd(p);		 
		} else if (*p == 'l') {
	 		list();		 
		} else if (*p == 'c') {
	 		check(p);		 
		} else if (*p == 'e') {
	 		emptylist();		 
		} else if (*p == 's') {
	 		sort_pr();		 
		} else if (*p == 'w') {
			p++;
	 		if (*p == 'r') {
	 			write(p);
	 		} else {
	 			printf("there is no command like this\n");
	 			return 1;
	 		} 
		} else if (*p == 'r') {
			p++;
	 		if (*p == 'd') {
	 			read(p);
	 		} else if (*p == ' ') { 
	 			rm(p);
	 		
	 		} else {
	 			printf("there is no command like this\n");
	 			return 1;
	 		} 
		}
	 } else {
	 	printf("commands starts with '-'\n"); 
	 	fflush (stdout);
	 	return 1;
	 }
	 
	 return 0;
}
//--------------------------------------------------------
int main()
{
	tlist = malloc(sizeof (t_tasklist));
	tlist->start = NULL;
	tlist->end = NULL;
	char str [255];
	startup();
	gets(str);
	parancsertelmezo(&str);
	while(1) {
		printf("\n");
		gets(str);
		parancsertelmezo(&str);
		
	}
	return 0;
}
