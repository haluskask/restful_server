#include "DHT_task.h"
#include <errno.h>

void DHT_task(void *pvParameter){
	esp_vfs_spiffs_conf_t conf = {
      .base_path = "/data",
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = true
    };
	esp_err_t ret = esp_vfs_spiffs_register(&conf); //register config
	//*****CHECKING ERROR
	if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG1, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG1, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG1, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG1, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG1, "Partition size: total: %d, used: %d", total, used);
    }
	//*****
	FILE * fp;
	setDHTgpio( 27 ); 
	//while(1) {
		ESP_LOGI(TAG1,"=== Reading DHT ===\n");
		fp = fopen("/data/datas.txt", "a"); //fopen("/data/mem.bin", "w");
		if(fp == NULL){ 
		ESP_LOGI(TAG1,"FILE FAILED TO OPEN\n");
		printf("%s\n",strerror(errno));
		}
		else ESP_LOGI(TAG1,"FILE OPENED\n");
		int ret2 = readDHT();
		errorHandler(ret2);
		fprintf(fp,"[\n%.2f\n%.2f\n]\n",getTemperature(),getHumidity());
		vTaskDelay( 1000 / portTICK_RATE_MS );
		fclose(fp);	
		vTaskDelay( 30000 / portTICK_RATE_MS );
		esp_vfs_spiffs_unregister(conf.partition_label);
	//}
	
}


void * p_sensor_f(void* param){
	TaskHandle_t xHandle;
	xTaskCreate( &DHT_task, "DHT_task", 2048, &param, 5, &xHandle ); //4ty parameter funkcie pre passovanie parametrov z mainu
	pthread_exit((void*) NULL);
}
