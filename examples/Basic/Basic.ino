#include <Arduino.h>
#include <RA4M1_QuadratureEncoder.h>

// GPT1, 32bit timer
// PinA: P105 (UNO R4 Minima: D2)
// PinB: P104 (UNO R4 Minima: D3)
QuadratureEncoder encoder(1, 105, 104);

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
