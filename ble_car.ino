#define led1 = 13
#define in1 = 12
#define in2 = 11
#define in3 = 10
#define in4 = 9

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char inputvalue = char(Serial.read());
    if (inputvalue == 'F') {
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(9, LOW);
    }
    else if (inputvalue == 'B') {
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(9, HIGH);
    }

    else if (inputvalue == 'R') {
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(9, LOW);
    }

    else if (inputvalue == 'L') {
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(10, LOW);
      digitalWrite(9, LOW);
    }

    else if (inputvalue == 'C') {
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(9, LOW);
    }

    else if (inputvalue == 'A') {
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(10, LOW);
      digitalWrite(9, HIGH);
    }

    else if (inputvalue == 'O') {
      digitalWrite(13, HIGH);
    }

    else if (inputvalue == 's') {
      digitalWrite(13, LOW);
    }

    else if (inputvalue == 'S') {
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      digitalWrite(10, LOW);
      digitalWrite(9, LOW);
    }
  }
}