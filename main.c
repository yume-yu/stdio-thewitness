#include"theBeautifulSky.h"

	char *circle[] = {
		" ▄▀▀▀▀▄ ",
		"█      █",
		"▀▄    ▄▀",
		"  ▀▀▀▀  ",
	};
int g_width = 58;
int g_height= 30;
arrow_pos practice_mappos[7][8] = {
	{{0,0,1,0},{0,1,0,0},{0,2,0,0},{0,3,0,0},{0,4,0,0},{0,5,0,0},{0,6,0,0},{0,7,0,0}},
	{{1,0,1,0},{1,1,0,0},{1,2,1,0},{1,3,0,0},{1,4,1,0},{1,5,0,0},{1,6,1,0},{1,7,0,0}},
	{{2,0,1,0},{2,1,0,0},{2,2,0,0},{2,3,0,0},{2,4,0,0},{2,5,0,0},{2,6,0,0},{2,7,0,0}},
	{{3,0,1,0},{3,1,0,0},{3,2,1,0},{3,3,0,0},{3,4,1,0},{3,5,0,0},{3,6,1,0},{3,7,0,0}},
	{{4,0,1,0},{4,1,0,0},{4,2,0,0},{4,3,0,0},{4,4,0,0},{4,5,0,0},{4,6,0,0},{4,7,0,0}},
	{{5,0,1,0},{5,1,0,0},{5,2,1,0},{5,3,0,0},{5,4,1,0},{5,5,0,0},{5,6,1,0},{5,7,0,0}},
	{{6,0,0,1},{6,1,0,0},{6,2,0,0},{6,3,0,0},{6,4,0,0},{6,5,0,0},{6,6,0,0},{6,7,0,0}},
};

void make_basemaze(int rows,int lines){
	int maze_width 	= 1 + rows * 8 + 1;
	int maze_height = 1 + lines * 4 + 1;
	char *exit_point[] ={
		"┌────────┐",
		"│        │",
		"│        │",
		"│        │",
		"┘        │",
	};
	make_flame(maze_width ,maze_height,1,5);
	print_lines(exit_point,maze_width - 9,1,5);
	for(int line = 0; line < lines; line++){
		for(int row = 0; row < rows; row++){
			if(line % 2 && row % 2){
				make_flame(8,4,2+row*8,6+line*4);
			}else{
				//print_lines(circle,2+row*8,6 + line*4,4);
			}
		}
	}
	//print_line("▲",15,12);
	//print_line("▲",35,21);
	//print_line("▲",33,23);
	//print_line("▲",37,23);
	fflush(stdout);
}


int main (int argc,char *argv[]){
	if(argc != 3){
		fprintf(stderr,"not enough args.\n");
		return 1;
	}
	int rows = atoi(argv[1]);
	if(rows % 2 == 0){
		fprintf(stderr,"rows is even. that must be odd.\n");
		return 1;
	}
	int lines = atoi(argv[2]);
	if(lines % 2 == 0){
		fprintf(stderr,"lines is even. that musr be odd.\n");
		return 1;
	}
	init_term();

	mvcur(1,1);

	arrow_pos **map_pos = make_coors(rows,lines);

	make_basemaze(rows,lines);
	arrow_pos start_pos = {0,lines,0,0};
                       /*上オフセット+行数 */
	for(int line = 0; line < lines; line++){
		for(int row = 0; row < rows; row++){
			//print_lines(circle,2+row*8,6 + line*4,4);
		}
	}
	mvcur(0,1 + lines * 4 + 2 + 6);
	fflush(stdout);

	move_on_maze(rows,lines+1,map_pos,start_pos);
}
