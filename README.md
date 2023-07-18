# ESP32_RTOS_25_Esempio priority inheritance

## FreeRTOS Esercizio 25: Esempio illustrativo della ereditarietà di priorità.

Si considerano tre task: __Task H__ ad alta priorità, __Task M__ a media priorità e __Task L__ a bassa priorità.

__Task L__ e __Task H__ utilizzano un lock per arbitrare l'accesso alla medesima risorsa condivisa.

L'inversione di priorità illimitata (_Unbouded Priority Inversion_) si verifica quando il task
con priorità media (__Task M__) interrompe il task a bassa priorità (__Task L__) che sta tenendo bloccato un lock.

Se il __Task H__ ad alta priorità tenta di acquisire il lock, rimarrà bloccato (in cascata) fino a quando
il __Task L__ non rilascerà il lock.

Si chiama "illimitato" perché il __Task M__ può bloccare il __Task H__ per qualsiasi periodo di tempo,
poiché il __Task M__ sta bloccando il __Task L__ (che detiene ancora il semaforo).

Si risolve sostituendo il semaforo con un __mutex__, poiché in FreeRTOS i mutex sono implementati con
l'algoritmo di ereditarità della priorità:

il __Task L__ prende il lock. Solo quando il __Task H__ tenta di prendere il lock, la priorità del __Task L__ 
viene aumentata a quella del __Task H__. Ancora una volta, il __Task M__ non può più interrompere il ___Task L__ 
fino al completamento di entrambe le attività nella sezione critica.