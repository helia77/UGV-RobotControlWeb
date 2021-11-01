#include <ESP8266WiFi.h>

const char* ssid = "Helia";
const char* password = "----";

// SoftwareSerial test(2,4); // Rx | Tx

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  // test.begin(115200);
  delay(10);

 // pinMode(output_pin1, OUTPUT);
 //  pinMode(output_pin2, OUTPUT);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");

  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  
  char* cc;
  if (req.indexOf("/Forward") != -1) {
    cc = "ww";
    }
  else if (req.indexOf("/Backward") != -1) {
    cc = "ss"; 
    }
  else if (req.indexOf("/Left") != -1)  {
    cc = "aa"; 
    }
  else if (req.indexOf("/Right") != -1)  {
    cc = "dd";
    }
  else if (req.indexOf("/Stop") != -1)  {
    cc = "zz";
    }
  else if (req.indexOf("/Wait") != -1)  {
    cc = "ii";
    }

    
  client.flush();
  Serial.println(cc);


  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  s += "<head>";
  s += "<meta charset=\"utf-8\">";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  s += "<script src=\"https://code.jquery.com/jquery-2.1.3.min.js\"></script>";
  s += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">";
  s += "</head>";

  s += "<div class=\"container\">";
  s += "<h1 style=\"margin-top:50px;\"><b>Control Robot</b></h1>";
  s += "<div class=\"row\">";
  s += "<div class=\"col-md-12\"><input class=\"btn btn-block btn-lg btn-success\"style=\"margin-left:400px;color:#fff;font-size:14px;background-color:#000080;border:none;border-radius:100%;cursor: pointer;height:100px;width:100px;\"type=\"button\" value=\"Forward\" onmousedown=\"forward()\" onmouseup=\"wait()\"></div></div>";
  s += "<div class=\"row\" style=\"margin-top:50px;\">";
  s += "<div class=\"col-md-4\"><input class=\"btn btn-block btn-lg btn-success\"style=\"margin-left:200px;color: #fff;font-size:23px;background-color:#000080;border:none;border-radius:100%;cursor: pointer;height:100px;width:100px;\"type=\"button\" value=\"Left\" onmousedown=\"left()\" onmouseup=\"wait()\"></div>";
  s += "<div class=\"col-md-4\"><input class=\"btn btn-block btn-lg btn-success\"style=\"margin-left:10px;color:#fff;font-size:23px;background-color: #e80000; border: none;border-radius:100%;cursor:pointer;height:100px;width:100px;\"type=\"button\" value=\"Stop\" onmousedown=\"stop()\" onmouseup=\"wait()\"></div>";
  s += "<div class=\"col-md-4\"><input class=\"btn btn-block btn-lg btn-success\"style=\"margin-left:-185px;color:#fff;font-size:23px;background-color:#000080;border:none;border-radius:100%;cursor:pointer;height:100px;width:100px;\"type=\"button\" value=\"Right\" onmousedown=\"right()\" onmouseup=\"wait()\"></div>";
  s += "</div>";
  s += "<div class=\"row\" style=\"margin-top:50px;\">";
  s += "<div class=\"col-md-12\"><input class=\"btn btn-block btn-lg btn-success\"style=\"margin-left:400px;color:#fff;font-size:18px;background-color:#000080;border:none;border-radius:100%;cursor:pointer;height:100px;width:100px;\" type=\"button\" value=\"Backward\" onmousedown=\"backward()\" onmouseup=\"wait()\"></div>";
  s += "</div>";

  s += "<script>function forward() {$.get(\"/Forward\");}</script>";
  s += "<script>function backward() {$.get(\"/Backward\");}</script>";
  s += "<script>function left() {$.get(\"/Left\");}</script>";
  s += "<script>function right() {$.get(\"/Right\");}</script>";
  s += "<script>function stop() {$.get(\"/Stop\");}</script>";
  s += "<script>function wait() {$.get(\"/Wait\");}</script>";

  client.print(s);
  delay(1);
  //Serial.println("Client disconnected");
}
