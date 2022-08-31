#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "DHT22.h"
#include <unistd.h>
#include <sys/param.h>

#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_spiffs.h>

#define BUFF_SIZE 2048
//static const char *TAG = "VLAKNO";
static const char *TAG1 = "PTHREAD";
static const char *TAG2 = "MAIN";

void DHT_task(void *pvParameter);
void * p_sensor_f(void* param);