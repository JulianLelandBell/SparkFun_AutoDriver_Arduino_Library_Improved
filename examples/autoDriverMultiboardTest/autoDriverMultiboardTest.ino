/* autoDriverMultiboardTest
 *  Julian Bell, UPS Advanced Technology Group
 *  2022-08-31
 *  
 *  Script that implements multiple Sparkfun AutoDriver stepper boards, l
 */

// Includes
#include <SparkFunAutoDriver.h>
#include <SPI.h>

// Variables & objects
// Define AutoDriver boards
AutoDriver boardA(0, 10, 7);
AutoDriver boardB(1, 10, 7);
AutoDriver boardC(2, 10, 7);

// Define system operational parameters - supply voltage, motor inductance, motor resistance, etc.
float V_cc = 36; // Supply voltage to motors
float R_motor = 0.75; // Motor winding resistance, ohms/winding
float L_motor = 0.0024; // Motor winding inductance, henrys/winding
float Ke_motor = 0.08568; // Motor Ke parameter - defined and measured per STM datasheet
float I_motor = 2.8; // Motor target current per winding, amps/winding
int KVAL_motor = round(((R_motor * I_motor)/V_cc) * 256);

unsigned long stat;
unsigned long conf;

void setup() {
  // Configure serial & SPI
  Serial.begin(9600); 
  pinMode(7, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(7, HIGH);
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);

  // Tell the Autodriver object which SPI port you want to use. Some
  //  devices may have more than one.
  // TODO: Turn this into a function that can be passed a list of AutoDriver objects (possible?)
  boardA.SPIPortConnect(&SPI);
  boardB.SPIPortConnect(&SPI);
  boardC.SPIPortConnect(&SPI);

  // Check board status
  Serial.println("Checking board status...");
  conf = boardA.getParam(CONFIG);
  stat = boardA.getStatus();
  Serial.print("Board A: Status == ");
  Serial.print(stat, HEX);
  Serial.print(", Configuration == ");
  Serial.println(conf, HEX);
  conf = boardB.getParam(CONFIG);
  stat = boardB.getStatus();
  Serial.print("Board B: Status == ");
  Serial.print(stat, HEX);
  Serial.print(", Configuration == ");
  Serial.println(conf, HEX);
  conf = boardC.getParam(CONFIG);
  stat = boardC.getStatus();
  Serial.print("Board C: Status == ");
  Serial.print(stat, HEX);
  Serial.print(", Configuration == ");
  Serial.println(conf, HEX);
  
  // Set operational parameters for Board A
  Serial.print("Configuring Board A.");
  boardA.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  boardA.configStepMode(STEP_FS_64);   // 0 microsteps per step
  boardA.setMaxSpeed(750);        // 10000 steps/s max
  boardA.setFullSpeed(500);       // microstep below 10000 steps/s
  boardA.setAcc(5000);             // accelerate at 10000 steps/s/s
  boardA.setDec(5000);
  Serial.print(".");
  boardA.setSlewRate(SR_530V_us);   // Upping the edge speed increases torque.
  boardA.setOCThreshold(OC_3750mA);  // OC threshold 3750mA
  boardA.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
  boardA.setOCShutdown(OC_SD_ENABLE);
  // board.setOCShutdown(OC_SD_DISABLE); // don't shutdown on OC. Commenting out because we DEFINITELY want to shut down on OC
  boardA.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V
  Serial.print(".");
  boardA.setSwitchMode(SW_USER);    // Switch is not hard stop
  boardA.setOscMode(EXT_16MHZ_OSCOUT_INVERT); // use OSCOUT line
  boardA.setAccKVAL(KVAL_motor);           // We'll tinker with these later, if needed.
  boardA.setDecKVAL(KVAL_motor);
  boardA.setRunKVAL(KVAL_motor);
  boardA.setHoldKVAL(KVAL_motor);           // This controls the holding current; keep it low.
  Serial.println(".done!");

  // Set operational parameters for Board B
  Serial.print("Configuring Board B.");
  boardB.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  boardB.configStepMode(STEP_FS_64);   // 0 microsteps per step
  boardB.setMaxSpeed(750);        // 10000 steps/s max
  boardB.setFullSpeed(500);       // microstep below 10000 steps/s
  boardB.setAcc(5000);             // accelerate at 10000 steps/s/s
  boardB.setDec(5000);
  Serial.print(".");
  boardB.setSlewRate(SR_530V_us);   // Upping the edge speed increases torque.
  boardB.setOCThreshold(OC_3750mA);  // OC threshold 3750mA
  boardB.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
  boardB.setOCShutdown(OC_SD_ENABLE);
  // board.setOCShutdown(OC_SD_DISABLE); // don't shutdown on OC. Commenting out because we DEFINITELY want to shut down on OC
  boardB.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V
  Serial.print(".");
  boardB.setSwitchMode(SW_USER);    // Switch is not hard stop
  boardB.setOscMode(INT_16MHZ_OSCOUT_16MHZ); // internal 16MHz oscillator, with external clock (needed for multiboard systems)
  boardB.setAccKVAL(KVAL_motor);           // We'll tinker with these later, if needed.
  boardB.setDecKVAL(KVAL_motor);
  boardB.setRunKVAL(KVAL_motor);
  boardB.setHoldKVAL(KVAL_motor);           // This controls the holding current; keep it low.
  Serial.println(".done!");

  // Set operational parameters for Board C
  Serial.print("Configuring Board C.");
  boardC.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  boardC.configStepMode(STEP_FS_64);   // 0 microsteps per step
  boardC.setMaxSpeed(750);        // 10000 steps/s max
  boardC.setFullSpeed(500);       // microstep below 10000 steps/s
  boardC.setAcc(5000);             // accelerate at 10000 steps/s/s
  boardC.setDec(5000);
  Serial.print(".");
  boardC.setSlewRate(SR_530V_us);   // Upping the edge speed increases torque.
  boardC.setOCThreshold(OC_3750mA);  // OC threshold 3750mA
  boardC.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
  boardC.setOCShutdown(OC_SD_ENABLE);
  // board.setOCShutdown(OC_SD_DISABLE); // don't shutdown on OC. Commenting out because we DEFINITELY want to shut down on OC
  boardC.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V
  Serial.print(".");
  boardC.setSwitchMode(SW_USER);    // Switch is not hard stop
  boardC.setOscMode(INT_16MHZ_OSCOUT_16MHZ); // internal 16MHz oscillator, with external clock (needed for multiboard systems)
  boardC.setAccKVAL(KVAL_motor);           // We'll tinker with these later, if needed.
  boardC.setDecKVAL(KVAL_motor);
  boardC.setRunKVAL(KVAL_motor);
  boardC.setHoldKVAL(KVAL_motor);           // This controls the holding current; keep it low.
  Serial.println(".done!");

  // Check board status
  Serial.println("Checking board status...");
  conf = boardA.getParam(CONFIG);
  stat = boardA.getStatus();
  Serial.print("Board A: Status == ");
  Serial.print(stat, HEX);
  Serial.print(", Configuration == ");
  Serial.println(conf, HEX);
  conf = boardB.getParam(CONFIG);
  stat = boardB.getStatus();
  Serial.print("Board B: Status == ");
  Serial.print(stat, HEX);
  Serial.print(", Configuration == ");
  Serial.println(conf, HEX);
  conf = boardC.getParam(CONFIG);
  stat = boardC.getStatus();
  Serial.print("Board C: Status == ");
  Serial.print(stat, HEX);
  Serial.print(", Configuration == ");
  Serial.println(conf, HEX);

  // Test moves
  Serial.println("Beginning moves!");
  boardA.move(FWD, 12800);
  while(boardA.busyCheck()){
    continue;
  }
  delay(2000);
  boardB.move(FWD, 12800);
  while(boardB.busyCheck()){
    continue;
  }
  delay(2000);
  boardC.move(FWD, 12800);
  while(boardC.busyCheck()){
    continue;
  }
  // Check board status
  Serial.println("Checking board status...");
  conf = boardA.getParam(CONFIG);
  stat = boardA.getStatus();
  Serial.print("Board A: Status == ");
  Serial.print(stat, HEX);
  Serial.print(", Configuration == ");
  Serial.println(conf, HEX);
  conf = boardB.getParam(CONFIG);
  stat = boardB.getStatus();
  Serial.print("Board B: Status == ");
  Serial.print(stat, HEX);
  Serial.print(", Configuration == ");
  Serial.println(conf, HEX);
  conf = boardC.getParam(CONFIG);
  stat = boardC.getStatus();
  Serial.print("Board C: Status == ");
  Serial.print(stat, HEX);
  Serial.print(", Configuration == ");
  Serial.println(conf, HEX);
}

void loop() {
  
}
