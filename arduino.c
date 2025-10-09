#include <stdio.h>
#include <string.h>
#include "Arduino.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

// Function pointer type definition
typedef char* (*StringFunction)(char*);

// Forward declarations
char* function1(char* input);
char* function2(char* input);
char* function3(char* input);

typedef struct {
    const char* name;
    StringFunction function;
} TimedFunction;

TimedFunction functionList[] = {
    {"function1", function1},
    {"function2", function2},
    {"function3", function3}
};

char* function1(char* input) {
    static char result[100];
    strcpy(result, "Function1: ");
    strcat(result, input);
    return result;
}

char* function2(char* input) {
    static char result[100];
    strcpy(result, "Function2: ");
    strcat(result, input);
    return result;
}

char* function3(char* input) {
    static char result[100];
    strcpy(result, "Function3: ");
    strcat(result, input);
    return result;
}

// Arduino-compatible timing function using micros()
double measureTime(StringFunction func, char* input, char** result) {
    unsigned long start, end;
    
    start = micros();
    *result = func(input);
    end = micros();
    
    return (double)(end - start) / 1000000.0; // Convert microseconds to seconds
}

void display_freeram() {
    Serial.print(F("- SRAM left: "));
    Serial.println(freeRam());
}

int freeRam() {
    extern int __heap_start,*__brkval;
    int v;
    return (int)&v - (__brkval == 0
        ? (int)&__heap_start : (int) __brkval);
}

void setup()
{
  Serial.begin(9600);
  
  char input[] = "Hello";
  int numFunctions = sizeof(functionList) / sizeof(functionList[0]);

  for (int i = 0; i < numFunctions; i++) {
      char* result;
      double time_taken = measureTime(functionList[i].function, input, &result);

      // Correct Serial.println usage - print each part separately
      Serial.print("Function: ");
      Serial.println(functionList[i].name);
      
      Serial.print("Result: ");
      Serial.println(result);
      
      Serial.print("Time: ");
      Serial.print(time_taken, 6); // 6 decimal places
      Serial.println(" seconds");
      
      Serial.print("Time: ");
      Serial.print(time_taken * 1000, 3); // 3 decimal places
      Serial.println(" milliseconds");
      
      Serial.println("---");
  }
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Voltage: ");
  Serial.println("Hello world guys");
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for a second
  delay(1000);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);

   // wait for a second
  delay(1000);
}