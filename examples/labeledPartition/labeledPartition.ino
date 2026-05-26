/**
   esp32 firmware OTA — labeled partition update with application-level block list

   Demonstrates setSPIFFsPartitionLabel() to target a named data partition and
   setBlockedPartitions() to prevent specific partitions from being overwritten.
*/

#include <esp32fota.h>
#include <WiFi.h>

esp32FOTA fota("esp32-fota-http", 1, false);

const char* manifest_url = "http://server/fota/fota.json";

void setup()
{
  Serial.begin(115200);

  fota.setManifestURL(manifest_url);
  fota.setSPIFFsPartitionLabel("ui");
  fota.setBlockedPartitions({"config"});

  WiFi.begin();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop()
{
  bool updatedNeeded = fota.execHTTPcheck();
  if (updatedNeeded) {
    fota.execOTA();
  }
  delay(60000);
}
