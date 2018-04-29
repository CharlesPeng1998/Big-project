/*1751367 º∆2 ≈ÌΩ°¥œ*/
#pragma once

void one_check_mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char &input_alpha, int &input_num);
void mark2(int matrix1[][10], char matrix2[][10], int cord_row, int cord_col, int Max_row, int Max_col);
void two_check_mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char &input_alpha, int &input_num);
void input_rcg(int &row, int &col, int &goal);
void three_cmd_combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, char &input_alpha, int &input_num, int &score, int &total_score,int goal);
int combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char input_alpha, int input_num);
void fill_rmatrix(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col);
void print_color_zero(int(*rand_matrix)[10], int row, int col);
bool win_check(int(*rand_matrix)[10], int row, int col, int &goal);
void four_cmd_complete(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, char &input_alpha, int &input_num, int &score, int &total_score, int goal);
void five_GUI_dsp_undvd(int(*rand_matrix)[10], int row, int col);
void six_GUI_dsp_dvd(int(*rand_matrix)[10], int row, int col);
void seven_kb_choose(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col);
void eight_GUI_combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &goal,int &score, int &total_score);
void kb_move(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col);
int kb_confirm();
void print_shiny(int value, int cord_x, int cord_y);
int GUI_combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int curr_row, int curr_col);
void nine_GUI_complete(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &goal, int &score, int &total_score);
void kb_mouse_move(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col);

void GUI_full_cfg(char *cfgfile_name);

int read_game_cfg(const char *cfg_name, Game_area &game_area, Block &block, Block_color &block_color);