//
// Created by Glastis on 03/04/2018.
//

#ifndef LAMP_MAIN_H
#define LAMP_MAIN_H

#pragma GCC diagnostic ignored "-Wwrite-strings"

#include <WiFiClientSecure.h>
#include "OLED.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"

#define UNUSED(X)                           (void)(X)
#define BAUDRATE                            115200u

#define WIFI_SSID                           "ssid"
#define WIFI_PASS                           "pass"
#define IP_LEN                              15


//SCREEN MACRO
#define SCREEN_SIZE_X       128
#define SCREEN_SIZE_Y       64
#define OFFSET_X            0
#define OFFSET_Y            0
#define CHAR_X              8
#define CHAR_Y              8
#define MAXX                ((SCREEN_SIZE_X) - ((OFFSET_X) * (CHAR_X)))
#define MAXY                ((SCREEN_SIZE_Y) - ((OFFSET_Y) * (CHAR_Y)))
#define MAX_CHAR_PER_LINE   ((MAXX) / (CHAR_X))
#define MAX_LINES           ((MAXY) / (CHAR_Y))
#define MAX_CHAR            ((MAX_CHAR_PER_LINE) * (MAX_LINES))
#define PIN_SDA             4
#define PIN_SCL             5

//BUTTONS ADDRESS
#define BUTTON_UP           0x2000
#define BUTTON_DOWN         0x100
#define BUTTON_LEFT         0x800
#define BUTTON_RIGHT        0x1000
#define BUTTON_OK           0x8000
#define BUTTON_BACK         0x4000

//MAIN MENU
const char MENU_TITLE[] =       "Main";
const char MENU_LINE_1[] =      "Connect wifi";
#define MENU_CONNECT_WIFI       0
const char MENU_LINE_2[] =      "Deauth all";
#define MENU_DEAUTH_ALL         1
const char MENU_LINE_3[] =      "Sniff wifi";
#define MENU_SNIFF_WIFI         2
const char MENU_LINE_4[] =      "";
const char MENU_LINE_5[] =      "";
const char MENU_NIY[] =         "Feature not     implemented";
#define MENU_NAX_LINE_BUFF      6
#define MENU_OFFSET_Y           2
#define CURSOR_POS_X            0
const char CURSOR_LOOK[] =      " >";
const char NO_CURSOR_LOOK[] =   "  ";

#define USER_AGENT          "curl/7.47.0"
#define SSL_PORT            443
#define REFRESH_DELAY       150

#define DEBUG_MODE

typedef struct  s_menu
{
  int           writed;
  int           pos;
  const char    *in_menu;
  int           moved;
  int           max_pos;
  const char    *menu_lines[MENU_NAX_LINE_BUFF];
}               t_menu;

typedef struct  s_coord
{
  int           x;
  int           y;
}               t_coord;


/* screen.cpp */
int             comp_str(const char *str1, const char *str2);
int             compare_str_beg(const char *str1, const char *str2);
void            write_epur(t_coord *coord, const char *str);
void            write_string(t_coord *coord, String str);
void            write_newline(t_coord *coord, const char *str);
void            write(t_coord *coord, const char *str);
void            clear_screen(t_coord *coord);
void            init_coord(t_coord *coord);
void            new_line(t_coord *coord);
void            add_to_coords(t_coord *coord, int x, int y);
void            write_raw(const char *str, int x, int y);

/* connection.cpp */
void            try_reconnect(t_coord *coord);
void            check_connection(t_coord *coord);

/* buttons.cpp */
int             is_pressed(uint16_t all, uint16_t button);
int             get_address();
uint16_t        pcf8575_read(int address);
void            pcf8575_write(uint16_t dt, int address);

/* menu.cpp */
void            main_menu(t_coord *coord, uint16_t input);


#endif //LAMP_MAIN_H
