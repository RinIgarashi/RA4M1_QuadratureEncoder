#include <Arduino.h>
#include <RA4M1_QuadratureEncoder.h>

// GPT1, 32bit timer
// PinA: P105 (R4 Minima: D2 /  R4 WiFi: D3)
// PinB: P104 (R4 Minima: D3 /  R4 WiFi: D2)
QuadratureEncoder encoder(1, 105, 104);
// QuadratureEncoder encoder(1, PORT_PIN(1, 5), PORT_PIN(1, 4)); // Alternative using PORT_PIN macro

void setup() {
    Serial.begin(115200);
    encoder.begin();
    Serial.println("RA4M1 QuadratureEncoder example started.");
}

void loop() {
    Serial.println(encoder.read());

    if (Serial.available()) {
        char c = Serial.read();
        if (c == 'z') {
            encoder.write(0);
            Serial.println("Counter reset to 0.");
        }
    }

    delay(100);
}
