#ifndef DHT11_SENSOR_H
#define DHT11_SENSOR_H

//#define DHTPIN D7
#define DHTPIN D2
#define DHTTYPE DHT11

struct DHTdata{
  float humidity;
  float temperature; 
};
struct DHTdata getDHT();
void dht_initialize();
#endif
