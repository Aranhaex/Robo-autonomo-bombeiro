#include <Servo.h>

// === SERVOS ===
Servo garra;
Servo braco;

// Pinos dos servos
int PINO_GARRA = A1;   
int PINO_BRACO = A2;

// === ULTRASSÔNICO ===
const int TRIG = 13;
const int ECHO = A0;

// === MOTORES (ponte H) ===
int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;

// === SENSORES DE LINHA ===
const int SENSOR_ESQ = 10;
const int SENSOR_CEN = 11;
const int SENSOR_DIR = 12;

// === Função medir distância ===
long medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracao = pulseIn(ECHO, HIGH, 30000);
  long distancia = duracao * 0.0343 / 2;
  return distancia;
}

// === MOVIMENTOS ===
void pararMotores() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void esquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void direita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// === AÇÃO DE PEGAR OBJETO ===
void pegarObjeto() {

  pararMotores();

  // Levanta o braço
  braco.write(130);
  delay(700);

  // Abre a garra
  garra.write(50);
  delay(500);

  // Desce braço
  braco.write(40);
  delay(700);

  // Fecha garra
  garra.write(120);
  delay(600);

  // Levanta objeto
  braco.write(130);
  delay(700);
}

void setup() {
  Serial.begin(9600);

  // Motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Sensores
  pinMode(SENSOR_ESQ, INPUT);
  pinMode(SENSOR_CEN, INPUT);
  pinMode(SENSOR_DIR, INPUT);

  // Ultrassônico
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Servos
  garra.attach(PINO_GARRA);
  braco.attach(PINO_BRACO);

  // Posições iniciais (evita estralos)
  garra.write(90);
  braco.write(130);
}

void loop() {
  int esq = digitalRead(SENSOR_ESQ);
  int cen = digitalRead(SENSOR_CEN);
  int dir = digitalRead(SENSOR_DIR);

  long distancia = medirDistancia();

  // === Evita servos ficarem fazendo força (estralando) ===
  garra.detach();
  braco.detach();

  // === OBJETO DETECTADO ===
  if (distancia > 0 && distancia <= 10) {
    pararMotores();

    // Ativar servos somente agora
    garra.attach(PINO_GARRA);
    braco.attach(PINO_BRACO);

    pegarObjeto();

    garra.detach();
    braco.detach();

    return;
  }

  // === SEGUIDOR DE LINHA ===
  if (cen == 0 && esq == 1 && dir == 1) {
    frente();
  }
  else if (esq == 0) {
    esquerda();
  }
  else if (dir == 0) {
    direita();
  }
  else {
    frente();
  }
}
