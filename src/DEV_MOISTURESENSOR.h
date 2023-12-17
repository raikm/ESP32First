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
    hum->setRange(30, 100);                                

    // initialization message
    Serial.print("Configuring Humidity Sensor");           
    Serial.print("\n");

  } // end constructor

  void loop() {

    // the humidity refreshes every 10 seconds by the elapsed time
    if (hum->timeVal() > 10000) {
      // read humidity from sensor dht22
      float humidity = 30;  
      // set the new humidity; this generates an Event Notification and also resets the elapsed time        
      hum->setVal(humidity);                            

      LOG1("Humidity Update: ");
      LOG1(humidity);
      LOG1(" ; ");
    }
  } 
};

