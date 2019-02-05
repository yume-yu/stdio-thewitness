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

	for(int line = 0; line < lines + 1; line++){
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
    int route_length = 0;
	arrow_pos *route = (arrow_pos*)malloc(sizeof(arrow_pos)*100);
	char *circle[] = {
			" ▄▀▀▀▀▄ ",
			"█      █",
			"▀▄    ▄▀",
			"  ▀▀▀▀  ",
	};
	char *dis_circle[] = {
			"████████",
			"████████",
			"████████",
			"████████",
	};
	char *space[] = {
			"        ",
			"        ",
			"        ",
			"        ",
	};
	arrow_pos now_position = start_position;
	input_assort tmp_input_list; //入力の一時的な入れ物

    //開始地点の座標を0番目に登録
	set_coor_data(&route[route_length],start_position.x,start_position.y,start_position.not_active,start_position.at_event);

	print_lines(circle,2+8*now_position.x,2+now_position.y*4,4);
	while(1){
		mvcur(1,2);
		printf("length = %d : {%d,%d}",route_length,route[route_length].x,route[route_length].y);
		if(route_length > 0){
			mvcur(1,3);
			printf("length = %d : {%d,%d}",route_length - 1,route[route_length - 1].x,route[route_length - 1].y);
		}

	    fflush(stdout);
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		//break;
		switch(tmp_input_list.input_char){
			case 'w':
				print_lines(dis_circle,2+8*now_position.x,2 +4*now_position.y,4);
				if(now_position.y <= 0 || map_coors[now_position.x][now_position.y - 1].not_active || map_coors[now_position.x][now_position.y - 1].was_passed) {
					if (route_length > 0 && map_coors[now_position.x][now_position.y - 1].x == route[route_length - 1].x &&
						map_coors[now_position.x][now_position.y - 1].y == route[route_length - 1].y) {
						print_lines(space, 2 + 8 * now_position.x, 2 + 4 * now_position.y, 4);
						map_coors[now_position.x][now_position.y].was_passed = 0;
						now_position.y--;
						route_length--;
					}
				}else{
					map_coors[now_position.x][now_position.y].was_passed = 1;
					now_position.y--;
					route_length++;
					set_coor_data(&route[route_length],now_position.x,now_position.y,now_position.not_active,now_position.at_event);
				}
				print_lines(circle,2+8*now_position.x,2+now_position.y*4,4);
				break;
			case 's':
				print_lines(dis_circle,2+8*now_position.x,2 +4*now_position.y,4);
				if(now_position.y > height - 2 || map_coors[now_position.x][now_position.y + 1].not_active || map_coors[now_position.x][now_position.y + 1].was_passed){
					if (route_length > 0 && map_coors[now_position.x][now_position.y + 1].x == route[route_length - 1].x &&
						map_coors[now_position.x][now_position.y + 1].y == route[route_length - 1].y) {
						print_lines(space, 2 + 8 * now_position.x, 2 + 4 * now_position.y, 4);
						map_coors[now_position.x][now_position.y].was_passed = 0;
						now_position.y++;
						route_length--;
					}
				}else{
					map_coors[now_position.x][now_position.y].was_passed = 1;
					now_position.y++;
					route_length++;
					set_coor_data(&route[route_length],now_position.x,now_position.y,now_position.not_active,now_position.at_event);
				}
				print_lines(circle,2+8*now_position.x,2+now_position.y*4,4);
				break;
			case 'd':
				print_lines(dis_circle,2+8*now_position.x,2 +4*now_position.y,4);
				if(now_position.x > width - 2 || map_coors[now_position.x + 1][now_position.y].not_active|| map_coors[now_position.x + 1][now_position.y].was_passed){
					if (route_length > 0 && map_coors[now_position.x + 1][now_position.y].x == route[route_length - 1].x &&
						map_coors[now_position.x + 1][now_position.y].y == route[route_length - 1].y) {
						print_lines(space, 2 + 8 * now_position.x, 2 + 4 * now_position.y, 4);
						map_coors[now_position.x][now_position.y].was_passed = 0;
						now_position.x++;
						route_length--;
					}
				}else{
					map_coors[now_position.x][now_position.y].was_passed = 1;
					now_position.x++;
					route_length++;
					set_coor_data(&route[route_length],now_position.x,now_position.y,now_position.not_active,now_position.at_event);
				}
				print_lines(circle,2+8*now_position.x,2+now_position.y*4,4);
				break;
			case 'a':
				print_lines(dis_circle,2+8*now_position.x,2 +4*now_position.y,4);
				if(now_position.x <= 0 || map_coors[now_position.x - 1][now_position.y].not_active || map_coors[now_position.x - 1][now_position.y].was_passed){
					if (now_position.x > 0 && route_length > 0 && map_coors[now_position.x - 1][now_position.y].x == route[route_length - 1].x &&
						map_coors[now_position.x - 1][now_position.y].y == route[route_length - 1].y) {
						print_lines(space, 2 + 8 * now_position.x, 2 + 4 * now_position.y, 4);
						map_coors[now_position.x][now_position.y].was_passed = 0;
						now_position.x--;
						route_length--;
					}
				}else{
					map_coors[now_position.x][now_position.y].was_passed = 1;
					now_position.x--;
					route_length++;
					set_coor_data(&route[route_length],now_position.x,now_position.y,now_position.not_active,now_position.at_event);
				}
				print_lines(circle,2+8*now_position.x,2+now_position.y*4,4);
				break;
		}
		if(map_coors[now_position.x][now_position.y].at_event){
			set_coor_data(&route[route_length+1],-1,-1,false,false);
			break;
		}
	}
	return route;
}

