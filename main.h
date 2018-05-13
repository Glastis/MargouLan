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

#define USER_AGENT          "curl/7.47.0"
#define SSL_PORT            443
#define REFRESH_DELAY       250

#define DEBUG_MODE

typedef struct {
  int    x;
  int   y;
} t_coord;


/* screen.cpp */
int             comp_str(const char *str1, const char *str2);
int             compare_str_beg(const char *str1, const char *str2);
void            write_epur(t_coord *coord, char *str);
void            write_string(t_coord *coord, String str);
void            write_newline(t_coord *coord, char *str);
void            write(t_coord *coord, char *str);
void            clear_screen(t_coord *coord);
void            init_coord(t_coord *coord);
void            new_line(t_coord *coord);
void            add_to_coords(t_coord *coord, int x, int y);

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
