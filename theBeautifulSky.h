/**
 * @file thebeautifulsky.h
 * @brief ゲーム｢thebeautifulsky｣のヘッダ
 * @author yume_yu
 * @date 2018/07/08
 */

//多重インクルード防止
#pragma once

/**
 * コンパイルするOSの宣言
 * Windows系	WINDOWS
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
#define MAIN_FLAME_X	1
#define MAIN_FLAME_Y 	1

/*
 * ステージセレクトフレーム関連定数
 * SELECT_STAGE_FLAME_WIDTH  フレームの幅
 * SELECT_STAGE_FLAME_HEIGHT フレームの高さ
 * SELECT_STAGE_FLAME_X      フレームの開始位置のX座標
 * SELECT_STAGE_FLAME_Y      フレームの開始位置のY座標
 */
#define SELECT_STAGE_FLAME_WIDTH  				25
#define SELECT_STAGE_FLAME_HEIGHT 				11
#define SELECT_STAGE_FLAME_X      				(WIDTH  - SELECT_STAGE_FLAME_WIDTH) / 2
#define SELECT_STAGE_FLAME_Y      				(HEIGHT - SELECT_STAGE_FLAME_HEIGHT) / 2

/**
 * 戦闘画面でのウィンドウサイズ/配置関連定数
 * BATTLE_MODE_STATUS_FLAME_WIDTH   下分割フレームの幅
 * BATTLE_MODE_STATUS_FLAME_HEIGHT  下分割フレームの高さ
 * BATTLE_MODE_STATUS_FLAME_X       下分割フレームの開始位置のX座標
 * BATTLE_MODE_STATUS_FLAME_SPLIT_X 下分割フレームの分割位置
 * BATTLE_MODE_COMMAND_POS          戦闘コマンドブレーム(下左)の1行目のX座標
 * BATTLE_MODE_STATUS_HP_POS        ステータスフレーム(下右)の1行目のX座標
 */
#define BATTLE_MODE_STATUS_FLAME_WIDTH		WIDTH-2
#define BATTLE_MODE_STATUS_FLAME_HEIGHT		6
#define BATTLE_MODE_STATUS_FLAME_X				2
#define BATTLE_MODE_STATUS_FLAME_SPLIT_X 	2*(WIDTH-2)/3-1 -2
#define BATTLE_MODE_COMMAND_POS 					7
#define BATTLE_MODE_STATUS_HP_POS 				BATTLE_MODE_STATUS_FLAME_SPLIT_X+5

/*
 * キャラクターステータス設定モード関連定数
 * EDIT_MODE_SELECT_FLAME_WIDTH
 * EDIT_MODE_SELECT_FLAME_HEIGHT
 * EDIT_MODE_SELECT_FLAME_X
 * EDIT_MODE_SELECT_FLAME_Y
 * EDIT_MODE_EDIT_FLAME_CHAR_X
 * EDIT_MODE_EDIT_FLAME_CHAR_Y
 */
#define EDIT_MODE_SELECT_FLAME_WIDTH			WIDTH - 4
#define EDIT_MODE_SELECT_FLAME_HEIGHT			10
#define EDIT_MODE_SELECT_FLAME_X					3
#define EDIT_MODE_SELECT_FLAME_Y					2
#define EDIT_MODE_EDIT_FLAME_WIDTH				WIDTH - 4
#define EDIT_MODE_EDIT_FLAME_HEIGHT				HEIGHT - 12
#define EDIT_MODE_EDIT_FLAME_X						3
#define EDIT_MODE_EDIT_FLAME_Y						12
#define EDIT_MODE_EDIT_FLAME_CHAR_X				6
#define EDIT_MODE_EDIT_FLAME_CHAR_Y 			14
#define ECHECK_SELECT_FLAME_WIDTH  				WIDTH / 4 + 3
#define ECHECK_SELECT_FLAME_HEIGHT 				HEIGHT / 4
#define ECHECK_SELECT_FLAME_X							WIDTH / 4 + 8
#define ECHECK_SELECT_FLAME_Y      				3 * HEIGHT / 4
#define ECHECK_TEMPLATE_FLAME_WIDTH  			WIDTH / 4 + 10
#define ECHECK_TEMPLATE_FLAME_HEIGHT 			HEIGHT / 4
#define ECHECK_TEMPLATE_FLAME_X      			WIDTH / 4 + 3
#define ECHECK_TEMPLATE_FLAME_Y      			HEIGHT / 2 + 3

#define SELECT_MODE_FLAME_HEIGHT_OFFSET 	2
#define SCHECK_SELECT_FLAME_WIDTH  				WIDTH / 4
#define SCHECK_SELECT_FLAME_HEIGHT 				HEIGHT / 4
#define SCHECK_SELECT_FLAME_X      				WIDTH / 4 + 8
#define SCHECK_SELECT_FLAME_Y      				HEIGHT / 2 - 6
#define SELECT_MODE_EQIP_FLAME_WIDTH			WIDTH / 2 - 6
#define SELECT_MODE_POTION_FLAME_HEIGHT		3
#define SELECT_MODE_EQIP_FLAME_HEIGHT			6
#define SELECT_MODE_EQIP_FLAME_X					3 + WIDTH / 2 + 2
#define SELECT_MODE_EQIP_FLAME_Y					SELECT_MODE_FLAME_HEIGHT_OFFSET
#define SELECT_MODE_EQIP_CHARASET_X				SELECT_MODE_EQIP_FLAME_X + SELECT_MODE_EQIP_FLAME_WIDTH - 2

#define CHARACTER_STATUS_ATK_DIFF 				10
#define CHARACTER_STATUS_HP_DIFF 					20

#define SET_WEAPON_MODE_FLAME_WIDTH 			18
#define SET_WEAPON_MODE_FLAME_HEIGHT 			7
#define SET_WEAPON_MODE_FLAME_X 					(WIDTH - SET_WEAPON_MODE_FLAME_WIDTH) / 2
#define SET_WEAPON_MODE_FLAME_Y 					(HEIGHT - SET_WEAPON_MODE_FLAME_HEIGHT) / 2
#define SET_WEAPON_EDIT_FLAME_CHAR_X 			5
#define SET_WEAPON_EDIT_FLAME_CHAR_Y 			13

#define EDIT_EQIP_SELECT_FLAME_X					2
#define EDIT_EQIP_SELECT_FLAME_Y					2
#define EDIT_EQIP_SELECT_FLAME_WIDTH			(WIDTH - 2)
#define EDIT_EQIP_SELECT_FLAME_HEIGHT			(HEIGHT - 2) / 3
#define EDIT_EQIP_EDIT_FLAME_X						2
#define EDIT_EQIP_EDIT_FLAME_Y						EDIT_EQIP_SELECT_FLAME_HEIGHT + 1
#define EDIT_EQIP_EDIT_FLAME_WIDTH				(WIDTH - 2)
#define EDIT_EQIP_EDIT_FLAME_HEIGHT				2* (HEIGHT - 2) / 3

//タイトル画面の星の数
#define STAR_AMOUNT 											50
#define TITLE_MENU_BASE_X									(WIDTH - 24)/2
#define TITLE_MENU_BASE_Y									HEIGHT - 6

/**
 *	@def
 *	マップ上のメニューに関する定数
 */
#define MAP_WIN_WIDTH		(WIDTH - 2) / 3
#define MAP_WIN_HEIGHT	6
#define MAP_WIN_X				WIDTH - 1 - MAP_WIN_WIDTH
#define MAP_WIN_Y				5

/**
 *	@def
 *	マップ上のステータスメニューに関する定数
 */
#define STAT_WIN_WIDTH		MAP_WIN_WIDTH  + 10
#define STAT_WIN_HEIGHT		8
#define STAT_WIN_X				MAP_WIN_X - (MAP_WIN_WIDTH + 10)


/* 構造体の宣言 */

// arrow_pos	座標を管理するための構造体。リスト表示やマップ上で、配列にして使う
typedef struct {
	int x;							//x座標
	int y;							//y座標
	bool not_active;		//移動可能な座標かどうか
	bool at_event;			//イベントが有るマスかどうか
} arrow_pos;

// character	キャラクターの基本ステータス構造体
typedef struct {
	char *name;					//名前
	int hp;							//現在の体力
	int max_hp;					//体力の最大値
	int max_atk;				//与ダメージの上限
	int min_atk;				//与ダメージの下限
} character;

// weapon 武器の基本ステータス構造体
typedef struct {
	char *name;					//名前
	int atk;						//与ダメージ増加分
	bool is_gun;				//銃であるかどうか
} weapon;

// protector 防具の基本ステータス構造体
typedef struct {
	char *name;					//名前
	int def;						//防御力の増加分
} protector;

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

// stage マップを表す列挙
typedef enum {
	stage1,
	stage2,
	stage3_1,
	stage3_2,
	stage3_3,
	stage4_1,
	stage4_2,
	stage4_3,
	stage5,
	ope_exp
} stage;

// event マップで起こるイベントを表す列挙
typedef enum {
	battle_event, //戦闘イベント
	talk_event,		//会話イベント
	move_map,			//マップ間の移動
	open_menu			//メニューを開く
} event;

/* 定数の定義(const) */


/* グローバル関数宣言 */


//ステージ管理/マップ管理

/* ここからmap_stX.cで定義する変数 */

/* 関数マクロ定義 */
//char配列やextendstr配列の文字数/行数を返すマクロ
#define lengthof(var,type) (sizeof(var)/sizeof(type))

/* プロトタイプ宣言 */

/* ここからutil_func.cで定義する関数 */
#ifdef WINDOWS									//Windowsのときだけ必要な記述をこのifの中に入れる
void usleep(int time);					//usleepの表記統一のため
#endif

void mvcur(int x, int y);																												//カーソル移動を行う関数
input_assort mykbhit();																													//キー入力を取る関数
void wait_anyinput();																														//なにかキー入力を待つ関数
void wait_input_without_arrow();																								//AWSD以外のキー入力を待つ関数
void init_term();																																//ターミナルの初期化を行う関数
void print_line(char string[], int x, int y);																		//指定した座標を行頭にに1行出力する関数
void print_lines(char *string[], int x, int y, int num_lines);									//指定した座標を行頭に複数行出力する関数
void string_march(extendstr *(tmp)[],int x,int y,int lines);										//指定した座標を行頭に複数行アニメーション出力する関数
void reset_style();																															//エスケープシーケンスでの文字色,スタイル指定をリセットする関数
void to_bold();																																	//エスケープシーケンスで以降の文字を太字にする関数
void change_text_color(int color);																							//エスケープシーケンスで文字色を変更する関数
void change_back_color(int color);																							//エスケープシーケンスでh背景色を変更する関数
int eslengthof(extendstr sxstr[]);																							//拡張文字列変数extend_strのlengthを返す関数
void exstrcpy(extendstr *(to)[],extendstr from[],int lines);										//アニメーション表示用構造体配列をアドレスの配列に変換する関数
int select_from_list(arrow_pos tmp_pos[10], int length);												//縦方向のリストから選択させる関数
int select_from_hlist(arrow_pos tmp_pos[10], int length);												//横方向のリストから選択させる関数
int select_from_2dlist(int width, int height,arrow_pos tmp_pos[width][height]);	//平面リストから選択させる関数
/* ここまでutil_func.cで定義する関数 */

/* ここからflame_func.cで定義する関数 */
void make_flame(int width, int height, int offset_x, int offset_y);								//指定位置を左上に高さと幅を指定したフレームを作成する関数
void make_vsflame(int width, int height, int offset_x, int offset_y, int split_x);//指定位置を左上に高さと幅と分割位置を指定した横2分割のフレームを作成する関数
void animete_make_flame_speedfix(int width,int height,int x,int y);								//指定位置にフレームをアニメーション付きで表示する関数
void flame_flush();																																//メインフレーム内をアニメーション付きでスペース埋めする関数
void curtain_animation();																																//メインフレーム内をカーテンアニメーション付きでスペース埋めする関数
void flame_clean();																																//メインフレーム内をアニメーションなしでスペース埋めする関数
void sub_flame_clean(int width, int height, int x, int y);												//指定範囲内をアニメーションなしでスペース埋めする関数
int check_window(int width, int height, int x, int y, char *string);							//確認文とy/nの確認フレームを出す関数
/* ここまでflame_func.cで定義する関数 */

/* ここからmap_menu.cで定義する関数 */
void view_status();								//マップメニューでステータスを表示する関数
void item_list_on_map();					//マップメニューでアイテム一覧を表示する関数
int onmap_manu();									//マップメニューを開く関数
void update_map(stage now_stage);	//表示するマップをステージに合わせて更新する関数
/* ここまでmap_menu.cで定義する関数 */


arrow_pos move_on_maze(int width, int height,arrow_pos map_coors[width][height],arrow_pos start_position);
