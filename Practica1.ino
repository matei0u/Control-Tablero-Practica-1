#include <Controllino.h>

// --- Variables de tiempo ---
unsigned long t_previo = 0;     // Guarda tiempo del último cambio
unsigned long intervalo = 500;  // Tiempo de espera (ms)

// --- Configuración de LEDs ---
int numeros[9] = {              // Lista de pines en orden
  CONTROLLINO_D0, CONTROLLINO_D6, CONTROLLINO_D12,
  CONTROLLINO_D13, CONTROLLINO_D14, CONTROLLINO_D8,
  CONTROLLINO_D2, CONTROLLINO_D1, CONTROLLINO_D7
};

// Calcula cuántos LEDs hay
const int N_LEDS = sizeof(numeros) / sizeof(numeros[0]);

// --- Variables de control ---
int idx = 0;        // LED actual (0, 1, 2...)
int prev_idx = -1;  // LED anterior
int *ptr = numeros; // Puntero al LED actual

void setup() {
  // Configura todos los pines como SALIDA
  pinMode(CONTROLLINO_D0, OUTPUT);
  pinMode(CONTROLLINO_D1, OUTPUT);
  pinMode(CONTROLLINO_D2, OUTPUT);
  pinMode(CONTROLLINO_D6, OUTPUT);
  pinMode(CONTROLLINO_D7, OUTPUT);
  pinMode(CONTROLLINO_D8, OUTPUT);
  pinMode(CONTROLLINO_D12, OUTPUT);
  pinMode(CONTROLLINO_D13, OUTPUT);
  pinMode(CONTROLLINO_D14, OUTPUT);

  
  ptr = numeros + idx;      // Apunta al primer LED
  digitalWrite(*ptr, HIGH); // Enciende el primer LED

  prev_idx = idx;
  t_previo = millis();      // Inicia el cronómetro
}

void loop() {
  unsigned long t_actual = millis(); // Tiempo actual

  // Comprueba si ya pasaron 500ms
  if (t_actual - t_previo >= intervalo) {
    
    // Apaga el LED anterior
    if (prev_idx >= 0) {
      int *prev_ptr = numeros + prev_idx;
      digitalWrite(*prev_ptr, LOW);
    }

    // Avanza al siguiente LED (y vuelve a 0 si llega al final)
    idx = (idx + 1) % N_LEDS;

    ptr = numeros + idx;      // Apunta al nuevo LED
    digitalWrite(*ptr, HIGH); // Enciende el nuevo LED

    prev_idx = idx;       // Guarda el LED actual como "anterior"
    t_previo = t_actual;  // Reinicia el cronómetro
  }
}