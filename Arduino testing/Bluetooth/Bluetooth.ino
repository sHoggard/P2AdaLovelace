
/*
  Send and receive data via Bluetooth
 By: Björn Berggren
 Ada Lovelace

 */
void setup()
{
  Serial1.println("U,9600,N");  // Change the baudrate to 9600, no parity
  Serial1.begin(9600);  // Start bluetooth serial at 9600
}
 
void loop()
{ 

 delay(50);
 
  if(Serial1.available())  // If the PC sent any characters
  { 
    
  Serial1.print((char)Serial1.read()); // Receives the string from PC and prints it back.
  delay(50);
  }
  
}

