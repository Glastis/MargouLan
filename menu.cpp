#include "main.h"

static int      add_pos(int pos, int add, int max_pos)
{
  pos += add;
  if (pos < 0)
  {
    return 0;
  }
  if (pos >= (max_pos))
  {
    return (max_pos) - 1;
  }
  return pos;
}

static void     write_menu(t_coord *coord, const char *title, const char **options)
{
  int           i;
  
  i = 0;
  clear_screen(coord);
  write(coord, title);
  while (i < MENU_OFFSET_Y)
  {
    new_line(coord);
    ++i;
  }
  i = 0;
  while (options && options[i])
  {
    write(coord, NO_CURSOR_LOOK);
    write(coord, options[i]);
    new_line(coord);
    ++i;
  }
}

static void     write_cursor(int pos, int max_pos)
{
  int           i;

  i = 0;
  if (max_pos == 0)
  {
    return;
  }
  while (i < max_pos)
  {
    if (i != pos)
    {
      write_raw(NO_CURSOR_LOOK, CURSOR_POS_X, i + MENU_OFFSET_Y);
    }
    ++i;
  }
  write_raw(CURSOR_LOOK, CURSOR_POS_X, pos + MENU_OFFSET_Y);
}

static void           init_menu(t_menu *menu)
{
  menu->menu_lines[0] = MENU_LINE_1;
  menu->menu_lines[1] = MENU_LINE_2;
  menu->menu_lines[2] = MENU_LINE_3;
  menu->menu_lines[3] = MENU_LINE_4;
  menu->menu_lines[4] = MENU_LINE_5;
  menu->menu_lines[5] = NULL;
  menu->max_pos = 3;
  menu->moved = 0;
  menu->in_menu = MENU_TITLE;
  menu->pos = 0;
  menu->writed = 0;
}

void                  main_menu(t_coord *coord, uint16_t input)
{
  static t_menu       menu;
  static int          init;
  int                 moved;

  if (init == 0)
  {
    init = 1;
    init_menu(&menu);
  }
  if (is_pressed(input, BUTTON_UP))
  {
    menu.pos = add_pos(menu.pos, -1, menu.max_pos);
    moved = 1;
  }
  if (is_pressed(input, BUTTON_DOWN))
  {
    menu.pos = add_pos(menu.pos, +1, menu.max_pos);
    moved = 1;
  }
  if (is_pressed(input, BUTTON_OK) && menu.in_menu == MENU_TITLE)
  {
    if (menu.pos == MENU_CONNECT_WIFI || menu.pos == MENU_DEAUTH_ALL || menu.pos == MENU_SNIFF_WIFI)
    {
      menu.in_menu = menu.menu_lines[menu.pos];
      menu.menu_lines[0] = MENU_NIY;
      menu.menu_lines[1] = NULL;
      menu.max_pos = 0;
      menu.pos = 0;
      menu.writed = 0;
    }
  }
  if (is_pressed(input, BUTTON_BACK))
  {
    init_menu(&menu);
    moved = 1;
  }
  if (!menu.writed)
  {
    write_menu(coord, menu.in_menu, menu.menu_lines);
    menu.writed = 1;
    moved = 1;
  }
  if (moved)
  {
    write_cursor(menu.pos, menu.max_pos);
  }
}

