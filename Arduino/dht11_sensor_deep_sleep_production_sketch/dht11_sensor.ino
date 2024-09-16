#include "DHT.h"
#include "./dht11_sensor.h"

DHT dht(DHTPIN, DHTTYPE);

void dht_initialize() {
  dht.begin();
}

struct DHTdata getDHT(){
  struct DHTdata data;
  data.humidity = -99;
  data.temperature = -99;
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  delay(10);
  if(!isnan(h) || !isnan(t)){
    data.humidity = h;
    data.temperature = t;
    return data;
  }
  return data;
}
