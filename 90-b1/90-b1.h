/*1751367 º∆2 ≈ÌΩ°¥œ*/
#pragma once




void eliminate(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col);
int elmn_score(char(*mark_matrix)[10], int row, int col);
int remain_num(int(*rand_matrix)[10], int row, int col);
void move(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type);
void GUI_eliminate(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col);
void block_left(int(*rand_matrix)[10], int row, int col);
int enter_click(int bnt);
int elmn_fall(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &curr_row, int &curr_col, int &score, int &total_score,int question);


void A_find_mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, char &input_alpha, int &input_num);
void B_eliminate(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, char &input_alpha, int &input_num, int &score, int &total_score);
void C_cmd_complete(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, char &input_alpha, int &input_num, int &score, int &total_score);
void D_GUI_choose_undvd(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &score, int &total_score);
void E_GUI_choose_dvd(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &score, int &total_score);
void F_GUI_eliminate(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &score, int &total_score,int question);
void G_GUI_complete(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &score, int &total_score);

void GUI_full_cfg(const char *cfgfile_name);
void GUI_eliminate_cfg(Game_area &game_area, Block block, Block_color block_color);
int elmn_fall_cfg(Game_area &game_area, Block block, Block_color block_color,int &score);
void block_left_cfg(Game_area &game_area, Block block, Block_color block_color);
int read_game_cfg(const char *cfg_name, Game_area &game_area, Block &block, Block_color &block_color);