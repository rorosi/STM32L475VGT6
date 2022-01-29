/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/
void vTask1(void *pvParameters);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {


  /* Create the thread(s) */
  xTaskCreate(vTask1,		/* Pointer to the function that implements the task. */
		  	  "Task 1",		/* text name */
			  128,			/* stack depth */
			  NULL,			/* task parameter. */
			  3,			/* task priority */
			  NULL);		/* task handle. */

}

void vTask1( void *pvParameters )
{
	int i = 0;

	/* infinite loop */
	for( ;; )
	{
		if(5 == (i%7))
		{
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		}
		else if(0 == (i%7))
		{
			HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		}
		HAL_Delay(100);
		i++;
	}
}
