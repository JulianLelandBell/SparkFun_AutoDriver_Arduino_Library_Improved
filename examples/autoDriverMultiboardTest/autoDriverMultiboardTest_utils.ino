void setBoardParams(AutoDriver &curBoard) {
    Serial.print("Configuring board.");
    curBoard.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
    //  second paramter ignored.
    curBoard.configStepMode(STEP_FS_64);   // 0 microsteps per step
    curBoard.setMaxSpeed(750);        // 10000 steps/s max
    curBoard.setFullSpeed(500);       // microstep below 10000 steps/s
    curBoard.setAcc(5000);             // accelerate at 10000 steps/s/s
    curBoard.setDec(5000);
    Serial.print(".");
    curBoard.setSlewRate(SR_530V_us);   // Upping the edge speed increases torque.
    curBoard.setOCThreshold(OC_3750mA);  // OC threshold 3750mA
    curBoard.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
    curBoard.setOCShutdown(OC_SD_ENABLE);
    // board.setOCShutdown(OC_SD_DISABLE); // don't shutdown on OC. Commenting out because we DEFINITELY want to shut down on OC
    curBoard.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V
    Serial.print(".");
    curBoard.setSwitchMode(SW_USER);    // Switch is not hard stop
    curBoard.setOscMode(EXT_16MHZ_OSCOUT_INVERT); // use OSCOUT line
    curBoard.setAccKVAL(KVAL_motor);           // We'll tinker with these later, if needed.
    curBoard.setDecKVAL(KVAL_motor);
    curBoard.setRunKVAL(KVAL_motor);
    curBoard.setHoldKVAL(KVAL_motor);           // This controls the holding current; keep it low.
    Serial.println(".done!");
}