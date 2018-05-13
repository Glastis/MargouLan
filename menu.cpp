#include "main.h"

static int      add_pos(int pos, int add)
{
  int           max;

  max = 3
  pos += add;
  if (pos < (OFFSET_Y))
  {
    pos = OFFSET_Y;
  }
  if (pos > max)
  {
    pos = max;
  }
  return pos;
}

static void     write_menu(int pos)
{
  
}

void            main_menu(t_coord *coord, uint16_t input)
{
  static int    pos;

  if (is_pressed(input, BUTTON_UP))
  {
    pos = add_pos(pos, -1);
  }
  if (is_pressed(input, BUTTON_DOWN))
  {
    pos = add_pos(pos, +1);
  }
  write_menu(pos);
}

