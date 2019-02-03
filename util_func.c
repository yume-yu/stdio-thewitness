/**
 * @file util_func.c
 * @brief 汎用的な関数を定義するファイル
 * @author yume_yu
 * @date 2018/07/08
 */
#include "theBeautifulSky.h"
#ifdef WINDOWS

/**
 * Windowsにはマイクロ秒でsleepするusleep(int)がないので
 * time 処理を停止する時間[ms]
 */
void usleep(int time){
	Sleep(time/1000);
}

/**
 * 左上を(1,1)としてカーソルを指定位置へ移動させる関数
 * x カーソルのx座標
 * y カーソルのy座標
 */
void mvcur(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE),
			coord
			);
}

/*
 * キーボードが押されているかとその入力キーをとる関数
 * 戻り値
 * input_assort temp	2つのフラグの構造体
 */
input_assort mykbhit(){
	input_assort temp;
	if(_kbhit()){
		temp.input_char =  _getch();
		temp.kbhit_flag = 1;
	}else{
		temp.input_char = 0;
		temp.kbhit_flag = 0;
	}
	return temp;
}

/**
 * 標準出力の初期化
 */
void init_term(){
	//カーソル位置を(1,1)に移動
	mvcur(1,1);
}

#elif defined MAC
/**
 * なんかわからんがunixでkbhit()を実装するおまじない
 *
 */
input_assort mykbhit(){
	struct termios oldt, newt;
	input_assort reply;
	int ch;
	int oldf;
	int flag;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF) {
			//ungetc(ch, stdin);
			reply.input_char = ch;
			reply.kbhit_flag = 1;
		return reply;
	}
	//reply.input_char = '\0';
	reply.kbhit_flag = 0;
	return reply;
}

/**
 * 任意の箇所へカーソルを移動する関数
 * x 移動するカーソルのx座標
 * y 移動するカーソルのy座標
 */
void mvcur(int x,int y){
	printf("\033[%d;%dH",y,x);
}

/**
 * 標準出力の初期化
 */
void init_term(){
	//標準出力を流す
	printf("\033[2J");
	//カーソル位置を(1,1)に移動
	mvcur(1,1);
}
#endif

/**
 *  なにかの入力の待機をする関数
 */
void wait_anyinput(){
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
	while(!mykbhit().kbhit_flag);
	while(mykbhit().kbhit_flag);
}

/**
 *  方向キー以外の入力の待機をする関数
 */
void wait_input_without_arrow(){
	int flag = 1;
	input_assort tmp;
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
	while(flag){
		tmp = mykbhit();
		switch(tmp.input_char){
			case 'a':
			case 's':
			case 'w':
			case 'd':
				break;
			default:
				if(tmp.kbhit_flag){
					flag = 0;
				}
				break;
		}
	}
	while(mykbhit().kbhit_flag);
}

/**
 * 指定箇所への1行の文字出力を行う関数
 * string 出力する文字列
 * x      出力するx座標
 * y      出力するy座標
 */
void print_line(char string[], int x, int y){
	mvcur(x,y);
	printf("%s",string);
	mvcur(0,HEIGHT + 1);
}

/*
 * 指定箇所への複数行行の文字出力を行う関数
 * string    出力する文字列配列
 * x         出力を開始するx座標
 * y         出力を開始するy座標
 * num_lines 出力する行数
 */
void print_lines(char *string[], int x, int y, int num_lines){
	for(int i = 0; i < num_lines; i++){
		print_line(string[i],x,y+i);
	}
	mvcur(0,HEIGHT + 1);
}

/**
 * 指定箇所への複数行のアニメーションつき文字出力を行う関数
 * string    出力する文字列2次元配列
 * x         出力を開始するx座標
 * y         出力を開始するy座標
 * num_lines 出力する行数
 */
void string_march(extendstr *(tmp)[],int x,int y,int lines){
	char substring[100];
	int text_length = eslengthof(*tmp);
	for(int i = 0; i < text_length; i++){
		for(int j = MULTIBYTE_CHAR_SIZE ; j < strlen(tmp[i]->string); j += MULTIBYTE_CHAR_SIZE ){
			mvcur(x + tmp[i]->offset,y + i);
			strncpy(substring,tmp[i]->string,j);
#if defined WINDOWS
			substring[j] = '¥0';
#elif defined MAC
			substring[j] = '\0';
#endif
			printf("%s",substring);
			mvcur(0,HEIGHT + 1);
			fflush(stdout);
			input_assort now = mykbhit();
			if(now.kbhit_flag && now.input_char == ENTERKEY){
			}else{
				usleep(30 * 1000);
			}
		}
		if(!tmp[i]->not_need_return){
			wait_input_without_arrow();
			//wait_anyinput();
		}
	}
}

/**
 *	エスケープシーケンスによるスタイル指定をリセットする関数
 */
void reset_style(){
	printf("\e[0m");
}

/**
 *	エスケープシーケンスで以降の文字を太字にする関数
 */
void to_bold(){
	printf("\e[1m");
}

/**
 *	エスケープシーケンスで以降の文字色を変更する関数
 *	0 < color < 244
 */
void change_text_color(int color){
	printf("\e[38;5;%dm",color);
}

/**
 *	エスケープシーケンスで以降の背景色を変更する関数
 *	0 < color < 244
 */
void change_back_color(int color){
	printf("\e[48;5;%dm",color);
}

/**
 *	拡張文字列extendstrの文字列長を返す関数
 */
int eslengthof(extendstr sxstr[HEIGHT - 2]){
	int counter = 0;
	while(true){
		if(!strcmp(sxstr[counter].string,"")){
			break;
		}
		counter++;
	}
	return counter;
}


/**
 *	表示文章を文章のアドレス配列に変換する関数
 */
void exstrcpy(extendstr *(to)[],extendstr from[],int lines){
	int counter;
	for(counter = 0; counter < lines; counter++){
		to[counter] = &from[counter];
	}
}

/**
 * リストを表示した際にカーソルの縦移動と決定した項目を管理する関数
 * tmp_pos[10] カーソルを表示する位置を定義したarrow_pos型の配列
 * length      リスト項目の数
 * 戻り値 length/Enterが押されたときの項目のラベル(何個目のメニューだったか)
 */
int select_from_list(arrow_pos tmp_pos[10], int length){
	int arrow_pos_label = 0;
	input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		switch(tmp_input_list.input_char){
			case 'w':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label <= 0){
					arrow_pos_label = length - 1;
				}else{
					arrow_pos_label--;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case 's':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label >= length - 1){
					arrow_pos_label = 0;
				}else{
					arrow_pos_label++;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label;
}

/**
 * リストを表示した際にカーソルの横移動と決定した項目を管理する関数
 * tmp_pos[10] カーソルを表示する位置を定義したarrow_pos型の配列
 * length      リスト項目の数
 * 戻り値 length/Enterが押されたときの項目のラベル(何個目のメニューだったか)
 */
int select_from_hlist(arrow_pos tmp_pos[10], int length){
	int arrow_pos_label = 0;
	input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		switch(tmp_input_list.input_char){
			case 'a':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label <= 0){
					arrow_pos_label = length - 1;
				}else{
					arrow_pos_label--;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case 'd':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label >= length - 1){
					arrow_pos_label = 0;
				}else{
					arrow_pos_label++;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label;
}

/*
 * リストを表示した際にカーソルの二次元移動と決定した項目を管理する関数
 * tmp_pos[10][10]	カーソルを表示する位置を定義したarrow_pos型の配列
 * length			リスト項目の数
 * 戻り値
 * int length		Enterが押されたときの項目のラベル(何個目のメニューだったか)
 */
int select_from_2dlist(int width, int height,arrow_pos tmp_pos[width][height]){
	arrow_pos arrow_pos_label = {0,0};
	input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);

		print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
		switch(tmp_input_list.input_char){
			case 'w':
				do{
					if(arrow_pos_label.y <= 0){
						arrow_pos_label.y = height - 1;
					}else{
						arrow_pos_label.y--;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 's':
				do{
					if(arrow_pos_label.y >= height - 1){
						arrow_pos_label.y= 0;
					}else{
						arrow_pos_label.y++;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 'a':
				do{
					if(arrow_pos_label.x <= 0){
						arrow_pos_label.x = width - 1;
					}else{
						arrow_pos_label.x--;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 'd':
				do{
					if(arrow_pos_label.x >= width - 1){
						arrow_pos_label.x= 0;
					}else{
						arrow_pos_label.x++;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label.x + width * arrow_pos_label.y;
}

