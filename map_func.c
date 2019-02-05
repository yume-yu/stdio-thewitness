/**
 * @file map_func.c
 * @brief マップ関連の変数や関数を定義するファイル
 * @author yume_yu
 * @date 2018/07/12
 */

#include "stdio_witness.h"

void set_coor_data(arrow_pos *target,int x,int y, bool not_active,bool at_event){
	target->x = x;
	target->y = y;
	target->not_active = not_active;
	target->at_event = at_event;
}

/*実マップ/arrow_pos配列を作る*/
arrow_pos **make_coors(int rows,int lines){
	arrow_pos **return_map = (arrow_pos**)malloc(sizeof(arrow_pos*)*rows);
	return_map[0] = (arrow_pos*)malloc(sizeof(arrow_pos)*rows*(lines+1));
	for(int row = 0; row < rows; row++){
		return_map[row] = return_map[0] + row*(lines+1);
	}

	for(int line = 0; line < lines; line++){
		for(int row = 0; row < rows; row++){
			set_coor_data(&return_map[row][line],row,line,0,0);
			if(line % 2 == 0 && row % 2 == 1){
				set_coor_data(&return_map[row][line],row,line,1,0);
			}
			if(line == 0 && row == rows - 1){
				set_coor_data(&return_map[row][line],row,line,0,1);
			}else if(line == 0){
				set_coor_data(&return_map[row][line],row,line,1,0);
			}
		}
	}
	return return_map;
}

arrow_pos *move_on_maze(int width, int height,arrow_pos **map_coors,arrow_pos start_position){
	arrow_pos *route = (arrow_pos*)malloc(sizeof(arrow_pos)*100);
	char *dis_circle[] = {
		"████████",
		"████████",
		"████████",
		"████████",
	};
	char *circle[] = {
		" ▄▀▀▀▀▄ ",
		"█      █",
		"▀▄    ▄▀",
		"  ▀▀▀▀  ",
	};
	arrow_pos now_position = start_position;
	input_assort tmp_input_list; //入力の一時的な入れ物

	print_lines(circle,2+8*now_position.x,2+now_position.y*4,4);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		//break;
		switch(tmp_input_list.input_char){
			case 'w':
				print_lines(dis_circle,2+8*now_position.x,2 +4*now_position.y,4);
				if(now_position.y <= 0 || map_coors[now_position.x][now_position.y - 1].not_active || map_coors[now_position.x][now_position.y - 1].was_passed){
				}else{
					map_coors[now_position.x][now_position.y].was_passed = 1;
					now_position.y--;
				}
				print_lines(circle,2+8*now_position.x,2+now_position.y*4,4);
				break;
			case 's':
				print_lines(dis_circle,2+8*now_position.x,2 +4*now_position.y,4);
				if(now_position.y > height - 2 || map_coors[now_position.x][now_position.y + 1].not_active || map_coors[now_position.x][now_position.y + 1].was_passed){
				}else{
					map_coors[now_position.x][now_position.y].was_passed = 1;
					now_position.y++;
				}
				print_lines(circle,2+8*now_position.x,2+now_position.y*4,4);
				break;
			case 'd':
				print_lines(dis_circle,2+8*now_position.x,2 +4*now_position.y,4);
				if(now_position.x > width - 2 || map_coors[now_position.x + 1][now_position.y].not_active|| map_coors[now_position.x + 1][now_position.y].was_passed){
				}else{
					map_coors[now_position.x][now_position.y].was_passed = 1;
					now_position.x++;
				}
				print_lines(circle,2+8*now_position.x,2+now_position.y*4,4);
				break;
			case 'a':
				print_lines(dis_circle,2+8*now_position.x,2 +4*now_position.y,4);
				if(now_position.x <= 0 || map_coors[now_position.x - 1][now_position.y].not_active || map_coors[now_position.x - 1][now_position.y].was_passed){
				}else{
					map_coors[now_position.x][now_position.y].was_passed = 1;
					now_position.x--;
				}
				print_lines(circle,2+8*now_position.x,2+now_position.y*4,4);
				break;
		}
		if(map_coors[now_position.x][now_position.y].at_event){
			break;
		}
	}
	return route;
}

