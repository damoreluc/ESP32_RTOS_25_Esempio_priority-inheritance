#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <Arduino.h>
// Impostazioni
// durata simulata della sezione critica (ms)
extern TickType_t cs_wait;  
// durata del task intermedio Task M (ms)
extern TickType_t med_wait;

// Variabili Globali
extern SemaphoreHandle_t lock; 
#endif
