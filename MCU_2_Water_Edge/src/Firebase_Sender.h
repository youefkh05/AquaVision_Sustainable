/*
        Code by: Amir Sameh
        date: 7.3.2025

        this file uploads ESP32 sensor data to Firebase realtime database
*/ 


#include <WiFi.h>
#include <FirebaseESP32.h>

const char* ssid = "Tp-LINK_B238";    //AndroidAPCCB0 -- Communication(8310) -- Linksys00431_5GHz -- Tp-LINK_B238
const char* password = "90701702";    //A123456a      -- open                -- open              -- 90701702

// Firebase credentials
#define API_KEY "AIzaSyC-D17GV3prkmQDssF9ZbXiKGQq2-XLsiE"
#define DATABASE_URL "https://project-0-51c9c-default-rtdb.firebaseio.com"
#define USER_EMAIL "amirsameh770@gmail.com"
#define USER_PASSWORD "123456789"


/*
apiKey: "AIzaSyC-D17GV3prkmQDssF9ZbXiKGQq2-XLsiE",

authDomain: "project-0-51c9c.firebaseapp.com",

databaseURL: "https://project-0-51c9c-default-rtdb.firebaseio.com",

projectId: "project-0-51c9c",

storageBucket: "project-0-51c9c.firebasestorage.app",

messagingSenderId: "486817466192",

appId: "1:486817466192:web:6203cdb94a9d9d62604e55"
*/



// NTP Server
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 2 * 3600;  // Change according to your timezone (e.g., GMT+2 = 2*3600)
const int   daylightOffset_sec = 0;    // Adjust for daylight savings time if needed

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void connect_WiFi(){

   // Connect to Wi-Fi
   WiFi.mode(WIFI_STA);            // essential to share the same WiFi channel with ESP-NOW
   WiFi.setSleep(false);
   if(password=="open"){
     WiFi.begin(ssid);             // for open networks
   }
   else {
     WiFi.begin(ssid, password);  // for secured networks
   }
 
 
   while (WiFi.status() != WL_CONNECTED) {
     delay(1000);
     Serial.println("Connecting to WiFi...");
   }
   Serial.println("__WiFi Connected!__");
 
   configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

}
void  Setup_Firebase() {
  // Serial.begin(9600);
  
  // Initialize Firebase
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

}

// tm GetLocalTime() {
//   struct tm timeinfo;
//   if (!getLocalTime(&timeinfo)) {
//       Serial.println("Failed to obtain time");
//       return;
//   }
//   Serial.print("Current time: ");
//   Serial.println(&timeinfo, "%Y-%m-%d %H:%M:%S");  // Print formatted time
// }

void Send_Firebase_Data() {
  FirebaseJson json;
  // tm time = GetLocalTime();

  json.set("time", "Text");
  json.set("date", "202ameer 13");
  json.set("depth1", "A");
  json.set("temp1", "30");
  json.set("depth2", "56");
  json.set("temp2", "24");

  if (Firebase.pushJSON(fbdo, "/sensors/data", json)) {
    Serial.println("JSON Data Uploaded Successfully!");
  } else {
    Serial.println("Failed to upload JSON: ");
    Serial.println(fbdo.errorReason());
  }
}
