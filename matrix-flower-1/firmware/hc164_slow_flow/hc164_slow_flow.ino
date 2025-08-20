/*
  HC164 Slow Flow - for Flower 1

  by Mark J Koch ( @maehem at GitHub )

  Slow moving and random segment bits.
  
*/

#define DATA_PIN 2
#define CLK_PIN 3

// Segment layout
// Seg: MSB-LSB: 
//     7: top,
//     6: r-upper
//     5: r-lower
//     4: bot
//     3: l-lower
//     2: l-upper
//     1: mid
//     0: point 
//
// Another way to look at it: Clockwise: top..mid..point
//

uint8_t seg[8] = {
  0b00000001, // 8
  0b00011111, // 7
  0b01000001, // 6
  0b01001001, // 5
  0b10011001, // 4
  0b00001101, // 3
  0b00100101, // 2
  0b10011111  // 1

};

int val;
int val2;

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);

  digitalWrite(DATA_PIN, LOW);
  digitalWrite(CLK_PIN, LOW);

  // for (int i = 0; i < 4; i++) {
  //   for (int j = 0; j < 8; j++) {
  //     digitalWrite(DATA_PIN, (seg[i] >> j) & 0x01);
  //     clkPulse();
  //   }
  // }
}

void loop() {
  int channel = 0x80;

  val = random(256) | random(256);
  val2 = random(2)?random(16):(random(16)<<4);

  for (int i = 0; i < 8; i++) {

    for (int j = 0; j < 8; j++) { // Write the segment data.
      digitalWrite(DATA_PIN, (val >> j) & 0x01);
      clkPulse();
    }
    
    for (int j = 0; j < 8; j++) { // Write which digit to address.
      digitalWrite(DATA_PIN, (val2 >> j) & 0x01);
      clkPulse();
    }

  }
}

void clkPulse() {
  digitalWrite(CLK_PIN, HIGH);
  digitalWrite(CLK_PIN, LOW);
  //delayMicroseconds(10);

  // Slow the clock for cool Matrix effect.
  delay(120);
}
