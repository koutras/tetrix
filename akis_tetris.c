#include <X11/Xutil.h>
#include	<X11/Xos.h>
#include <X11/Xatom.h>
#include<X11/Xlib.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#include<string.h>
#include"akis_tetris.h"






int main (int argc, char **argv)
{
	/* auti i metavliti tha periexei deikti se struct display
	 * pou epistrefetai otan dimiourgoume mia syndesi
	 *
	 * genika mporoume na dimiourgisoume syndesi me apomakrismeno
	 * systima pou tha trexei ton server alla stin periptwsi mas
	 * syndeomaste sto idio systima pou trexoume ton server */


	/* auti i metavliti tha xrisimopoiithei gia na apothikeusi
	 * tin deufault othoni apo ton X server, sinithos o X server 
	 * exei  mia othoni opote gi'autin endiaferomaste */

	int screenNum;

	/* paxos tis grammis perigrammatos se pixel */

	int borderWidth=3;
//	char *windowName = " ###	AKIS-TETRIS	###";


	/* kathe othoni exei ena rootWindow pou kaliptei oli tin othoni*/

	Window rootWindow,win,menuBar;  



	/* win --> kyriws parathyro  tou programmatos mou */
	/* menuBar ---> to parathyro pou tha periexei ta pliktra start
	 * kai exit */

	XSizeHints *win_size_hints; /* hints oson afora to size ston WM */


	XGCValues values;

	int menuBarHeight;
	int menuBarVertPos;
	/* to ypsos tou menuBar */
	/* tha tou dwsw 8% tou ypsous tou kentrikou
	 * parathyrou */

	Window exitButton, startButton;

	int buttonSize;
	int padding; // xwros metaxy twn koumpiwn sto menu


	int winWidth = 600;
	int winHeight = 500;


	/* plirofories gia font */

	XFontStruct *fontInfo;

	

	padding = borderWidth * 4;
	
	


	int x=0, y=0;


	if((display=XOpenDisplay(0))==NULL){
		fprintf(stderr,"error opening display\n");
		exit(-1);
	}


	/* vazi ton arithmo tis deufault screen tou X server */
	screenNum = XDefaultScreen(display);

	/* vriskei to id tou rootWindow */
	rootWindow = XDefaultRootWindow(display);

	myColor.white =  WhitePixel(display, screenNum);
	myColor.black = BlackPixel(display, screenNum);

	colorTable[aspro]=myColor.white;
	colorTable[mavro]=myColor.black;

	win = XCreateSimpleWindow(display, rootWindow, x,y,
										winWidth, winHeight, borderWidth,
										myColor.black,myColor.white);
										

	gameWindow = XCreateSimpleWindow(display, win, borderWidth,borderWidth, 
										250, 450, borderWidth,
										myColor.black,myColor.white);
										


assert(fontInfo = XLoadQueryFont(display, "9x15"));
		
	
	menuBarHeight = 30; /* ypsos menu 8% tou parathyrou */

	/* na thimithw na to peiraxw */
	menuBarVertPos = winHeight -menuBarHeight - 2 * borderWidth;

	menuBar = XCreateSimpleWindow(display, win, 0, menuBarVertPos,
											winWidth - 2 * borderWidth,
											menuBarHeight, borderWidth,
											myColor.black, myColor.white);

	buttonSize = menuBarHeight - 2 * borderWidth;

	exitButton = XCreateSimpleWindow(display, menuBar,
												winWidth - (padding + 2*buttonSize),
												borderWidth,
												2*buttonSize, buttonSize, 1,
												myColor.black, myColor.white);


	startButton = XCreateSimpleWindow(display, menuBar,
												padding,
												borderWidth,
												2*buttonSize, buttonSize, 1,
												myColor.black, myColor.white);
	
	win_size_hints=XAllocSizeHints();
	assert(win_size_hints);

	win_size_hints->flags=PSize|PMinSize|PMaxSize;
	win_size_hints->min_width=winWidth;
	win_size_hints->min_height=winHeight;
	win_size_hints->base_width=winWidth;
	win_size_hints->base_height=winHeight;
	win_size_hints->max_height=winHeight;
	win_size_hints->max_width=winWidth;

	XSetWMNormalHints(display,win,win_size_hints);

	/* setting up the GC */

	values.foreground= myColor.black;
	values.background = myColor.white;

	gc = XCreateGC(display, gameWindow,
					(GCForeground | GCBackground), &values); 

	buttonGc = XCreateGC(display, menuBar,
						(GCForeground | GCBackground), &values); 





	assert(gc);
	assert(buttonGc);


		XSetLineAttributes(display, gc,
							3, LineSolid, CapButt, JoinRound);

		XSetLineAttributes(display, buttonGc,
							3, LineSolid, CapButt, JoinRound);




	XMapWindow(display,win);
	XMapSubwindows(display, win);
	XMapWindow(display, menuBar);
	XMapSubwindows(display, menuBar);

XFlush(display);

	/* do some random stuff */

	XSync(display, False); /* poly simantiko!!!!! */ 


//XDrawLine(display, gameWindow, gc, 20, 20, 40, 100);
	//XDrawRectangle(display, gameWindow, gc, 0, 0, 25, 25);
//	XDrawRectangle(display, gameWindow, gc, 25, 0, 25, 25);

	XFlush(display);

	sleep(3);


			

	XDrawImageString(display, exitButton, buttonGc,
							7,
							buttonSize/2.0+(fontInfo->ascent/2.0) ,
							 "E X I T",strlen("E X I T"));

	XDrawImageString(display, startButton, buttonGc,
							7,
							buttonSize/2.0+(fontInfo->ascent/2.0) ,
							 "START",strlen("START"));

	XFlush(display);



	initMainGameTable();
	printAllBlocks();
	drawMainGameTable();


	XFlush(display);

	sleep(10);

	XFlushGC(display, gc);
	XFlushGC(display, buttonGc);
	XFreeGC(display, buttonGc);
	XFreeGC(display, gc);
	XCloseDisplay(display);
	XFree(win_size_hints);

	return 0;
}
/* dimiourgei ton kyrio pinaka tou paixnidiou */



void initMainGameTable()
{
	int i;
	int j;
	int x,y;


	/* malloc memory space for blocks */

	for(i=0;i<VBLOCKS;i++)
		for(j=0;j<HBLOCKS;j++){
			gameTable[i][j]=newBlock();
		}


		printf("Block table malloced\n");


	/* assign positions to malloced blocks */


		
	

		for(i=0,y=0;i<VBLOCKS;i++)
			for(j=0,x=0;j<HBLOCKS;j++)
				setBlock(gameTable[i][j],j,i);
				
			
	 printf("Blocks placed\n");	

}

void setBlock(Block *thisBlock,int x, int y)
{
	thisBlock->x=x;
	thisBlock->y=y;
}

void drawBlock(Block *thisBlock)
{

	printf("trying to draw a block at %d, %d with size %d \n ",
		BLOCKSIZE*(thisBlock->x),
		BLOCKSIZE*(thisBlock->y),BLOCKSIZE);

	
	XDrawRectangle(display, gameWindow, gc,BLOCKSIZE*( thisBlock->x),
								BLOCKSIZE*(thisBlock->y),
								BLOCKSIZE, BLOCKSIZE);

						

	XFlush(display);

	sleep(4);

						
}

void dumpPieceInGameTable(Piece *thisPiece)
{
	int i,j;
	int x,y;

	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(thisPiece->table[i][j]){
				y=thisPiece->blockTable[i][j]->y;
				x=thisPiece->blockTable[i][j]->x;

				gameTable[i + y ][j + x ]->color=colorTable[thisPiece->type];
			}


	
	free(thisPiece);

	printf("piece Destroyed\n\n");
	
}

void drawPiece(Piece *thisPiece)
{
	int i,j;
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				if(thisPiece->table[i][j])
					drawBlock(thisPiece->blockTable[i][j]);
}

void printAllBlocks()
{
	int i,j;

	for(i=0;i<VBLOCKS;i++)
		for(j=0;j<HBLOCKS;j++)
			printf("blockTable[%d][%d] ,x=%d, y=%d \n", i,j,
											gameTable[i][j]->x,
											gameTable[i][j]->y);

	printf("blocks printed\n");
}	

void drawMainGameTable()
{

	int i,j;

	for(i=0;i<VBLOCKS;i++)
		for(j=0;j<HBLOCKS;j++)
			drawBlock( gameTable[i][j]);
								


}

/* dimiourgei ena sygekrimeno kommati */
	
Piece  *createPiece(int type)
{
	Piece *thisPiece;
	int i,j;
	Block *aBlock;
	
	thisPiece=(Piece*)malloc(sizeof(Piece));
	assert(thisPiece);


	for(i=0;i<3;i++)
		for(j=0;j<3;j++){
			aBlock=newBlock();
			thisPiece->blockTable[i][j]=aBlock;

		}


	printf("piece created\n");

	switch(type){
		
		case 0:/* dot */

			

			thisPiece->type=0;
			thisPiece->orientation=N;
			thisPiece->color=colorTable[0];
			memcpy(thisPiece->table,dot,sizeof(int)*9);	
				break;
		case 1: /* tuple */

			thisPiece->type=1;
			thisPiece->orientation=N;
			thisPiece->color=colorTable[1];
			memcpy(thisPiece->table,tupleNorth,sizeof(int)*9);	
					break;
		case 2: /* gwnia */
		
			thisPiece->type=2;
			thisPiece->orientation=N;
			thisPiece->color=colorTable[2];
			memcpy(thisPiece->table,cornerNorth,sizeof(int)*9);	
				break;
		case 3: /* T */
			
			thisPiece->type=3;
			thisPiece->orientation=N;
			thisPiece->color=colorTable[3];
			memcpy(thisPiece->table,TNorth,sizeof(int)*9);	
			break;
		case 4: /* hat */
			
			thisPiece->type=4;
			thisPiece->orientation=N;
			thisPiece->color=colorTable[4];
			memcpy(thisPiece->table,hatNorth,sizeof(int)*9);	
		break;

		case 5: /* square */
			
			thisPiece->type=0;
			thisPiece->orientation=N;
			thisPiece->color=colorTable[5];
			memcpy(thisPiece->table,square,sizeof(int)*9);	
			break;

		default:
			printf("Invalid piece Name\n");
			exit(-1);
		}

		
				
		

		return thisPiece;

}	


/* topotheteitai stin arxiki tou thesi tou
 * pinaka paixnidiou */

void placePieceAtOrigin(Piece *thisPiece)
{	
	Block *aBlock;


	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(thisPiece->table[i][j]){
				aBlock=newBlock();
				setBlock(aBlock,j+ORIGINX,i+ORIGINY);
				
				thisPiece->blockTable[i][j]=aBlock;
			}

			else 
				thisPiece->blockTable[i][j]=NULL;

}
	
	


Block *newBlock()
{
	
	Block *new;
	new=(Block*)malloc(sizeof(Block));
	assert(new);

	new->color=mavro;

	return new;
}

//peristrofi komatiou
void rotatePiece(Piece *thisPiece)
{
	switch(thisPiece->type){
		case 0:
			break;	

		case 1:
			switch(thisPiece->orientation){
				case N:
									 
					memcpy(thisPiece->table,tupleWest,9*sizeof(int));
					thisPiece->orientation= (thisPiece->orientation+1)%6;
				break;

				case W:	
					
					memcpy(thisPiece->table,tupleSouth,9*sizeof(int));
					thisPiece->orientation= (thisPiece->orientation+1)%6;

				break;

				case S:
					memcpy(thisPiece->table,tupleEast,9*sizeof(int));
					thisPiece->orientation= (thisPiece->orientation+1)%6;

				break;

				case E:
					memcpy(thisPiece->table,tupleNorth,9*sizeof(int));
					thisPiece->orientation= (thisPiece->orientation+1)%6;


				break;	
				}
		break;	

		case 2:
			switch(thisPiece->orientation){


				case N:

									 
					memcpy(thisPiece->table,cornerWest,9*sizeof(int));
					thisPiece->orientation= (thisPiece->orientation+1)%6;
				break;

				case W:	
					
					memcpy(thisPiece->table,cornerSouth,9*sizeof(int));
					thisPiece->orientation= (thisPiece->orientation+1)%6;

				break;

				case S:
					memcpy(thisPiece->table,cornerEast,9*sizeof(int));
					thisPiece->orientation= (thisPiece->orientation+1)%6;

				break;

				case E:
				memcpy(thisPiece->table,cornerNorth,9*sizeof(int));
						thisPiece->orientation= (thisPiece->orientation+1)%6;


				break;}
		break;	



	case 3:
			switch(thisPiece->orientation){


		   	case N:

									 
					memcpy(thisPiece->table,TWest,9*sizeof(int));
					thisPiece->orientation= (thisPiece->orientation+1)%6;
				break;

				case W:	
					
					memcpy(thisPiece->table,TSouth,9*sizeof(int));
					thisPiece->orientation= (thisPiece->orientation+1)%6;

				break;

				case S:
					memcpy(thisPiece->table,TEast,9*sizeof(int));
				thisPiece->orientation= (thisPiece->orientation+1)%6;

				break;

				case E:
				memcpy(thisPiece->table,TNorth,9*sizeof(int));
				thisPiece->orientation= (thisPiece->orientation+1)%6;


				break;}
		break;	


	case 4:
			switch(thisPiece->orientation){

		

				case N:

									 
					memcpy(thisPiece->table,hatWest,9*sizeof(int));
					thisPiece->orientation= (thisPiece->orientation+1)%6;
				break;

				case W:	
					
					memcpy(thisPiece->table,hatSouth,9*sizeof(int));
					thisPiece->orientation= (thisPiece->orientation+1)%6;

				break;

				case S:
					memcpy(thisPiece->table,hatEast,9*sizeof(int));
				thisPiece->orientation= (thisPiece->orientation+1)%6;

				break;

				case E:
				memcpy(thisPiece->table,hatNorth,9*sizeof(int));
				thisPiece->orientation= (thisPiece->orientation+1)%6;


				break;}
			break;	


	case 5:
													 
		break;	



	}	

}


/* orizontia metatopisi kommatiou */

void slidePiece(Piece *thisPiece,int orientation)
{
	int i,j;
	if(LEFT==orientation){
		
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				setBlock(thisPiece->blockTable[i][j],
					thisPiece->blockTable[i][j]->x-1,
					thisPiece->blockTable[i][j]->y);


	}

	else{
		/* RIGHT */

		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				setBlock(thisPiece->blockTable[i][j],
					thisPiece->blockTable[i][j]->x+1,
					thisPiece->blockTable[i][j]->y);


	}
}

/* sinartiseis oi opoies aforoun to kvanto kathe
 * sximatos diladi to block pou tha efarmozontai
 * epanaliptika se kathe block tou sximatos */



int isBlockedDownwardsBlock(Block *thisBlock)
{
	if(thisBlock->y == VBLOCKS -1)
		return TRUE;
	else if(gameTable[thisBlock->x][thisBlock->y]->color==mavro )
		return TRUE;

	else
		return FALSE;
		
		
}

int isBlockedDownwardsPiece(Piece *thisPiece)
{
	int i,j;
	int x,y;

	x=thisPiece->x;
	y=thisPiece->y;

	for(i=0;i<3;i++)
		for(j=0;j<3;j++){
			if(thisPiece->table[i][j] &&
				isBlockedDownwardsBlock(thisPiece->blockTable[i][j])
			)
				return TRUE;


		}
	return FALSE;
}
		
void enforceGravityAtPiece(Piece *thisPiece)
{
	int i,j;

	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(thisPiece->table[i][j])
				setBlock(thisPiece->blockTable[i][j],
					thisPiece->blockTable[i][j]->x,
					thisPiece->blockTable[i][j]->y+1);


}
int isBlockedHorizontallyBlock(Block *thisBlock)
{
	if(gameTable[thisBlock->x][thisBlock->y]->color== mavro ||
		thisBlock->x<0 || thisBlock->x >= HBLOCKS 
	)
		return TRUE;
	else
		return FALSE;
}
	


	
int isBlockedHorizontallyPiece(Piece *thisPiece)
{
	int i,j;
	int x,y;

	x=thisPiece->x;
	y=thisPiece->y;

	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(thisPiece->table[i][j] && 
				isBlockedHorizontallyBlock(thisPiece->blockTable[i][j])
			)
			
				return TRUE;

	return FALSE;

}

	
