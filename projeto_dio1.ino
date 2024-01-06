// Definição dos pinos utilizados
const int sensorTemperatura = A0;  // Pino analógico do sensor de temperatura
const int pinoMotor = 9;           // Pino para o controle do motor
const int pinoLED = 12;            // Pino para o LED
const int pinoBuzzer = 11;         // Pino para o buzzer

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  pinMode(pinoMotor, OUTPUT);
  pinMode(pinoLED, OUTPUT);
  pinMode(pinoBuzzer, OUTPUT);
}

void loop() {
  int temperatura = lerTemperatura();
  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  // Verifica a temperatura e toma ações baseadas nos valores
  if (temperatura >= 30 && temperatura < 50) {
    acionarVentilador();  // Aciona o motor do ventilador
  } else if (temperatura >= 50) {
    emergencia();  // Ativa o LED vermelho e o buzzer em caso de emergência
  } else {
    desligarComponentes();  // Desliga todos os componentes
  }

  delay(1000);  // Aguarda 1 segundo antes de fazer a próxima leitura
}

int lerTemperatura() {
  int valorSensor = analogRead(sensorTemperatura);
  float tensao = (valorSensor * 5.0) / 1024.0;  // Tensão do sensor
  float temperaturaC = (tensao * 100.0);  // Conversão para temperatura em Celsius
  return temperaturaC;
}

void acionarVentilador() {
  digitalWrite(pinoMotor, HIGH);  // Liga o motor do ventilador
  digitalWrite(pinoLED, LOW);     // Garante que o LED está desligado
  digitalWrite(pinoBuzzer, LOW);  // Garante que o buzzer está desligado
}

void emergencia() {
  digitalWrite(pinoLED, HIGH);    // Liga o LED vermelho
  tone(pinoBuzzer, 1000);         // Ativa o buzzer em frequência de 1000 Hz
  delay(1000);                    // Espera por um segundo
  noTone(pinoBuzzer);             // Desliga o buzzer
  delay(1000);                    // Espera por um segundo
}

void desligarComponentes() {
  digitalWrite(pinoMotor, LOW);   // Desliga o motor do ventilador
  digitalWrite(pinoLED, LOW);     // Desliga o LED
  noTone(pinoBuzzer);             // Desliga o buzzer
}