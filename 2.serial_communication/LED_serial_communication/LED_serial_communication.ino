
#define LED_pin 2
#define LED_error_pin 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_pin, OUTPUT);
  pinMode(LED_error_pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    String message = Serial.readString();

    if(message == "ON"){
      digitalWrite(LED_pin, HIGH);
    }

    else if(message == "OFF"){
      digitalWrite(LED_pin, LOW);
    }

    else{
      digitalWrite(LED_error_pin, HIGH);
      delay(500);
      digitalWrite(LED_error_pin, LOW);
    }
  }
}
