#include <TASKS/taskL.h>
#include <GLOBALS/globals.h>

// Task H (alta priorità)
void doTaskH(void *parameters) {

  TickType_t timestamp;

  // Ciclo infinito
  while (1) {

    // prova a prendere il lock
    Serial.println("Task H prova ad acquisire il lock...");
    timestamp =  pdTICKS_TO_MS( xTaskGetTickCount() );
    xSemaphoreTake(lock, portMAX_DELAY);

    // Stampa il tempo trascorso in attesa del lock
    Serial.printf("Task H ha acquisito il lock. Sono trascorsi %i ms aspettando il lock\n", pdTICKS_TO_MS( xTaskGetTickCount() ) - timestamp);

    // Satura la CPU in un loop per un certo tempo
    Serial.println("Task H esegue il suo compito...");
    timestamp = pdTICKS_TO_MS( xTaskGetTickCount() );
    while ( pdTICKS_TO_MS( xTaskGetTickCount() ) - timestamp < cs_wait);

    // Rilascia il lock
    Serial.println("Task H rilascia il lock.");
    xSemaphoreGive(lock);

    // Si mette in pausa
    vTaskDelay( pdMS_TO_TICKS( 500 ) );
  }
}