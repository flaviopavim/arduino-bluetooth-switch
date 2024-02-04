/*

    Controlador Bluetooth pra Arduino pro Mini
    Feito para dispositivos WhiteHats ou compatíveis
    Aplicativo pra controle:
        https://play.google.com/store/apps/details?id=br.com.whitehats.bluetooth

    Feito pra ligar e forçar desligamento de computadores 
    ou dispositivos que desligam ao segurar o botão de power

    Conectar o Relê no botão de power do computador

*/

bool bool_on=false;
int port = 2;

void on() {
    bool_on=true;
    digitalWrite(port, HIGH);
    delay(1000);
    digitalWrite(port, LOW);
    delay(1000);
    digitalWrite(13, HIGH);
}

void off() {
    bool_on=false;
    digitalWrite(port, HIGH);
    delay(6000);
    digitalWrite(port, LOW);
    delay(1000);
    digitalWrite(13, LOW);
}

void toggle() {
    if (bool_on) {
        off();
    } else {
        on();
    }
    bool_on=!bool_on;
}


String value = "";
void setup() {
    Serial.begin(9600);
    pinMode(port,OUTPUT);
    pinMode(13,OUTPUT);
}

void loop() {
    // se o Bluetooth tiver ativo
    if (Serial.available() > 0) {
        // lê cada char que o Bluetooth envia
        char c = Serial.read();
        // printa cada char que passa no Bluetooth
        Serial.println(c);
        if (c) {
            // Exemplos de strings pra receber: *12., *13., *A1.
            if (c == '*') {
                // aqui é o início da string, limpa value
                value = "";
            } else if (c == '.') {
                // quando receber . é o fim da instrução. compara value pra saber qual porta ligar ou desligar
                if (value=="2") {
                    // liga ou desliga as portas digitais
                    toggle();
                }
                // limpa a variável pra escrever a próxima instrução
                value = "";
            } else {
                // não é o início nem o fim, concatena o char na string (junta a letra na string)
                value += c;
            }
        }
    }
}