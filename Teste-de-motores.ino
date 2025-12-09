#define PWM2                      2    // Pino do Arduino que será ligado ao BTS7960 para o motor 1
#define PWM3                      3    // Pino do Arduino que será ligado ao BTS7960 para o motor 1
#define PWM4                      4    // Pino do Arduino que será ligado ao BTS7960 para o motor 2
#define PWM5                      5    // Pino do Arduino que será ligado ao BTS7960 para o motor 2
#define TEMPO_DA_VELOCIDADE       150  // Tempo (ms) que o motor ficará na mesma velocidade

void setup()
{ 
    // Configura os pinos de saída
    pinMode(PWM2, OUTPUT);  // Motor 1, controle de velocidade
    pinMode(PWM3, OUTPUT);  // Motor 1, controle de direção
    pinMode(PWM4, OUTPUT);  // Motor 2, controle de velocidade
    pinMode(PWM5, OUTPUT);  // Motor 2, controle de direção
}
   
void loop()
{   
    int valor_pwm = 100;   // Armazena o PWM inicial
    
    // Controla o motor 1 (PWM2 e PWM3)
    digitalWrite(PWM3, LOW);  // Define a direção do motor 1 para frente (PWM3 é LOW)

    // Aumenta a velocidade do motor 1 até o valor máximo
    for (valor_pwm = 100; valor_pwm < 256; valor_pwm++)
    {
        analogWrite(PWM2, valor_pwm);  // Ajusta a velocidade do motor 1
        delay(TEMPO_DA_VELOCIDADE);    // Aguarda o tempo configurado
    }

    // Controla o motor 2 (PWM4 e PWM5)
    digitalWrite(PWM5, LOW);  // Define a direção do motor 2 para frente (PWM5 é LOW)

    // Aumenta a velocidade do motor 2 até o valor máximo
    for (valor_pwm = 100; valor_pwm < 256; valor_pwm++)
    {
        analogWrite(PWM4, valor_pwm);  // Ajusta a velocidade do motor 2
        delay(TEMPO_DA_VELOCIDADE);    // Aguarda o tempo configurado
    }

    // Agora ambos os motores giram continuamente para frente, com velocidade máxima
    // O motor 1
    while(true)
    {
        analogWrite(PWM2, 255); // Mantém a velocidade máxima do motor 1
        delay(1000); // Aguarda 1 segundo (opcional, pode ser ajustado ou removido)

        // O motor 2
        analogWrite(PWM4, 255); // Mantém a velocidade máxima do motor 2
        delay(1000); // Aguarda 1 segundo (opcional, pode ser ajustado ou removido)
    }
}
