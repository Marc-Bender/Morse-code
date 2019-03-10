uint8_t pulseOutPin=3;
void setup() 
{
    // put your setup code here, to run once:
    pinMode(pulseOutPin,OUTPUT);
    Serial.begin(9600);
    while(!Serial)
    {
    ;//wait
    }
    Serial.println(("I fluently speak Morse code"));
}
#define longPulseTime 200
#define shortPulseTime 100
#define timeDelay 50
String morseCodeAlphabet[]={
                                ".-",
                                "-...",
                                "-.-.",
                                "-..",
                                ".",
                                "..-.",
                                "--.",
                                "....",
                                "..",
                                ".---",
                                "-.-",
                                ".-..",
                                "--",
                                "-.",
                                "---",
                                ".--.",
                                "--.-",
                                ".-.",
                                "...",
                                "-",
                                "..-",
                                "...-",
                                ".--",
                                "-..-",
                                "-.--",
                                "--..",
                                //numbers
                                "-----",//0
                                ".----",
                                "..---",
                                "...--",
                                "....-",
                                ".....",
                                "-....",
                                "--...",
                                "---..",
                                "----.",
                                //punkt
                                ".-.-.-"
                               };
void pulseOut(bool isLongPulse,const uint8_t pin)
{
  digitalWrite(pin,HIGH);
  delay(isLongPulse?longPulseTime:shortPulseTime);
  digitalWrite(pin,LOW);
  delay(timeDelay);
}
void toPulseSequence(String *input,const uint8_t pin)
{
  for(uint8_t i=0;i<(*input).length();i++)
  {
    switch((*input).charAt(i))
    {
      case '.': pulseOut(false,pin);break;
      case '-': pulseOut(true,pin);break;
    }
  }
}
void process(String *input,const uint8_t pin)
{
  (*input).toLowerCase();  
  for(unsigned int i=0;i<(*input).length();i++)
  {
    String output;
    
    if(isAlpha((*input).charAt(i)))
    {
        output=morseCodeAlphabet[((*input).charAt(i))-'a'];
    }
    else if(isDigit((*input).charAt(i)))
    {
      output=morseCodeAlphabet['z'-'a'+((*input).charAt(i))-'0'];
    }
    else if((*input).charAt(i)=='.')
    {
      output=morseCodeAlphabet[36];// lastelement ==36
    }
    Serial.print(output+"  ");
    toPulseSequence(&output,pin);
  }
  Serial.print("\r\n");
}
void loop() {
  if(Serial.available()>0)
  {
    String input=Serial.readString();
    Serial.println(input);
    process(&input,pulseOutPin);   
  }
}
