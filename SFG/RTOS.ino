#include <FreeRTOS_SAMD51.h>

void rtos_us_delay(int us){vTaskDelay(us/portTICK_PERIOD_US);}
void rtos_ms_delay(int ms){vTaskDelay((ms*1000)/portTICK_PERIOD_US);}
