int state = 0; // Initial state
int count = 0; // Total amount
int user_in = 0; // Input: 0 = no input, 1 = 5 cents, 2 = 10 cents

void setup() {
  Serial.begin(9600);
  Serial.println("Vending Machine System");
  Serial.println("-----------------------");
}

void loop() {
  if (Serial.available() > 0) {
    char incoming_byte = Serial.read();
    switch (incoming_byte) {
      case '1': // 5 cents
        user_in = 1;
        break;
      case '2': // 10 cents
        user_in = 2;
        break;
      default: // Invalid input
        user_in = 0;
        break;
    }
  }

  fsm(&state, &count, user_in);
  
  Serial.print("Current total: ");
  Serial.println(count);

  if (count >= 25) {
    Serial.println("25 cents reached! Dispensing item...");
    count %= 25;
    Serial.println("Remaining change of %d will be returned...", &count);
    count = 0;
  }

  delay(500);
}

void fsm(int *state, int *count, int input) {
  switch (*state) {
    case 0: // Idle state
      if (input == 1) { // 5 cents
        *count += 5;
        *state = 0;
      } else if (input == 2) { // 10 cents
        *count += 10;
        *state = 0;
      } // else, do nothing
      break;

    default: // default or wrong input state (ignored)
      *state = 0; 
      break;
  }
}
