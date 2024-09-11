
// #include <HX711_ADC.h>
// #include <SoftwareSerial.h>


// #define DID "1165012403110001"
// #define CALIBRATION_VALUE 24.65

// //pins:
// #define HX711_dout 5   //mcu > HX711 dout pin
// #define HX711_sck 4    //mcu > HX711 sck pin
// #define HC12_TX_PIN 7  // Connect HC-12 TX pin to Arduino pin 2
// #define HC12_RX_PIN 6  // Connect HC-12 RX pin to Arduino pin 3
// #define Led 13

// #define HC12_BAUD_RATE 9600

// HX711_ADC LoadCell(HX711_dout, HX711_sck);
// SoftwareSerial hc12(HC12_RX_PIN, HC12_TX_PIN);  // RX, TX


// const int calVal_calVal_eepromAdress = 0;
// unsigned long t = 0;

// void setup() {
//   pinMode(Led, OUTPUT);
//   digitalWrite(Led, LOW);
//   Serial.begin(57600);
//   hc12.begin(HC12_BAUD_RATE);
//   Serial.println("Starting...");

//   LoadCell.begin();
//   unsigned long stabilizingtime = 1000;  // tare preciscion can be improved by adding a few seconds of stabilizing time
//   bool _tare = true;                     //set this to false if you don't want tare to be performed in the next step
//   LoadCell.start(stabilizingtime, _tare);

//   if (LoadCell.getTareTimeoutFlag()) {
//     Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
//   } else {
//     LoadCell.setCalFactor(CALIBRATION_VALUE);  // set calibration factor (float)
//     Serial.println("Startup is complete");
//   }
//   while (!LoadCell.update())
//     ;

//   Serial.print("Calibration value: ");
//   Serial.println(LoadCell.getCalFactor());
//   Serial.print("HX711 measured conversion time ms: ");
//   Serial.println(LoadCell.getConversionTime());
//   Serial.print("HX711 measured sampling rate HZ: ");
//   Serial.println(LoadCell.getSPS());
//   Serial.print("HX711 measured settlingtime ms: ");
//   Serial.println(LoadCell.getSettlingTime());
//   Serial.println("Note that the settling time may increase significantly if you use delay() in your sketch!");

//   if (LoadCell.getSPS() < 7) {
//     Serial.println("!!Sampling rate is lower than specification, check MCU>HX711 wiring and pin designations");
//   } else if (LoadCell.getSPS() > 100) {
//     Serial.println("!!Sampling rate is higher than specification, check MCU>HX711 wiring and pin designations");
//   }





//   Serial.println("########################################  Check your Weight");
// }

// int w_counter = 0;
// int w = 0;
// bool check_weight_stable = true;
// bool take_weight = false;
// float total_weight = 0.0;
// int twc = 0;
// bool calculate_weight = false;
// bool process_running = false;
// bool take_new_weight = false;

// #define MAX_WEIGHT_COUNT 20

// void loop() {
//   static boolean newDataReady = 0;
//   const int serialPrintInterval = 100;  //increase value to slow down serial print activity

//   // check for new data/start next conversion:
//   if (LoadCell.update()) newDataReady = true;

//   // get smoothed value from the dataset:
//   if (newDataReady) {
//     if (millis() > t + serialPrintInterval) {
//       float i = LoadCell.getData();
//       float x = i / 1000;
//       // Serial.print("Raw Value: ");
//       // Serial.println(i);
//       // Serial.print("Raw Weight: ");
//       // Serial.println(x);

//       if (x > 5.00) {
//         if (!process_running) {
//           check_weight_stable = false;
//           take_new_weight = false;
//         }
//       } else if (process_running && take_new_weight && (x < 5.00)) {
//         process_running = false;
//         Serial.println("########################################  Check your Weight");
//       }


//       // weight stability check
//       if (!check_weight_stable) {
//         process_running = true;
//         int temp = x;
//         if (temp == w) {
//           w_counter++;
//           if (w_counter == MAX_WEIGHT_COUNT) {
//             Serial.println("*********** weight stablizeing check done ***********");
//             check_weight_stable = true;  // don't need to check weight any more.
//             take_weight = true;          // now calculate the weight.
//             w_counter = 0;
//           }
//         } else {
//           w_counter = 0;
//         }
//         w = x;
//         // Serial.print("W: ");
//         // Serial.println(w);
//       }


//       // if weight is stable then read weight
//       if (take_weight) {
//         total_weight += x;
//         twc++;
//         if (twc == MAX_WEIGHT_COUNT) {
//           take_weight = false;
//           calculate_weight = true;
//           twc = 0;
//         }
//       }

//       // after reading weight send data
//       if (calculate_weight) {

//         float actual_weight = total_weight / MAX_WEIGHT_COUNT;
//         total_weight = 0.0;
//         Serial.print(">>>>>>>>>>>>>>>>>> actual_weight: ");
//         Serial.println(actual_weight);
//         calculate_weight = false;
//         take_new_weight = true;

//         digitalWrite(Led, HIGH);
//         delay(200);
//         char buffer[20];           // Allocate buffer for the string
//         dtostrf(x, 6, 2, buffer);  // Convert float to string with 8 characters and 2 decimal places
//         char data[100];
//         sprintf(data, "%s,%s", DID, buffer);
//         Serial.println(buffer);
//         Serial.println(data);
//         hc12.print(data);

//         //send data done;
//       }





//       newDataReady = 0;
//       t = millis();
//     }
//     digitalWrite(Led, LOW);
//   }

//   // receive command from serial terminal, send 't' to initiate tare operation:
//   if (Serial.available() > 0) {
//     char inByte = Serial.read();
//     if (inByte == 't') LoadCell.tareNoDelay();
//   }

//   // check if last tare operation is complete:
//   if (LoadCell.getTareStatus() == true) {
//     Serial.println("Tare complete");
//   }
// }



// // void loop() {
// //   static boolean newDataReady = 0;
// //   const int serialPrintInterval = 3000;  //increase value to slow down serial print activity

// //   // check for new data/start next conversion:
// //   if (LoadCell.update()) newDataReady = true;

// //   // get smoothed value from the dataset:
// //   if (newDataReady) {

// //     if (millis() > t + serialPrintInterval) {
// //       float i = LoadCell.getData();
// //       float x = i / 1000;
// //       Serial.print("X: ");
// //       Serial.println(x);

// //       // if (x >= 35) {
// //       //   digitalWrite(Led, HIGH);
// //       //   delay(200);
// //       //   // Convert float to string
// //       //   char buffer[20];           // Allocate buffer for the string
// //       //   dtostrf(x, 6, 2, buffer);  // Convert float to string with 8 characters and 2 decimal places

// //       //   // Serial.print("Load_cell output val: ");
// //       //   // Serial.println(buffer);
// //       //   // Serial.println("Kg");
// //       //   // Send string data via HC-12


// //       //   // String a = "Weight :";
// //       //   // String b = "Kg";
// //       //   // String data = a + buffer + b;
// //       //   char data[100];
// //       //   sprintf(data, "%s,%s", DID, buffer);
// //       //   Serial.println(buffer);
// //       //   Serial.println(data);
// //       //   hc12.print(data);
// //       // }
// //       t = millis();
// //       newDataReady = false;
// //     }
// //     digitalWrite(Led, LOW);
// //   }

// //   // receive command from serial terminal, send 't' to initiate tare operation:
// //   if (Serial.available() > 0) {
// //     char inByte = Serial.read();
// //     if (inByte == 't') LoadCell.tareNoDelay();
// //   }

// //   // check if last tare operation is complete:
// //   if (LoadCell.getTareStatus() == true) {
// //     Serial.println("Tare complete");
// //   }
// // }
