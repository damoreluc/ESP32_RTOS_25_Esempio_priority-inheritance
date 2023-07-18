/*
 * FreeRTOS Esercizio 25: Esempio illustrativo della ereditarietà di priorità.
 *
 * Si considerano tre task: Task H ad alta priorità, Task M a media priorità e Task L a bassa priorità.
 *
 * Task L e Task H utilizzano un lock per arbitrare l'accesso alla medesima risorsa condivisa.
 *
 * L'inversione di priorità illimitata (Unbouded Priority Inversion) si verifica quando il task
 * con priorità media (Task M) interrompe il task a bassa priorità (Task L) che sta tenendo bloccato un lock.
 * Se il Task H ad alta priorità tenta di acquisire il lock, rimarrà bloccato (in cascata) fino a quando
 * il Task L non rilascerà il lock.
 *
 * Si chiama "illimitato" perché il Task M può bloccare il Task H per qualsiasi periodo di tempo,
 * poiché il Task M sta bloccando il Task L (che detiene ancora il semaforo).
 * 
 * Si risolve sostituendo il semaforo con un mutex, poiché in FreeRTOS i mutex sono implementati con
 * l'algoritmo di ereditarità della priorità: 
 * il Task L prende il lock. Solo quando il Task H tenta di prendere il blocco, la priorità del Task L 
 * viene aumentata a quella del Task H. Ancora una volta, il Task M non può più interrompere il Task L 
 * fino al completamento di entrambe le attività nella sezione critica. 
 *
 * Nota: nel file soc.h sono definiti i riferimenti ai due core della ESP32:
 *   #define PRO_CPU_NUM (0)
 *   #define APP_CPU_NUM (1)
 *
 * Qui viene adoperata la APP_CPU
 *
 */

#include <Arduino.h>
#include <GLOBALS/globals.h>
#include <TASKS/taskL.h>
#include <TASKS/taskM.h>
#include <TASKS/taskH.h>

// Impostazioni  **************************************************************
// durata simulata della sezione critica (ms)
TickType_t cs_wait = 250;
// durata del task intermedio Task M (ms)
TickType_t med_wait = 5000; // Time medium task spends working (ms)

// Variabili Globali  **********************************************************
// lock della sezione critica
SemaphoreHandle_t lock;

//************************************************************************************
// Main (sul core 1, con priorità 1)

// configurazione del sistema
void setup()
{
  // Configurazione della seriale
  Serial.begin(115200);

  // breve pausa
  vTaskDelay(pdMS_TO_TICKS(1000));
  Serial.println();
  Serial.println("FreeRTOS Esempio di unbounded priority inversion risolto con Priority Inheritance");

  // crea il mutex per la l'accesso alla sezione critica in TaskL e TaskH
  lock = xSemaphoreCreateMutex();

  // Crea e avvia i tre task; rispettare l'ordine di avvio per verificare la priority inversion
  // Start Task L (bassa priorità)
  xTaskCreatePinnedToCore(doTaskL,
                          "Task L",
                          3072,
                          NULL,
                          1,
                          NULL,
                          APP_CPU_NUM);

  // Introduce un breve ritardo per innescare la priority inversion
  vTaskDelay(pdMS_TO_TICKS(1));

  // Start Task H (alta priorità)
  xTaskCreatePinnedToCore(doTaskH,
                          "Task H",
                          3072,
                          NULL,
                          3,
                          NULL,
                          APP_CPU_NUM);

  // Start Task M (media priorità)
  xTaskCreatePinnedToCore(doTaskM,
                          "Task M",
                          3072,
                          NULL,
                          2,
                          NULL,
                          APP_CPU_NUM);

  // Elimina il task con "Setup e Loop"
  vTaskDelete(NULL);
}

void loop()
{
  // lasciare vuoto
}
