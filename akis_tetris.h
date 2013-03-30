
		

enum {HBLOCKS=10,VBLOCKS=18,BLOCKSIZE=25};
enum {N,W,S,E};
enum {LEFT,RIGHT};
enum {FALSE, TRUE};
enum {ORIGINY,ORIGINX=3};
enum {aspro=6,mavro=7};
							



	int dot[3][3]={{0, 0, 0},
						{0, 1, 0},
						{0, 0, 0}};


   /* TUPLE */

int tupleNorth[3][3]={{0, 1, 0},
                      {0, 1, 0},
	      			    {0, 0, 0}};

			

int tupleWest[3][3]={{0, 0, 0},
							{1, 1, 0},
							{0, 0, 0}};


	
int tupleSouth[3][3]=   {{0, 0, 0},
						       {0, 1, 0},
								 {0, 1, 0}};

 
int tupleEast[3][3]={{0, 0, 0},
							{0, 1, 1},
							{0, 0, 0}};

  /* CORNER */


int cornerNorth[3][3]= {{0, 1, 0},
								{0, 1, 1},
								{0, 0, 0}};


int cornerWest[3][3]=  {{0, 1, 0},
								{1, 1, 0},
								{0, 0, 0}};



int cornerSouth[3][3]={{0, 0, 0},
							  {1, 1, 0},
							  {0, 1, 0}};

 
int cornerEast[3][3]={{0, 0, 0},
						    {0, 1, 1},
							 {0, 1, 0}};

   /* T */


int TNorth[3][3]={{0, 0, 0},
					    {1, 1, 1},
				       {0, 1, 0}};



int TWest[3][3]= {{0, 1, 0},
				   	{0, 1, 1},
						{0, 1, 0}};


	
int TSouth[3][3]={{0, 1, 0},
						{1, 1, 1},
						{0, 0, 0}};

 
int TEast[3][3]=  {{0, 1, 0},
						 {1, 1, 0},
						 {0, 1, 0}};

   /* HAT */


int hatNorth[3][3]={{0, 0, 0},
					    	{1, 1, 1},
							{1, 0, 1}};



int hatWest[3][3]=  {{0, 1, 1},
					   	{0, 1, 0},
							{0, 1, 1}};


	
int hatSouth[3][3]= {{1, 0, 1},
				   		{1, 1, 1},
							{0, 0, 0}};


int hatEast[3][3]=   {{1, 1, 0},
		 					{0, 1, 0},
							{1, 1, 0}};



					
/* SQUARE */


int square[3][3]={{0, 1, 1},
		  				{0, 1, 1},
			      	{0, 0, 0}};


	
/* ta xrwmata twn 6 sximatwn + mavro aspro */
int colorTable[8];

typedef struct {
			XRectangle *blockPtr;
			int color;
			int x, y;
			}Block;


Block *gameTable[HBLOCKS][VBLOCKS];


typedef struct{

	/*syntetagmenes tou panw aristerou tetragwnou */

	int x,y;
	
	/* pio apo ta 6 kommatia einai */
	int type;

	/* to 3x3 kommati mesa sto opoio
	 * vrisketai to kommati */

	int table[3][3]; // xartis flag
	Block *blockTable[3][3]; //xartis block
	int color;
	int orientation; //arxizontas apo voria;

	}Piece;

struct COLOR_STRUCT{unsigned long black,white;}myColor;





/* to parathiro kai to gc to xreiazontai
 * polles sinartiseis kai gi'auto ta ekana
 * global 
 */



Display *display;
Window gameWindow;
GC gc,buttonGc;





void placeBlockAt(Block *thisBlock,short int x,short int y);
void initMainGameTable();
void drawMainGameTable();
void drawBlock(Block *thisBlock);
void drawPiece(Piece *thisPiece);
void setBlock(Block *thisBlock,int x, int y);
void printAllBlocks();
Piece  *createPiece(int type);
void rotatePiece(Piece *thisPiece);
void slidePiece(Piece *thisPiece,int orientation);
void enforceGravityAtPiece(Piece *thisPiece);
int isBlockedDownwardsBlock(Block *thisBlock);
int isBlockedDownwardsPiece(Piece *thisPiece);
int isBlockedHorizontallyPiece(Piece *thisPiece);	
Block * newBlock();
void placePieceAtOrigin(Piece *thisPiece);
void dumpPieceInGameTable(Piece *thisPiece);
