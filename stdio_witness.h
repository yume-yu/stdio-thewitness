/**
 * @file stdio_witness.h
 * @brief stdioで作るthe witnessもどきのヘッダ
 * @author yume_yu
 * @date 2018/07/08
 */

//多重インクルード防止
#pragma once

/**
 * コンパイルするOSの宣言
 * Windows系		WINDOWS
 * mac/Linux	MAC
 */
#define MAC

/* 使用するヘッダのインクルード */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

//OSに依存するライブラリをここに書く
#if defined WINDOWS

#include <windows.h>						//カーソル移動SetConsoleCursorPosition等
#include <conio.h>							//kbhit(),getch()など

#define ENTERKEY 0x0d						//Enterキーの入力の統一表記
#define MULTIBYTE_CHAR_SIZE 2		//マルチバイト文字の大きさの統一表記(文字コード?)

#elif defined MAC

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define ENTERKEY '\n'						//Enterキーの入力の統一表記
#define MULTIBYTE_CHAR_SIZE 3		//マルチバイト文字の大きさの統一表記(文字コード?)

#endif

/* 定数の定義(define) */

/**
 * メインフレーム(大枠)関連定数
 * WIDTH          メインフレームの幅
 * HEIGHT         メインフレームの高さ
 * MAIN_FLAME_X   メインフレームの開始位置のX座標
 * MAIN_FLAME_Y   メインフレームの開始位置のY座標
 */
#define WIDTH					70
#define HEIGHT 				45


/* 構造体の宣言 */

// arrow_pos	座標を管理するための構造体。リスト表示やマップ上で、配列にして使う
typedef struct {
	int x;							//x座標
	int y;							//y座標
	bool not_active;		//移動可能な座標かどうか
	bool at_event;			//イベントが有るマスかどうか
	bool was_passed;		//通過済みか
} arrow_pos;

// extendstr ストーリー等表示文字列の構造体
typedef struct {
	char string[100];		//表示する文字列
	int offset;					//表示位置の右ずらしオフセット
	int not_need_return;//入力を待つ行であるかのフラグ
} extendstr;

// input_assort 入力を扱う構造体
typedef struct {
	bool kbhit_flag;		//キーが押されているかを返すフラグ
	int input_char;			//入力されたキー
} input_assort;

/* 定数の定義(const) */


/* グローバル関数宣言 */

/* 関数マクロ定義 */
//char配列やextendstr配列の文字数/行数を返すマクロ
#define lengthof(var,type) (sizeof(var)/sizeof(type))

/* プロトタイプ宣言 */

/* ここからutil_func.cで定義する関数 */
#ifdef WINDOWS									//Windowsのときだけ必要な記述をこのifの中に入れる
void usleep(int time);					//usleepの表記統一のため
#endif

void mvcur(int x, int y);																		//カーソル移動を行う関数
input_assort mykbhit();																			//キー入力を取る関数
void wait_anyinput();																			//なにかキー入力を待つ関数
void wait_input_without_arrow();																//AWSD以外のキー入力を待つ関数
void init_term();																				//ターミナルの初期化を行う関数
void print_line(char string[], int x, int y);													//指定した座標を行頭にに1行出力する関数
void print_lines(char *string[], int x, int y, int num_lines);									//指定した座標を行頭に複数行出力する関数
void string_march(extendstr *(tmp)[],int x,int y,int lines);									//指定した座標を行頭に複数行アニメーション出力する関数
void reset_style();																				//エスケープシーケンスでの文字色,スタイル指定をリセットする関数
void to_bold();																					//エスケープシーケンスで以降の文字を太字にする関数
void change_text_color(int color);																//エスケープシーケンスで文字色を変更する関数
void change_back_color(int color);																//エスケープシーケンスでh背景色を変更する関数
int eslengthof(extendstr sxstr[]);																//拡張文字列変数extend_strのlengthを返す関数
void exstrcpy(extendstr *(to)[],extendstr from[],int lines);									//アニメーション表示用構造体配列をアドレスの配列に変換する関数
int select_from_list(arrow_pos tmp_pos[10], int length);										//縦方向のリストから選択させる関数
int select_from_hlist(arrow_pos tmp_pos[10], int length);										//横方向のリストから選択させる関数
int select_from_2dlist(int width, int height,arrow_pos tmp_pos[width][height]);					//平面リストから選択させる関数
/* ここまでutil_func.cで定義する関数 */

/* ここからflame_func.cで定義する関数 */
void make_flame(int width, int height, int offset_x, int offset_y);								//指定位置を左上に高さと幅を指定したフレームを作成する関数
void animete_make_flame_speedfix(int width,int height,int x,int y);								//指定位置にフレームをアニメーション付きで表示する関数
void flame_flush();																				//メインフレーム内をアニメーション付きでスペース埋めする関数
void curtain_animation();																		//メインフレーム内をカーテンアニメーション付きでスペース埋めする関数
void flame_clean();																				//メインフレーム内をアニメーションなしでスペース埋めする関数
void sub_flame_clean(int width, int height, int x, int y);										//指定範囲内をアニメーションなしでスペース埋めする関数
int check_window(int width, int height, int x, int y, char *string);							//確認文とy/nの確認フレームを出す関数
/* ここまでflame_func.cで定義する関数 */

/* ここからmap_func.cで定義する関数 */
arrow_pos **make_coors(int rows,int lines);
arrow_pos *move_on_maze(int width, int height,arrow_pos **map_coors,arrow_pos start_position);
/* ここまでmap_func.cで定義する関数 */
