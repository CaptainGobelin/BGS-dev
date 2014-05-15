#ifndef CONST_H
#define CONST_H

//Paths
#define OPTION_PATH "usr/ini.txt"
#define TEXTURES_PATH "dat/"
#define SAVE_PATH "usr/sav/"
#define WORLD_PATH "usr/world/"
#define FONT_PATH "dat/font/"

//Window
#define T_TILES 28
#define L_WINDOW 992
#define H_WINDOW 672

//Inputs
#define INVALID_INPUT 0
#define CLOSE_INPUT 1
#define ANY_KEY_INPUT 2
#define UP_INPUT 3
#define DOWN_INPUT 4
#define LEFT_INPUT 5
#define RIGHT_INPUT 6
#define M_INPUT 7
#define ENTER_INPUT 8
#define ESCAPE_INPUT 9
#define DELETE_INPUT 10
#define Q_INPUT 11
#define Y_INPUT 12
#define N_INPUT 13

//Menu inputs
#define INIT_CHOICE 10
#define TO_SESSION 11
#define TO_MAIN_MENU 12
#define TO_GAME_SESSION 13
#define TO_CONTINUE 14
#define REDO 15

//Messages
#define MESS_LINES 21
#define MESS_SPACE 11
#define MESS_X 30
#define MESS_Y 138

//Races
#define UNDEFINED_CODE 0
#define HUMAN_CODE 1

//Map Prototype Cells
#define IS_SOLID 0
#define WALL_ITEM -2
#define WALL -1
#define FLOOR 1
#define DOOR 2

//Cells
#define CHANGE_MAP_CODE 1000
#define NOTHING_CODE 0
#define DUNGEON_WALL_A 1
#define DUNGEON_FLOOR_A 2
#define DUNGEON_EXIT 3
#define CAVERN_WALL_A 4
#define CAVERN_FLOOR_A 5
#define GRASS_A 6
#define TREE_A 7
#define DUNGEON_WALL_ITEM_A 8

//Save File
#define END_OF_FILE -99999

//Atributes
#define ATTR_VIEW 0

//Items
#define DEFAULT_ITEM -1
#define SWORD_1H_A 1
#define GREAVES_L_A 2

//Obstacles
#define DEFAULT_OBSTACLE -1
#define TABLE_A 1

#endif