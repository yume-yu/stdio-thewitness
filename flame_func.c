/**
 * @file flame_func.c
 * @brief フレーム操作に関する関数を定義するファイル
 * @author yume_yu
 * @date 2018/07/09
 */
#include "theBeautifulSky.h"

/*
 * フレームの作成関数
 * width    作成するフレームの幅
 * height   作成するフレームの高さ
 * offset_x 作成するフレームの開始位置のx座標
 * offset_y 作成するフレームの開始位置のy座標
 */
void make_flame(int width, int height, int offset_x, int offset_y){
	int print_width = width - 2;
	int print_height = height - 2;
	//1行目の描画
	mvcur(offset_x,offset_y);
	printf("┌");
	for(int i = 0; i < print_width; i++){
		printf("─");
	}
	printf("┐");
	//中間部分の描画
	for(int i = 0; i < print_height; i++){
		mvcur(offset_x,offset_y + 1 + i);
		printf("│");
		for(int j = 0; j < print_width; j++){
			printf(" ");
		}
		printf("│");
	}

	//最終行部分の描画
	mvcur(offset_x,offset_y + height - 1);
	printf("└");
	for(int i = 0; i < print_width; i++){
		printf("─");
	}
	printf("┘");

	//カーソル位置の初期化
	mvcur(1,HEIGHT+1);
}

/**
 * 横分割フレームの作成関数
 * width    作成するフレームの幅
 * height   作成するフレームの高さ
 * offset_x 作成するフレームの開始位置のx座標
 * offset_y 作成するフレームの開始位置のy座標
 * split_x  フレームの区切り線を入れるx座標
 */
void make_vsflame(int width, int height, int offset_x, int offset_y, int split_x){
	int print_width = width - 2;
	int print_height = height - 2;
	//1行目の描画
	mvcur(offset_x,offset_y);
	printf("┌");
	for(int i = 0; i < print_width; i++){
		if(i == split_x){
			printf("┬");
		}else{
			printf("─");
		}
	}
	printf("┐");
	//中間部分の描画
	for(int i = 0; i < print_height; i++){
		mvcur(offset_x,offset_y + 1 + i);
		printf("│");
		for(int j = 0; j < print_width; j++){
			if(j == split_x){
				printf("│");
			}else{
				printf(" ");
			}
		}
		printf("│");
	}
	//最終行部分の描画
	mvcur(offset_x,offset_y + height - 1);
	printf("└");
	for(int i = 0; i < print_width; i++){
		if(i == split_x){
			printf("┴");
		}else{
			printf("─");
		}
	}
	printf("┘");
#if defined WINDOWS
	printf("¥n");
#elif defined MAC
	printf("%c",ENTERKEY);
#endif
	//カーソル位置の初期化
	mvcur(1,HEIGHT+1);
}

/**
 *	アニメーションつきフレーム表示
 * width    作成するフレームの幅
 * height   作成するフレームの高さ
 * x				作成するフレームの開始位置のx座標
 * y				作成するフレームの開始位置のy座標
 */
void animete_make_flame_speedfix(int width,int height,int x,int y){
	int current_x;					//アニメーション中のフレームの現在の左上x座標
	int current_y;					//アニメーション中のフレームの現在の左上y座標
	int current_width;			//アニメーション中のフレームの現在の幅
	int current_height;			//アニメーション中のフレームの現在の高さ
	int width_blank;				//アニメーション中に幅が伸びる量
	int height_blank;				//アニメーション中に高さが伸びる量
	int difference_width;		//アニメーション表示中の幅の変化量
	int difference_height;	//アニメーション表示中の高さの変化量

	//変化量の初期値をセット
	difference_width = 2;
	difference_height = 2;

	//与えられた幅の偶奇で初期幅を決定する
	switch(width%2){
		case 0:
			current_width = 2;
			break;
		case 1:
			current_width = 3;
			break;
	}
	//与えられた高さの偶奇で初期高さを決定する
	switch(height%2){
		case 0:
			current_height = 2;
			break;
		case 1:
			current_height = 3;
			break;
	}
	//開始時の座標に中心座標をセット
	current_x = x + width/2 - 2;
	current_y = y + height/2 - 2;


	//高さと幅の伸びしろをとる
	width_blank = width - current_width;
	height_blank = height - current_height;
	//
	//幅の伸びしろのほうが小さいとき
	if(width_blank < height_blank){
		difference_height *= height_blank / width_blank;
	}else if(height_blank < width_blank){
		difference_width *= width_blank / height_blank;
	}

	//アニメーション表示する
	while(true){

		make_flame(current_width,current_height,current_x,current_y);
		fflush(stdout);
		//アニメーション終了チェック
		if(current_width == width && current_height == height){
			break;
		}

		//現在の値の更新 ここから
		if(width - current_width < difference_width){
			current_width = width;
			current_x = x;
		}else if(current_width != width){
			current_width += difference_width;
			current_x -= difference_width/2;
		}

		if(height - current_height < difference_height){
			current_height = height;
			current_y = y;
		}else if(current_height != height){
			current_height += difference_height;
			current_y -= difference_height/2;
		}
		//現在の値の更新 ここまで


		//アニメーションにするための間
		usleep(5 * 10000);
	}
}

/**
 * フレーム内をアニメーションでスペース埋めにする関数
 */
void flame_flush(){
	for(int i = 2; i < HEIGHT; i++){
		for(int j = 2; j < WIDTH; j++){
			print_line(" ",j,i);
		}
		fflush(stdout);
		usleep(5 * 10000);
	}
	fflush(stdout);
	usleep(2 * 100000);
	flame_clean();
}

/**
 * フレーム内をカーテンアニメーションでスペース埋めにする関数(往復)
 */
void curtain_animation(){
	for(int i = 2; i < HEIGHT; i++){
		for(int nowLines = 2; nowLines <= i; nowLines++){
			if(nowLines < HEIGHT / 4){
					printf("\e[48;5;160m");
			}else if (nowLines < HEIGHT / 2){
					printf("\e[48;5;124m");
			}else if (nowLines < 3 * HEIGHT / 4){
					printf("\e[48;5;88m");
			}else{
					printf("\e[48;5;52m");
			}
			if(nowLines != i){
				for(int j = 2; j < WIDTH; j++){
					print_line(" ",j,nowLines);
				}
			}else{
				printf("\e[0m");
				printf("\e[38;5;184m");
				for(int j = 2; j < WIDTH; j++){
					print_line(";",j,nowLines);
				}
			}
		}
		fflush(stdout);
		usleep(5 * 10000);
	}
	printf("\e[0m");
	fflush(stdout);
	usleep(2 * 100000);
	for(int i = HEIGHT -1; i > 1; i--){
		for(int j = 2; j < WIDTH; j++){
			print_line(" ",j,i);
			if(i != 2){
				printf("\e[38;5;184m");
				print_line(";",j,i-1);
			}
		}
		fflush(stdout);
		usleep(5 * 10000);
	}
	printf("\e[0m");
}

/**
 * フレーム内をスペース埋めにする関数
 */
void flame_clean(){
	for(int i = 2; i < HEIGHT; i++){
		for(int j = 2; j < WIDTH; j++){
			mvcur(j,i);
			printf(" ");
		}
		//usleep(2 * 10000);
	}
	fflush(stdout);
}

/**
 * 指定フレーム内をスペース埋めにする関数
 */
void sub_flame_clean(int width, int height, int x, int y){
	for(int i = y; i < y + height; i++){
		for(int j = x; j <x+  width;j++){
			print_line(" ",j,i);
		}
	}
	fflush(stdout);
}

/**
 * 指定位置,サイズで確認窓を出す関数
 */
int check_window(int width, int height, int x, int y, char *string){
	arrow_pos yesno_pos[2] = {
		{x + width / 2 + 2,y+3},
		{x + width / 2 - 3,y+3}
	};
	make_flame(width,height,x,y);
	mvcur(x+2,y+1);
	printf("%s",string);
	print_line("y /  n",x + width / 2 - 2,y+3);
	return select_from_hlist(yesno_pos,2);
}

