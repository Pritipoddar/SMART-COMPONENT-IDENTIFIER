/* * Project: Priti's Smart Component Identifier
 * Components: Resistor, LDR, Capacitor
 * Display: Common Anode 7-Segment
 */

const int analogPin = A0;
const int chargePin = 11;    
const int buttonPin = 2;     

const int segA = 4; const int segB = 5; const int segC = 6;
const int segD = 7; const int segE = 8; const int segF = 9; const int segG = 10;

const float resistorValue = 10000.0; // 10k reference resistor

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, LOW);
  
  for(int i = 4; i <= 10; i++) pinMode(i, OUTPUT);
  clearDisplay();
  
  Serial.println("===============================================");
  Serial.println("  PRITI'S SMART COMPONENT IDENTIFIER READY    ");
  Serial.println("===============================================");
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    delay(250); 
    Serial.println("\n[SCANNING] Analyzing Component...");
    
    // 1. Capacitor Test
    float capacitance = checkCapacitor();
    if (capacitance > 0.01) { 
      Serial.println("SUCCESS: [ CAPACITOR ]");
      Serial.print("Value: "); Serial.print(capacitance); Serial.println(" uF");
      displayCharacter('C');
    } 
    // 2. Resistor / LDR Test
    else {
      checkResistorOrLDR();
    }
    while(digitalRead(buttonPin) == LOW); 
    delay(400);
  }
}

float checkCapacitor() {
  pinMode(analogPin, INPUT);
  digitalWrite(chargePin, HIGH); 
  unsigned long startTime = micros();
  
  // 15 seconds timeout for larger capacitors
  while(analogRead(analogPin) < 648) {
    if ((micros() - startTime) > 15000000) { 
      digitalWrite(chargePin, LOW);
      return 0.0; 
    }
  }
  
  unsigned long elapsedTime = micros() - startTime;
  digitalWrite(chargePin, LOW); 
  float microFarads = ((float)elapsedTime / resistorValue);
  
  pinMode(analogPin, OUTPUT);
  digitalWrite(analogPin, LOW);
  delay(2000); 
  return microFarads;
}

void checkResistorOrLDR() {
  pinMode(analogPin, OUTPUT);
  digitalWrite(analogPin, LOW);
  delay(100); 
  
  pinMode(analogPin, INPUT);
  pinMode(chargePin, INPUT); 
  delay(50); 
  
  int raw1 = analogRead(analogPin);
  delay(150);
  int raw2 = analogRead(analogPin);
  
  // LDR Check: check for dynamic light variance
  if (abs(raw1 - raw2) > 20) {
    Serial.println("SUCCESS: [ LDR ]");
    displayCharacter('L');
    return;
  }
  
  int raw = analogRead(analogPin);
  if (raw >= 1000 || raw <= 10) {
    Serial.println("RESULT: No Component or Short Circuit!");
    displayCharacter('E');
    return;
  }
  
  // Resistance Calculation
  float resistance = resistorValue * ((raw * 5.0 / 1024.0) / (5.0 - (raw * 5.0 / 1024.0)));
  Serial.print("SUCCESS: [ RESISTOR ] Value: "); Serial.print(resistance); Serial.println(" Ohms");
  displayCharacter('R');
}

void displayCharacter(char c) {
  clearDisplay();
  if (c == 'C') { digitalWrite(segA, LOW); digitalWrite(segF, LOW); digitalWrite(segE, LOW); digitalWrite(segD, LOW); }
  else if (c == 'R') { digitalWrite(segE, LOW); digitalWrite(segG, LOW); }
  else if (c == 'L') { digitalWrite(segF, LOW); digitalWrite(segE, LOW); digitalWrite(segD, LOW); }
  else if (c == 'E') { digitalWrite(segA, LOW); digitalWrite(segF, LOW); digitalWrite(segG, LOW); digitalWrite(segE, LOW); digitalWrite(segD, LOW); }
}

void clearDisplay() {
  for(int i = 4; i <= 10; i++) digitalWrite(i, HIGH);
}
