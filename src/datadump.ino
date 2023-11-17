#include <Ultrasonic.h>
#include "HX711.h"

const int echoPin = 25; // Pino digital utilizado pelo HC-SR04 Echo (recebe)
const int trigPin = 14; // Pino digital utilizado pelo HC-SR04 Trig (envia)

const int dtPin = 15;   // Pino digital do ESP32 conectado ao DT do HX711
const int sckPin = 5;   // Pino digital do ESP32 conectado ao SCK do HX711

const float profundidade = 18.8;
const float largura = 11;

Ultrasonic ultrasonic(trigPin, echoPin); // Inicializando os pinos do ESP32 para o sensor ultrassônico
HX711 scale;

void setup() {
  Serial.begin(115200); // Inicializa a porta serial
  scale.begin(dtPin, sckPin); // Inicializa o HX711 com os pinos corretos

  // Calibrar a célula de carga
  Serial.println("Inicie a calibracao. Por favor, coloque a massa conhecida na celula de carga...");
  delay(2000);
  scale.set_scale(); // Zera a escala (tara)

  // Coloque a massa conhecida na célula de carga
  Serial.println("Aguarde 10 segundos...");
  delay(10000);

  // Obtenha a leitura do HX711 após 10 segundos
  float peso = scale.get_units(10);

  // Configure a escala do HX711 para gramas
  scale.set_scale(peso / 1000.0); // Convertendo para gramas
  Serial.println("Calibracao concluida!");
}

void loop() {
  // Mede a distância em centímetros
  float distancia = ultrasonic.read(CM);

  // Mede o peso em gramas
  float peso = scale.get_units(10); // 10 leituras para suavizar o resultado

 float volume  = profundidade * largura * distancia;
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.print(" cm | Peso: ");
  Serial.print(peso);
  Serial.print(" g | Volume:");
  Serial.print(volume/1000);
  Serial.println(" m³");

  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}
