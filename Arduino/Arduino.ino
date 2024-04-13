#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

const char* WIFI_SSID = "red";
const char* WIFI_PASSWORD = "clave";

// Credenciales de Firebase
const char* API_KEY = "AIzaSyBwVivZN8J0fPOLyp8pykpCn3mR6EMvT-o";
const char* DATABASE_URL = "https://casadogmatica-default-rtdb.firebaseio.com/";//URL DE LA RTDB
const char* USER_EMAIL = "causa@causa.com";
const char* USER_PASSWORD = "123456";

// Objeto para manejar la comunicación con Firebase
FirebaseData fbdo;

// Objeto para la autenticación en Firebase
FirebaseAuth auth;

// Objeto de configuración de Firebase
FirebaseConfig config;

// Pines de los interruptores
const int SWITCH_PIN_1 = 5;
const int SWITCH_PIN_2 = 18;
const int SWITCH_PIN_3 = 19;
const int SWITCH_PIN_4 = 21;
const int SWITCH_PIN_5 = 22;
const int SWITCH_PIN_6 = 23;

// Nombres de los campos en la base de datos
const char* FIELD_NAME_1 = "Bano";
const char* FIELD_NAME_2 = "Cocina";
const char* FIELD_NAME_3 = "Dormitorio1";
const char* FIELD_NAME_4 = "Dormitorio2";
const char* FIELD_NAME_5 = "Dormitorio3";
const char* FIELD_NAME_6 = "Sala";

void setup() {
    Serial.begin(115200);
    setup_WIFI();
    setupFirebase();
    setupSwitches();
}

void setup_WIFI(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando a Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nConectado a Wi-Fi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase() {
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
  config.signer.tokens.legacy_token = "<database secret>";
  Firebase.reconnectNetwork(true);
  fbdo.setBSSLBufferSize(4096, 1024);
  fbdo.setResponseSize(2048);
  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);
  config.timeout.serverResponse = 10 * 1000;
  Serial.printf("Cliente de Firebase v%s\n\n", FIREBASE_CLIENT_VERSION);
}

void setupSwitches() {
  pinMode(SWITCH_PIN_1, INPUT_PULLUP);
  pinMode(SWITCH_PIN_2, INPUT_PULLUP);
  pinMode(SWITCH_PIN_3, INPUT_PULLUP);
  pinMode(SWITCH_PIN_4, INPUT_PULLUP);
  pinMode(SWITCH_PIN_5, INPUT_PULLUP);
  pinMode(SWITCH_PIN_6, INPUT_PULLUP);
}

void loop() {
  if (Firebase.ready()) {
    updateField(FIELD_NAME_1, digitalRead(SWITCH_PIN_1));
    updateField(FIELD_NAME_2, digitalRead(SWITCH_PIN_2));
    updateField(FIELD_NAME_3, digitalRead(SWITCH_PIN_3));
    updateField(FIELD_NAME_4, digitalRead(SWITCH_PIN_4));
    updateField(FIELD_NAME_5, digitalRead(SWITCH_PIN_5));
    updateField(FIELD_NAME_6, digitalRead(SWITCH_PIN_6));
  }
  delay(1000);
}

void updateField(const char* fieldName, bool state) {
  String path = "/casa/" + String(fieldName) + "/";
  if (Firebase.RTDB.setBool(&fbdo, path.c_str(), state)) {
    Serial.println("Datos enviados exitosamente.");
  } else {
    Serial.print("Error al enviar datos a ");
    Serial.println(fieldName);
    Serial.print("Error: ");
    Serial.println(fbdo.errorReason());
  }
}
