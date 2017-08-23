#define SONAR_TRIGGER_PIN     A2
#define SONAR_ECHO_PIN        A1
#define TRIGGER_PIN           A4
#define ECHO_PIN              A3
#define RELAY1_PIN            8
#define RELAY2_PIN            9
unsigned long pulse_length;
unsigned long pulse_length2;
unsigned int measure_distance()
{
   // Trigger the SRF05:
   digitalWrite(SONAR_TRIGGER_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(SONAR_TRIGGER_PIN, LOW);

   // Wait for Echo Pulse
  pulse_length = pulseIn(SONAR_ECHO_PIN, HIGH);

   // Ensure the ultrasonic "beep" has faded away
   delay(50);

   // Convert Pulse to Distance (inches) 
   // pulse_length/58 = cm or pulse_length/148 = inches
   return( (unsigned int) (pulse_length / 58) );
}
unsigned int measure_distance2 ()
{
   // Trigger the SRF05:
   digitalWrite(TRIGGER_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIGGER_PIN, LOW);

   // Wait for Echo Pulse
  pulse_length2 = pulseIn(ECHO_PIN, HIGH);

   // Ensure the ultrasonic "beep" has faded away
   delay(50);

   // Convert Pulse to Distance (inches) 
   // pulse_length2/58 = cm or pulse_length/148 = inches
   return( (unsigned int) (pulse_length2 / 58) );
}

void setup()
{
   pinMode(SONAR_TRIGGER_PIN, OUTPUT);
   pinMode(SONAR_ECHO_PIN, INPUT);
   pinMode(TRIGGER_PIN,OUTPUT);
   pinMode(ECHO_PIN, INPUT);
   pinMode(RELAY1_PIN, OUTPUT);
   pinMode(RELAY2_PIN, OUTPUT);
   Serial.begin(9600);
   digitalWrite (RELAY2_PIN, HIGH);
}

void loop()
{  
   unsigned int current_distance = measure_distance();
   unsigned int current_distance2 = measure_distance2();

   
   
   if(current_distance<20&&current_distance2>20)
   {digitalWrite (RELAY1_PIN, HIGH);
   digitalWrite (RELAY2_PIN, LOW);
   }
   else if (current_distance2<20&&current_distance>20)
   {
   digitalWrite (RELAY1_PIN, LOW);
   digitalWrite (RELAY2_PIN, HIGH);
   }
   Serial.println("current distance");
   Serial.println(current_distance);
   Serial.println("current distance2");
   Serial.println(current_distance2);
 
   delay (10);  
}
