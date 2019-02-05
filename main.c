#include"stdio_witness.h"

	char *circle[] = {
		" ▄▀▀▀▀▄ ",
		"█      █",
		"▀▄    ▄▀",
		"  ▀▀▀▀  ",
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
			}
		}
	}
	fflush(stdout);
}

int main (int argc,char *argv[]){
	/*列数 行数 開始地点行番号 列番号*/
    int rows,lines,start_x,start_y;

	if(argc != 2){
		fprintf(stderr,"argument was shortage.\n");
		return 1;
	}

	FILE *fp = fopen(argv[1],"r");
	if(fp == NULL){
		fprintf(stderr,"file open error.\n");
		return 1;
	}
	printf("open file is %s\n",argv[1]);
	int res = fscanf(fp,"%*s %d",&rows);
	if(res == -1){
		fprintf(stderr,"file format error. width is wrong.\n");
		return 1;
	}

	res = fscanf(fp,"%*s %d",&lines);
	if(res == -1){
		fprintf(stderr,"file format error. height is wrong.\n");
		return 1;
	}

	res = fscanf(fp,"%*s %d,%d",&start_x,&start_y);
	if(res == -1){
		fprintf(stderr,"file format error. startPoint is wrong.\n");
		return 1;
	}

	init_term();

	mvcur(1,1);

	arrow_pos **map_pos = make_coors(rows,lines);
	for(int i = 0; i < lines + 1;i++){
		mvcur(rows  *  8 + 4,i+1);
		for(int j = 0; j < rows; j++) {
			printf("[%2d,%2d] ", map_pos[j][i].x, map_pos[j][i].y);
		}
	}
	make_basemaze(rows,lines);
	char *square[] = {
		"┌─┐",
		"└─┘"
	};
	//print_lines(square,2+3*8 +3,6+3*4+1,2);
	print_line("▲",2+3*8 +4,6+3*4+1);
	//print_line("▲",35,21);
	//print_line("▲",33,23);
	//print_line("▲",37,23);
	arrow_pos start_pos = {start_x,start_y,0,0};
                       /*上オフセット+行数 */
	for(int line = 0; line < lines; line++){
		for(int row = 0; row < rows; row++){
			//print_lines(circle,2+row*8,6 + line*4,4);
		}
	}
	mvcur(0,1 + lines * 4 + 2 + 6);
	fflush(stdout);

	arrow_pos *result_route = move_on_maze(rows,lines+1,map_pos,start_pos);
	int label = 0;
	while(true) {
		printf("{%d,%d}\n",result_route[label].x,result_route[label].y);
		label++;
		if(result_route[label].x == -1){
			break;
		}
	}
}
