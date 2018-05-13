//
// Created by Glastis on 08/04/2018.
//

#include "main.h"

void            try_reconnect(t_coord *coord)
{
  while (WiFi.status() != WL_CONNECTED)
  {
     write(coord, ".");
     delay(500);
  }
  new_line(coord);
  write(coord, "Connected.");
}

void            check_connection(t_coord *coord)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    clear_screen(coord);
    write(coord, "Connection lost.");
    new_line(coord);
    write(coord, "Reconnecting");
    try_reconnect(coord);
  }
}

