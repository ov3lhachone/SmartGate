#include <Keypad.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo


/*What i need i still need to add:
OBRIGATORY:
-motor servo to work when correct PIN is verified
-list to put valid PINs(or maybe just make it to work)
TO DO AFTER:
-way to add valid PINs to the list 
-cancel operation when unused for a certain amount of time 


*/




const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte colPins[COLS] = {10, 11, 12, A0}; //column pins
byte rowPins[ROWS] = {2, 4, 7, 8}; //row pins

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char key;
byte keyAsANumber;
boolean entryComplete;
unsigned long total = 0;  //changed data type to allow for larger numbers
byte digitCount = 0;
boolean getNumber = true; //flags for data entry



void setup()
{
  Serial.begin(9600);
  myservo.attach(9);
  instructions();
}

void loop()
{
  currentTime = millis(); //used for timing blinks
  entryComplete = false;  //will be checked after reading a key
  readKeypad(4); //get a key if available - 4 digits max
  if (entryComplete)  //number entry is complete
  {
    if (getNumber == true)  //first number entry complete
    {
      PIN = total; //copy the number entered to another variable
      //LCD PART(simulated in the serial monitor)
      //-----------------------------------------------------------
      Serial.print("Verifying... ");
      //-----------------------------------------------------------
      verify(PIN);
      getNumber = false;  //flag first number entry is complete
      total = 0;  //reset the total
    }
  }
}



void readKeypad(byte maxDigits) //added a parameter for max digits to accept
{
  key = keypad.getKey();
  if (key == '#') //user signals complete
  {
    entryComplete = true; //flag completion
    digitCount = 0;
    Serial.println();
    
    return; //exit the function
  }
  else if (key == '*' && digitCount > 0)  //user wants to delete a digit
  {
    total = total / 10; //remove the last digit
    digitCount--; //decrement the count of digits entered
    //-----------------------------------------------------------
    Serial.println();
    Serial.print("digit deleted.  The number entered is now : ");
    //-----------------------------------------------------------
    Serial.println(total);
  }
  else if (key == 'C' && digitCount > 0)  //user wants to reset the whole pin
  {
    total = 0; //reset the total
    digitCount = 0; //decrement the count of digits entered
    //-----------------------------------------------------------
    Serial.println();
    Serial.print("PIN reset.");
    //-----------------------------------------------------------
  }
  if (digitCount == maxDigits) //user has already entered maximum digits
  {
    return; //don't accept any more
  }
  if (key >= '0' && key <= '9') //only act on numeric keys
  {
    keyAsANumber = key - 48;
    total = total * 10;
    total = total + keyAsANumber; //add the new number
    Serial.println(total);
    digitCount++;
  }
}
//add motor to this part to unlock when a specific number is set
void verify(unsigned long int PIN) {
  if (PIN == 1234)
    myservo.write(val);                  
    delay(15);  
    return;
  return;
  
}
void instructions()
{
  //-----------------------------------------------------------
  Serial.println("Use the keypad to enter the PIN up to 4 characters MAX:");
  Serial.println("When entry is complete for the PIN click '#' on the keypad\n");
  Serial.println("To delete the last digit entered click '*' on the keypad");
  Serial.println("To reset the whole PIN click 'C' on the keypad");
  //-----------------------------------------------------------
}
