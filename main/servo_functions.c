

#include "servo_functions.h"





static inline uint32_t example_convert_servo_angle_to_duty_us(int angle)
{
    return (angle + SERVO_MAX_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (2 * SERVO_MAX_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
}


int gate_opening(){
	ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, example_convert_servo_angle_to_duty_us(1000)));
	vTaskDelay(500 / portTICK_PERIOD_MS);
		while(READ_ENDSTOP_OPEN && !READ_RECEIVER && !STOP_COMMAND){ 
		}	
		if(!READ_ENDSTOP_OPEN){
		ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, example_convert_servo_angle_to_duty_us(0)));
		return 1;
		}
		else{
			ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, example_convert_servo_angle_to_duty_us(0)));
			STOP_COMMAND = 0;
			return 0;
		}
}
int gate_closing(){
	ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, example_convert_servo_angle_to_duty_us(-1000)));
	vTaskDelay(500 / portTICK_PERIOD_MS);
		while(READ_ENDSTOP_CLOSE && !READ_RECEIVER && !STOP_COMMAND){
		}
		if(!READ_ENDSTOP_CLOSE){
			ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, example_convert_servo_angle_to_duty_us(0)));
			return 1;
		}
		else{
			ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, example_convert_servo_angle_to_duty_us(0)));
			STOP_COMMAND = 0;
			return 0;
		}
}

void intialize_servo(){
	gpio_config_t io_conf;
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, SERVO_PULSE_GPIO); // To drive a RC servo, one MCPWM generator is enough
	STOP_COMMAND = 0;
	
	io_conf.mode = GPIO_MODE_INPUT;
	io_conf.intr_type = GPIO_INTR_ANYEDGE;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
	io_conf.pull_up_en = 1;	
    io_conf.pull_down_en = 0;
    gpio_config(&io_conf);
	
    mcpwm_config_t pwm_config = {
        .frequency = 50, // frequency = 50Hz, i.e. for every servo motor time period should be 20ms
        .cmpr_a = 0,     // duty cycle of PWMxA = 0
        .counter_mode = MCPWM_UP_COUNTER,
        .duty_mode = MCPWM_DUTY_MODE_0,
    };
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
	
}

void * pthread_f(void* pvParameter){
	SHARED* param = (SHARED*) pvParameter;
	int retval;
	while(!READ_RECEIVER && FRONTEND_OPEN){}
		retval = gate_opening();
		if(retval){
			param->state = OTVORENE;
			printf("GATE OPPPENED\n");
		}
		else{
			param->state = OTVORENE_STOP;
		printf("GATE OPPENING > STOP \n");
		}
	while(!READ_RECEIVER && FRONTEND_CLOSE){}
		retval = gate_closing();
		if(retval){
			param->state = ZATVORENE;
			printf("GATE CLOSED\n");
		}
		else{
			param->state = ZATVORENE_STOP;
			printf("GATE CLOSING > STOP \n");
		}
}










