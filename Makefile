
tetrix: akis_tetris.c akis_tetris.h
	gcc -g -Wall  -lX11  akis_tetris.c -o tetrix 

clean:  
	rm tetrix


