#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/queue.h"
#include "driver/mcpwm.h"
#include "driver/gpio.h"
#include "esp_event.h"
#include "nvs_flash.h"

#define SERVO_MIN_PULSEWIDTH_US (1000) // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US (2000) // Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE        (360)   // Maximum angle in degree upto which servo can rotate
#define PIN_ENDSTOP_CLOSE		17
#define PIN_ENDSTOP_OPEN		5
#define PIN_RECEIVER			2
#define READ_ENDSTOP_OPEN	gpio_get_level(PIN_ENDSTOP_OPEN)
#define READ_ENDSTOP_CLOSE	gpio_get_level(PIN_ENDSTOP_CLOSE)
#define READ_RECEIVER 	gpio_get_level(PIN_RECEIVER)

#define SERVO_PULSE_GPIO        (15)   // GPIO connects to the PWM signal line
#define GPIO_INPUT_PIN_SEL  ((1<<PIN_ENDSTOP_CLOSE) | (1<<PIN_ENDSTOP_OPEN) | (1<<PIN_RECEIVER))
static int STOP_COMMAND;
uint8_t FRONTEND_OPEN;
uint8_t FRONTEND_CLOSE;

typedef enum {OTVORENE, OTVORENE_STOP, ZATVORENE, ZATVORENE_STOP} STATE;
typedef struct shared {
	STATE state
} SHARED;
// == function prototypes =======================================

static inline uint32_t 	example_convert_servo_angle_to_duty_us(int angle);
int	 gate_opening();
int 	 gate_closing();
void 	 intialize_servo();
//void * pthread_f(void* pvParameter);

