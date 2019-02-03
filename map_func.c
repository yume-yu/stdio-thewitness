/**
 * @file map_func.c
 * @brief マップ関連の変数や関数を定義するファイル
 * @author yume_yu
 * @date 2018/07/12
 */

#include "theBeautifulSky.h"

/*
 * マップ上を移動する関数
 * width						マップの幅
 * hright 					マップの高さ
 * tmp_pos[10][10]	マップ座標の配列
 * offset						操作受け付け開始時の座標
 * 戻り値
 * int tmp_pos			ループを抜けた際の座標
 */
/*
arrow_pos move_on_map(int width, int height,arrow_pos *(tmp_pos)[WIDTH -2 ][HEIGHT - 2], arrow_pos offset){
	arrow_pos arrow_pos_label = offset;
	arrow_pos return_value;
	input_assort tmp_input_list;
	print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		switch(tmp_input_list.input_char){
			case 'w':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.y <= 0 || tmp_pos[arrow_pos_label.x][arrow_pos_label.y - 1]->not_active){
				}else{
					arrow_pos_label.y--;
				}
				print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;

			case 's':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.y > height - 2 || tmp_pos[arrow_pos_label.x][arrow_pos_label.y + 1]->not_active){
				}else{
					arrow_pos_label.y++;
				}
				print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;

			case 'a':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.x <= 0 || tmp_pos[arrow_pos_label.x - 1][arrow_pos_label.y]->not_active){
				}else{
					arrow_pos_label.x--;
				}
				print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;

			case 'd':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.x > width - 2 || tmp_pos[arrow_pos_label.x + 1][arrow_pos_label.y]->not_active){
				}else{
					arrow_pos_label.x++;
				}
				print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;
			case ' ':
				start_pos =*tmp_pos[arrow_pos_label.x][arrow_pos_label.y];
				start_pos.x -= 2;
				start_pos.y -= 2;
				arrow_pos_label.x = width - 2;
				arrow_pos_label.y = height - 1;
				return *tmp_pos[arrow_pos_label.x][arrow_pos_label.y];
				break;
			case ENTERKEY:
			default:
				//print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				mvcur(1,HEIGHT + 1);
				continue;
				//break;
		}
		//デバッグ用座標表示
		//printf("%2d,%2d",arrow_pos_label.x,arrow_pos_label.y);
		//printf("%2d,%2d %2d,%2d %d",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y,arrow_pos_label.x,arrow_pos_label.y,tmp_pos[arrow_pos_label.x][arrow_pos_label.y + 1]->not_active);
		if(tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->at_event){
			break;
		}
	}
	return *tmp_pos[arrow_pos_label.x][arrow_pos_label.y];
}
*/
/*エラーがうるさいのでとりあえず7*7特化で書く*/
arrow_pos move_on_maze(int width, int height,arrow_pos map_coors[7][8],arrow_pos start_position){
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

	print_lines(circle,2+10*start_position.x,start_position.y*5+1,4);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		//break;
		switch(tmp_input_list.input_char){
			case 'w':
				print_lines(dis_circle,2+10*now_position.x,now_position.y*5+1,4);
				if(now_position.y <= 0 || map_coors[now_position.x][now_position.y - 1].not_active){
				}else{
					now_position.y--;
				}
				print_lines(circle,2+10*now_position.x,now_position.y*5+1,4);
				break;
			case 's':
				print_lines(dis_circle,2+10*now_position.x,now_position.y*5+1,4);
				if(now_position.y > height - 2 || map_coors[now_position.x][now_position.y + 1].not_active){
				}else{
					now_position.y++;
				}
				print_lines(circle,2+10*now_position.x,now_position.y*5+1,4);
				break;
			case 'd':
				print_lines(dis_circle,2+10*now_position.x,now_position.y*5+1,4);
				if(now_position.x > width - 2 || map_coors[now_position.x + 1][now_position.y].not_active){
				}else{
					now_position.x++;
				}
				print_lines(circle,2+10*now_position.x,now_position.y*5+1,4);
				break;
			case 'a':
				print_lines(dis_circle,2+10*now_position.x,now_position.y*5+1,4);
				if(now_position.x <= 0 || map_coors[now_position.x - 1][now_position.y].not_active){
				}else{
					now_position.x--;
				}
				print_lines(circle,2+10*now_position.x,now_position.y*5+1,4);
				break;
		}
	}
	return start_position;
}

