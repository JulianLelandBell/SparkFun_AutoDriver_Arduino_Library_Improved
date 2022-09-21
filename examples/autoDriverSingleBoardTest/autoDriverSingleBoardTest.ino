#include <SparkFunAutoDriver.h>
#include <SPI.h>

/* autoDriverUnitTest
 *  Julian Bell, UPS Advanced Technology Group
 *  2022-08-12
 *  
 *  Simple script to perform unit tests with a single stepper motor and the Sparkfun AutoDriver stepper driver board.
 */

AutoDriver board(0, 10, 7);
unsigned long temp;
// Define system operational parameters - supply voltage, motor inductance, motor resistance, etc.
float V_cc = 36; // Supply voltage to motors
float R_motor = 0.75; // Motor winding resistance, ohms/winding
float L_motor = 0.0024; // Motor winding inductance, henrys/winding
float Ke_motor = 0.08568; // Motor Ke parameter - defined and measured per STM datasheet
float I_motor = 2.8; // Motor target current per winding, amps/winding
int KVAL_motor = round(((R_motor * I_motor)/V_cc) * 256);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  // Start by setting up the pins and the SPI peripheral.
  //  The library doesn't do this for you! 
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
  board.SPIPortConnect(&SPI);

  Serial.println("Checking board status...");

  // first check  board config register, should be 0x2E88 on bootup
  temp = board.getParam(CONFIG);
  Serial.print("Config reg value: ");
  Serial.println(temp, HEX);
  
  // Now check the status of the board. Should be 0x7c03
  temp = board.getStatus();
  Serial.print("Status reg value: ");
  Serial.println(temp, HEX);

  Serial.println("Motor Parameters (PLEASE CHECK FOR ACCURACY):");
  Serial.print("V_cc = ");
  Serial.print(V_cc, 3);
  Serial.print(" | ");
  Serial.print("I_motor = ");
  Serial.print(I_motor, 3);
  Serial.print(" | ");
  Serial.print("R_motor = ");
  Serial.print(R_motor, 3);
  Serial.print(" | ");
  Serial.print("L_motor = ");
  Serial.print(L_motor, 3);
  Serial.print(" | ");
  Serial.print("Ke_motor = ");
  Serial.print(Ke_motor, 3);
  Serial.print(" | ");
  Serial.print("KVAL_motor = ");
  Serial.println(KVAL_motor);
  Serial.println("Send any character over serial to continue with these parameters:");
  while (!Serial.available() > 0); {}

  // Set operational parameters for board
  board.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  board.configStepMode(STEP_FS_64);   // 0 microsteps per step
  board.setMaxSpeed(750);        // 10000 steps/s max
  board.setFullSpeed(500);       // microstep below 10000 steps/s
  board.setAcc(5000);             // accelerate at 10000 steps/s/s
  board.setDec(5000);
  board.setSlewRate(SR_530V_us);   // Upping the edge speed increases torque.
  board.setOCThreshold(OC_3750mA);  // OC threshold 750mA
  board.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
  board.setOCShutdown(OC_SD_ENABLE);
  // board.setOCShutdown(OC_SD_DISABLE); // don't shutdown on OC. Commenting out because we DEFINITELY want to shut down on OC
  board.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V
  board.setSwitchMode(SW_USER);    // Switch is not hard stop
  board.setOscMode(INT_16MHZ); // internal 16MHz oscillator
  board.setAccKVAL(KVAL_motor);           // We'll tinker with these later, if needed.
  board.setDecKVAL(KVAL_motor);
  board.setRunKVAL(KVAL_motor);
  board.setHoldKVAL(KVAL_motor);           // This controls the holding current; keep it low.
  delay(10);

  // Run motor once
  Serial.println("Running motor forwards...");
  board.run(FWD,500);
  delay(2000);
  board.softHiZ();
  while(board.busyCheck()){
    // Do nothing while we wait for the board to stop working
  }
  temp = board.getStatus();
  Serial.print("Status reg value: ");
  Serial.println(temp, HEX);
  Serial.println("Running motor reverse...");
  board.run(REV,500);
  delay(4000);
  board.softHiZ();
  while(board.busyCheck()){
    // Do nothing while we wait for the board to stop working
  }
  temp = board.getStatus();
  Serial.print("Status reg value: ");
  Serial.println(temp, HEX);
  Serial.println("Running motor reverse...");
  board.run(FWD,500);
  delay(2000);
  board.softHiZ();
  temp = board.getStatus();
  Serial.print("Status reg value: ");
  Serial.println(temp, HEX);
  Serial.println("Test complete!");
}

void loop() {
  // put your main code here, to run repeatedly:

}
