#ifndef __USER_DETECTION_TASK__
#define __USER_DETECTION_TASK__

#include "Task.h"
#include "Pir.h"

// Funzione: Rileva la presenza di un utente davanti al contenitore tramite il sensore PIR (USER DETECTOR).
// Stato iniziale: Il sistema è in sleep mode per risparmiare energia.
// Azioni:
// - Risveglia il sistema quando un utente viene rilevato.
// - Attiva il display e gli altri componenti.

class UserDetectionTask : public Task {
  int pirPin;

public:
  UserDetectionTask(int pirPin);
  void init(int period);
  void tick();
};

#endif