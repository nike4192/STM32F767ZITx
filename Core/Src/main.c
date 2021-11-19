/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */
uint8_t tim6_counter;  // Переменная счетчик для определения последовательности переключения светодиодов
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  // https://istarik.ru/blog/stm32/119.html
  /* HAL (Hardware Abstraction Layer) — это библиотека для создания приложений на stm32,
  разработанная компанией ST в 2014 году. HAL пришёл на смену SPL.

  Итак, HAL позволяет абстрагироваться от работы с регистрами и прочей сложной магии.
  Грубо говоря, HAL это обёртка над низкоуровневыми операциями.
  Конечно же это не отменяет необходимости понимания устройства микроконтроллеров, но значительно снижает уровень вхождения.*/
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();  // инициализация тактирования

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();  // инициализация GPIO
  MX_TIM6_Init();  // инициализация таймера
  /* USER CODE BEGIN 2 */

  /* Перед бесконечным циклом запустим таймер в режиме прерывания */
  HAL_TIM_Base_Start_IT(&htim6);
  tim6_counter = 0;  // Установим нулевое значение переменной, иначе в ней будет мусор
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


		/*led1 - GREn led2 - RED led3 - BLUE*/

	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV16;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  // Читайте больше по ссылке https://istarik.ru/blog/stm32/118.html
  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;  // TIM6 на шине APB1. Максимальная частота шины до 54 МГц. Максимальная частота таймера составляет до 216 МГц
  htim6.Init.Prescaler = 26999;  // Предделитель системной частоты таймера. Таймер будет тикать со скоростью 2кГц (54мГц / 27000 = 2000 тиков в секунду)
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;  // счётчик будет считать «вверх», от нуля до значения переполнения
  htim6.Init.Period = 199;  // Переполнение. Счётчик будет считать до 200. При частоте 2кГц он досчитает до 200 за 100мс. Если хотите чтобы тикал каждую секунду, то измение значение на 2000 - 1. И так далее вплоть до 65 536 - 1
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  // Регистр ARR — Auto-reload register (в нём хранится значение переполнения, в нашем случае это — 27000).
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Green_Pin|Red_Pin|Blue_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Green_Pin Red_Pin Blue_Pin */
  GPIO_InitStruct.Pin = Green_Pin|Red_Pin|Blue_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // Проверяем какой таймер вызывает это событие и переключаем светодиод
  if (htim == &htim6)
  {
    switch(tim6_counter)
    {
      case 0:
        // Здесь везде используется GPIOB поскольку все порты (Green_GPIO_Port, Red_GPIO_Port, Blue_GPIO_Port) ссылаются на него в Core/Inc/main.h
        HAL_GPIO_WritePin(GPIOB, Red_Pin|Green_Pin|Blue_Pin, GPIO_PIN_RESET);  // Сбрасываем значения пинов всех светодиодов
        HAL_GPIO_WritePin(GPIOB, Red_Pin, GPIO_PIN_SET);  // Включаем красный светодиод
        break;
      case 1:
        HAL_GPIO_WritePin(GPIOB, Red_Pin, GPIO_PIN_RESET);  // Выключаем красный светодиод
        HAL_GPIO_WritePin(GPIOB, Green_Pin, GPIO_PIN_SET);  // Включаем зеленый светодиод
        break;
      case 2:
        HAL_GPIO_WritePin(GPIOB, Blue_Pin, GPIO_PIN_RESET);  // Выключаем зеленый светодиод
        HAL_GPIO_WritePin(GPIOB, Blue_Pin, GPIO_PIN_SET);  // Включаем синий светодиод
        break;
    }
    // Проходимся от 0 до 2 (0, 1, 2). Тем самым переключаем светодиоды
    if (tim6_counter < 2) tim6_counter++;
    else tim6_counter = 0;
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
