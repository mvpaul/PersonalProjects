#define SENSOR_PIN A0
#define GREEN_LED 9
#define RED_LED 10

#define THRESHOLD 600       // Adjust based on your laser + photodiode
#define SAMPLES 5           // Number of pulses expected
#define INTERVAL 1000        // Delay between samples in ms

int receivedPattern[SAMPLES];
int key[SAMPLES] = {1, 0, 0, 1, 0}; // your “secret” pattern

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Waiting for key...");

  // Sample laser pulses
  for (int i = 0; i < SAMPLES; i++) {
    int signal = analogRead(SENSOR_PIN);
    receivedPattern[i] = (signal > THRESHOLD) ? 1 : 0;

    Serial.print("Sample ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(receivedPattern[i]);

    delay(INTERVAL);
  }

  // Compare received pattern to the key
  if (patternMatches()) {
    grantAccess();
  } else {
    denyAccess();
  }

  delay(1000); // Delay before next attempt
}

bool patternMatches() {
  for (int i = 0; i < SAMPLES; i++) {
    if (receivedPattern[i] != key[i]) {
      return false;
    }
  }
  return true;
}

void grantAccess() {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  Serial.println("ACCESS GRANTED");
}

void denyAccess() {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  Serial.println("ACCESS DENIED");
}
