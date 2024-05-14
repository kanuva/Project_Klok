void InitializeTime(){
  configTime(0, 0, "nl.pool.ntp.org");
  setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
  struct tm timeinfo;
}