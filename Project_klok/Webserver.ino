int currentColor = 0;
void WebServerRoutes(){
  ESPEssentials::WebServer.on("/", HTTP_GET, [&]() {
    ESPEssentials::WebServer.send(200, "text/html", generateHTML());
  });

  ESPEssentials::WebServer.on("/ToggleState", HTTP_GET, [&]() {
    if(ServoState == "RunClock"){ServoState ="Initialize";} else{ServoState ="RunClock";};
    ESPEssentials::WebServer.send(200, "text/html", generateHTML());
  });
  ESPEssentials::WebServer.on("/reset_wifi", HTTP_GET, [&]() {
    ESPEssentials::WebServer.send(200, "text/plain", "Wifi settings reset.");
    ESPEssentials::Wifi.resetSettings();
  });
  ESPEssentials::WebServer.on("/ToggleLed", HTTP_GET, [&]() {
    ESPEssentials::WebServer.send(200, "text/html", generateHTML());
    Serial.println(currentColor);
    toggleColor();
  });
}

char* generateHTML() {
const char* htmlCode = "<!DOCTYPE html>\n"
                       "<html lang=\"en\">\n"
                       "<head>\n"
                       "    <title>Klok Portal</title>\n"
                       "    <script>\n"
                       "        function confirmReset() {\n"
                       "            return confirm(\"Weet u zeker dat u het wifi wilt resetten?\");\n"
                       "        }\n"
                       "    </script>\n"
                       "</head>\n"
                       "<body>\n"
                       "    <h1>Current Time: <span id=\"time\">%s</span></h1>\n"
                       "    <p>Servo State: <span id=\"servoState\">%s</span></p>\n"
                       "    <form action=\"/\" method=\"get\"> <button type=\"submit\">Refresh Time</button></form>\n"
                       "    <form action=\"/ToggleState\" method=\"get\"> <button type=\"submit\">Toggle State</button></form>\n"
                       "    <form action=\"/ToggleLed\" method=\"get\"> <button type=\"submit\">Toggle Light</button></form>\n"
                       "    <form action=\"/reset_wifi\" method=\"get\" onsubmit=\"return confirmReset()\"> <button type=\"submit\">reset wifi</button></form>\n"
                       "</body>\n"
                       "</html>";

    // Get time as String
    String timeString = rtc.getTime("%H:%M:%S");
    // Convert timeString to const char*
    const char* timeChar = timeString.c_str();
    // Convert ServoState to const char*
    const char* servoStateChar = ServoState.c_str();
    // Allocate memory for the result
    char* result = (char*)malloc(strlen(htmlCode) + strlen(timeChar) + strlen(servoStateChar) + 1);
    // Fill in the result with sprintf
    sprintf(result, htmlCode, timeChar, servoStateChar);

    return result;
}

void toggleColor() {
    currentColor = (currentColor + 1) % 3; // switches between 0, 1 en 2 (red, green, blue)
    switch(currentColor) {
        case 0:
            neopixelWrite(LED_BUILTIN, 1, 0, 0); // Rood
            break;
        case 1:
            neopixelWrite(LED_BUILTIN, 0, 1, 0); // Groen
            break;
        case 2:
            neopixelWrite(LED_BUILTIN, 0, 0, 1); // Blauw
            break;
    }
}