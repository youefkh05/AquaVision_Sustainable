  #include "AI_blue.h"

  BluetoothSerial Bluetooth_serialESP;

const char* welcomeMessages[MAX_MESSAGES] = {
  "Hello, fish farmer!",
  "Welcome to AquaVision!",
  "Nice to see you!",
  "System ready and watching your tank!",
  "Hey there! AquaVision at your service.",
  "Good day! Monitoring in progress.",
  "Welcome aboard!",
  "Ready to optimize your aquaculture.",
  "Sensors are all set.",
  "Data flows, AquaVision knows!"
};

const char* waterMessages[MAX_MESSAGES] = {
  "Water levels are optimal!",
  "The water is calm and clear.",
  "All systems show good water status.",
  "Tank water is within safe range.",
  "Water conditions are being monitored.",
  "H2O is healthy today!",
  "Water quality checks out.",
  "Looks like the water is doing fine.",
  "No water alerts at the moment.",
  "Fish are swimming happy!"
};

const char* phMessages[MAX_MESSAGES] = {
  "pH is balanced and healthy.",
  "pH levels are looking good!",
  "Current pH: within ideal range.",
  "pH sensors report stable readings.",
  "No pH issues detected.",
  "Aquatic chemistry looks great.",
  "All pH systems are green.",
  "Fish approve of today's pH!",
  "pH is within the safe zone.",
  "Perfect acidity levels right now!"
};

const char* temperatureMessages[MAX_MESSAGES] = {
  "Water temperature is stable and ideal.",
  "Current temperature: Fish-friendly!",
  "No thermal stress in the tank.",
  "Temperature sensors are reporting safe levels.",
  "Cool and steady: perfect tank conditions.",
  "Heat levels are well regulated.",
  "Fish are comfy at this temperature.",
  "Tank environment is thermally balanced.",
  "No overheating detected.",
  "Temperature checks: all clear!"
};


  /* Bluetooth Initialization */
  void BLUE_init(void)
  {
    Bluetooth_serialESP.begin(BLUE_NAME);   
  }

  /* Bluetooth Receive */
  String BLUE_receive(void)
  {
      randomSeed(analogRead(0)); // Seed random generator
      delay(1000);
    String receivedData = "";
    if (Bluetooth_serialESP.available())
    {
      receivedData = Bluetooth_serialESP.readStringUntil('\n');
      receivedData.trim(); // remove extra spaces/newlines
    }
    return receivedData;
  }

  /* Send Random Message */
  void sendRandomMessage(const char* messages[], int size)
  {
    int index = random(0, size);
    Bluetooth_serialESP.println(messages[index]);
  }

  void BLUE_processInput(void)
{
  String userInput = BLUE_receive();

  if (userInput.length() > 0)
  {
    if (userInput.indexOf("water") >= 0)
    {
      sendRandomMessage(waterMessages, MAX_MESSAGES);
    }
    else if (userInput.indexOf("ph") >= 0 || userInput.indexOf("pH") >= 0)
    {
      sendRandomMessage(phMessages, MAX_MESSAGES);
    }
    else if (userInput.indexOf("Temp") >= 0 || userInput.indexOf("temperature") >= 0)
    {
      sendRandomMessage(temperatureMessages, MAX_MESSAGES);
    }
    else if (userInput.indexOf("Hi") >= 0 || userInput.indexOf("Hello") >= 0 || userInput.indexOf("hello") >= 0 || userInput.indexOf("hi") >= 0)
    {
      sendRandomMessage(welcomeMessages, MAX_MESSAGES);
    }
    else
    {
      Bluetooth_serialESP.println("I'm still learning. Try asking about 'water', 'pH', or 'temp'.");
    }
  }
}

void printSensorReading(int value, int type)
{
  switch (type)
  {
    case 1:
      Bluetooth_serialESP.print("Temperature reading is: ");
      break;
    case 2:
      Bluetooth_serialESP.print("Water level 1 reading is: ");
      break;
    case 3:
      Bluetooth_serialESP.print("Water level 2 reading is: ");
      break;
    default:
      Bluetooth_serialESP.print("Unknown sensor type: ");
      break;
  }
  Bluetooth_serialESP.println(value);
}

