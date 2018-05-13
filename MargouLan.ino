//
// Created by Glastis on 08/04/2018.
//

#include <Wire.h>
#include "main.h"

OLED        display(PIN_SCL, PIN_SDA);
t_coord     coord;
char        buffer[20];

int         address;

void setup() {
//    char      tmpip[IP_LEN];

  init_coord(&coord);
  display.begin();
#ifdef DEBUG_MODE
  Serial.begin(BAUDRATE);
#endif
//  WiFi.begin(WIFI_SSID, WIFI_PASS);
//  check_connection(&coord);
//  memcpy(tmpip, (const void *)WiFi.localIP().toString().c_str(), IP_LEN);
//  new_line(&coord);
//  write(&coord, "IP:");
//  new_line(&coord);
//  write(&coord, tmpip);
  address = get_address();
  if (address == -1)
  {
    clear_screen(&coord);
    write(&coord, "Error: no i2c peripheral found. Hanging now.");
    delay(2000000);
  }
  pcf8575_write(word(B00000000,B00000000), address);
  write(&coord, "  Booting...");
  delay(1000);
  clear_screen(&coord);
}

void loop() {
  main_menu(&coord, pcf8575_read(address));
  delay(REFRESH_DELAY);
}

