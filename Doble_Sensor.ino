// Pines de los sensores PIR
const int PIR1_PIN = 5;  // Sensor PIR 1
const int PIR2_PIN = 4;  // Sensor PIR 2

// Variables para guardar el estado de los sensores
bool estadoPIR1 = LOW;
bool estadoPIR2 = LOW;

void setup() {
  // Configurar los pines de los sensores PIR como entrada
  pinMode(PIR1_PIN, INPUT);
  pinMode(PIR2_PIN, INPUT);

  // Iniciar comunicación serial para depuración
  Serial.begin(115200);
  Serial.println("Sistema de detección de entrada/salida listo.");
}

void loop() {
  // Leer el estado de los sensores PIR
  int lecturaPIR1 = digitalRead(PIR1_PIN);
  int lecturaPIR2 = digitalRead(PIR2_PIN);

  // Detectar si PIR1 se activa primero y luego PIR2 (indica entrada)
  if (lecturaPIR1 == HIGH && estadoPIR1 == LOW) {
    // PIR 1 detecta primero
    Serial.println("PIR 1 activado, esperando PIR 2...");
    estadoPIR1 = HIGH;  // Guardar el estado de PIR 1
  

    if (lecturaPIR2 == HIGH && estadoPIR1 == HIGH) {
      // PIR 2 se activa después de PIR 1, indica entrada
      Serial.println("Persona ha ENTRADO.");
      estadoPIR1 = LOW;  // Reiniciar los estados
      estadoPIR2 = LOW;
    }
  }
  // Detectar si PIR2 se activa primero y luego PIR1 (indica salida)
  if (lecturaPIR2 == HIGH && estadoPIR2 == LOW) {
    // PIR 2 detecta primero
    Serial.println("PIR 2 activado, esperando PIR 1...");
    estadoPIR2 = HIGH;  // Guardar el estado de PIR 2


    if (lecturaPIR1 == HIGH && estadoPIR2 == HIGH) {
      // PIR 1 se activa después de PIR 2, indica salida
      Serial.println("Persona ha SALIDO.");
      estadoPIR1 = LOW;  // Reiniciar los estados
      estadoPIR2 = LOW;
    }
  }

  // Agregar un pequeño retraso para la estabilidad del sistema
  delay(3000);
}
