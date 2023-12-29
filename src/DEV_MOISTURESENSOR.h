/////////////////////////////////
//   DEVICE-SPECIFIC SERVICES //
////////////////////////////////




struct DEV_HumSensor : Service::HumiditySensor {     

  // reference to the Current Humidity Characteristic
  SpanCharacteristic *hum;                                  

  // constructor() method
  DEV_HumSensor() : Service::HumiditySensor() {      
                                   
    // instantiate the Current Temperature Characteristic
    hum = new Characteristic::CurrentRelativeHumidity(50);
    // expand the range to 30%-100% 
    hum->setRange(0, 100);                                

    // initialization message
    Serial.print("Configuring Humidity Sensor");           
    Serial.print("\n");

  } // end constructor

  void loop() {

    const int SensorPin = 34;
    int soilMoistureRawValue = 0;
    int soilMoisture = 0;
    const int dry = 2710;
    const int wet = 1200;
    soilMoistureRawValue = analogRead(SensorPin);
    int percentageValue = map(soilMoistureRawValue, wet, dry, 100, 0);
    // Serial.print(percentageValue);           

    // the humidity refreshes every 10 seconds by the elapsed time
    if (hum->timeVal() > 10000) {
      Serial.print("RAW=");
      Serial.print(soilMoistureRawValue);
      Serial.print("PERCENTAGE=");
      Serial.print(percentageValue);           
      Serial.print("|");
      float humidity = percentageValue;  
      // set the new humidity; this generates an Event Notification and also resets the elapsed time        
      hum->setVal(humidity);                            

      LOG1("Humidity Update: ");
      LOG1(humidity);
      LOG1(" ; ");
    }
  } 
};

