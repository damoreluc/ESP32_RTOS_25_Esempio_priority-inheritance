#include <TASKS/taskL.h>
#include <GLOBALS/globals.h>

// Task M (Media priorità)
void doTaskM(void *parameters) {

  TickType_t timestamp;

  // Ciclo infinito
  while (1) {
    
    // Satura la CPU in un loop per un certo tempo
    Serial.println("Task M esegue il suo compito...");
    timestamp = pdTICKS_TO_MS( xTaskGetTickCount() );
    while ( pdTICKS_TO_MS( xTaskGetTickCount() ) - timestamp < med_wait);

    // Si mette in pausa
    Serial.println("Task M terminato");
    vTaskDelay( pdMS_TO_TICKS( 500 ) );
  }
}