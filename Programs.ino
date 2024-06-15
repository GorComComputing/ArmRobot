// Automatic Program 1 
void program1(){
  TornStepper(30*5);

  run4(70, 5);
  run3(120, 3);
  run2(120, 3);
  run1(100, 1);////////////////100
  run4(5, 5);

  Serial.println("TAKE OK");

  run1(80, 1);
  run2(80, 3);
  run3(80, 3);

  Serial.println("UP OK");
  delay(1000);

  TornStepper(-30*10);

  run3(120, 3);
  run2(120, 3);
  run1(100, 1);//////////////////////100
  run4(70, 5);

  toZero();

  TornStepper(30*5);
}

// Automatic Program 2 
void program2(){
  run4(70, 5);
  run3(120, 3);
  run2(90, 3);
  run1(130, 1);////////////////100
  run4(15, 5);

  Serial.println("TAKE OK");

  run1(80, 1);
  run2(80, 3);
  run3(80, 3);

  Serial.println("UP OK");
  delay(1000);

  TornStepper(30*8);

  run3(120, 3);
  run2(90, 3);
  run1(130, 1);//////////////////////100
  run4(70, 5);

  Serial.println("DROP 1 OK");

  run1(80, 1);
  run2(80, 3);
  run3(80, 3);

  Serial.println("UP OK");
  delay(1000);

  TornStepper(-30*6);

  run4(70, 5);
  run3(125, 3);
  run2(95, 3);
  run1(125, 1);////////////////100
  run4(15, 5);

  Serial.println("TAKE OK");

  run1(80, 1);
  run2(80, 3);
  run3(80, 3);

  Serial.println("UP OK");
  delay(1000);

  TornStepper(30*6);

  run3(120, 3);
  run2(90, 3);
  run1(125, 1);//////////////////////100
  run4(70, 5); 

  toZero();

  TornStepper(-30*8);
}


// Automatic Program 3 
void program3(){
  TornStepper(-30*10);

  run4(85, 5);
  run3(140, 3);
  run2(110, 3);
  run1(110, 1);////////////////100
  run4(40, 5);

  Serial.println("TAKE OK");

  run2(55, 3);
  run3(45, 3);

  run1(100, 1);///----------

  Serial.println("UP OK");
  delay(1000);

  TornStepper(30*13);

  run1(135, 1);///----------
  run4(70, 5);

  Serial.println("DROP OK");
  delay(1000);

  toZero();

  TornStepper(-30*3);
}
