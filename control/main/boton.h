#ifndef BOTON_H
#include <stdint.h>
#define BOTON_H

void init_boton(void);
/* int boton_read(); */

uint32_t button_debounce_time(void);

#endif