//
// Created by Glastis on 08/04/2018.
//

#include <string.h>
#include "main.h"

extern OLED display;

int             comp_str(const char *str1, const char *str2)
{
    int         i;

    i = 0;
    while (str1[i] && str2[i] && str1[i] == str2[i])
    {
        ++i;
    }
    return (str1[i] == str2[i] || !str2[i]);
}

static void     check_endline(t_coord *coord)
{
  if (coord->y >= MAX_LINES)
  {
    clear_screen(coord);
  }
}

static int      write_word(t_coord *coord, char *str)
{
  unsigned int  i;
  unsigned int  ended;
  
  i = 0;
  ended = 0;
  while (str[i] && str[i] != ' ')
  {
    i = i + 1;
  }
  if (i + coord->x + 1 >= MAX_CHAR_PER_LINE)
  {
    new_line(coord);
    if (str[i])
    {
      str[i] = '\0';
    }
    else
    {
      ended = 1;
    }
  }
  else
  {
    write(coord, " ");
  }
  write(coord, str);
  if (ended)
  {
    str[i] = ' ';
  }
  return i;
}

int             compare_str_beg(const char *str1, const char *str2)
{
  unsigned int  i;

  i = 0;
  while (str1[i] && str2[i])
  {
    if (str1[i] != str2[i])
    {
      return (-1);
    }
    ++i;
  }
  return (0);
}

void            write_epur(t_coord *coord, char *str)
{
  unsigned int  i;
  
  i = 0;
  while (str[i])
  {
    while (str[i] == ' ')
    {
      ++i;
    }
    if (str[i])
    {
      i += write_word(coord, &str[i]);
    }
  }
}

void            write_string(t_coord *coord, String str)
{
  display.print((char *)str.c_str(), coord->y, coord->x);
  add_to_coords(coord, str.length(), 0);
}

void            write_newline(t_coord *coord, char *str)
{
  write(coord, str);
  new_line(coord);
}
void            write(t_coord *coord, char *str)
{
  display.print(str, coord->y, coord->x);
  add_to_coords(coord, strlen(str), 0);
}

void            clear_screen(t_coord *coord)
{
  init_coord(coord);
  display.clear();
}

void            init_coord(t_coord *coord)
{
  coord->x = OFFSET_X;
  coord->y = OFFSET_Y;
}

void            new_line(t_coord *coord)
{
  coord->x = OFFSET_X;
  coord->y += 1;
  check_endline(coord);
}

void            add_to_coords(t_coord *coord, int x, int y)
{
  coord->x += x;
  coord->y += y;
  while (coord->x >= MAX_CHAR_PER_LINE)
  {
    coord->x -= MAX_CHAR_PER_LINE;
    coord->y += 1;
  }
  if (coord->x < OFFSET_X)
  {
    coord->x = OFFSET_X;
  }
  check_endline(coord);
}
