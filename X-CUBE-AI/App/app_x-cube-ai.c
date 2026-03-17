
/**
  ******************************************************************************
  * @file    app_x-cube-ai.c
  * @author  X-CUBE-AI C code generator
  * @brief   AI program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

 /*
  * Description
  *   v1.0 - Minimum template to show how to use the Embedded Client API
  *          model. Only one input and one output is supported. All
  *          memory resources are allocated statically (AI_NETWORK_XX, defines
  *          are used).
  *          Re-target of the printf function is out-of-scope.
  *   v2.0 - add multiple IO and/or multiple heap support
  *
  *   For more information, see the embeded documentation:
  *
  *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
  *
  *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
  *   typical : C:\Users\[user_name]\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\7.1.0
  */

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#if defined ( __ICCARM__ )
#elif defined ( __CC_ARM ) || ( __GNUC__ )
#endif

/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "app_x-cube-ai.h"
#include "main.h"
#include "ai_datatypes_defines.h"
#include "network.h"
#include "network_data.h"

/* USER CODE BEGIN includes */
#include <stdio.h>
/* USER CODE END includes */

/* IO buffers ----------------------------------------------------------------*/

#if !defined(AI_NETWORK_INPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_in_1[AI_NETWORK_IN_1_SIZE_BYTES];
ai_i8* data_ins[AI_NETWORK_IN_NUM] = {
data_in_1
};
#else
ai_i8* data_ins[AI_NETWORK_IN_NUM] = {
NULL
};
#endif

#if !defined(AI_NETWORK_OUTPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_out_1[AI_NETWORK_OUT_1_SIZE_BYTES];
ai_i8* data_outs[AI_NETWORK_OUT_NUM] = {
data_out_1
};
#else
ai_i8* data_outs[AI_NETWORK_OUT_NUM] = {
NULL
};
#endif

/* Activations buffers -------------------------------------------------------*/

AI_ALIGNED(32)
static uint8_t pool0[AI_NETWORK_DATA_ACTIVATION_1_SIZE];

ai_handle data_activations0[] = {pool0};

/* AI objects ----------------------------------------------------------------*/

static ai_handle network = AI_HANDLE_NULL;

static ai_buffer* ai_input;
static ai_buffer* ai_output;

static void ai_log_err(const ai_error err, const char *fct)
{
  /* USER CODE BEGIN log */
  if (fct)
    printf("TEMPLATE - Error (%s) - type=0x%02x code=0x%02x\r\n", fct,
        err.type, err.code);
  else
    printf("TEMPLATE - Error - type=0x%02x code=0x%02x\r\n", err.type, err.code);

  do {
	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
      HAL_Delay(100);
  } while (1);
  /* USER CODE END log */
}

static int ai_boostrap(ai_handle *act_addr)
{
  ai_error err;

  /* Create and initialize an instance of the model */
  err = ai_network_create_and_init(&network, act_addr, NULL);
  if (err.type != AI_ERROR_NONE) {
    ai_log_err(err, "ai_network_create_and_init");
    return -1;
  }

  ai_input = ai_network_inputs_get(network, NULL);
  ai_output = ai_network_outputs_get(network, NULL);

#if defined(AI_NETWORK_INPUTS_IN_ACTIVATIONS)
  /*  In the case where "--allocate-inputs" option is used, memory buffer can be
   *  used from the activations buffer. This is not mandatory.
   */
  for (int idx=0; idx < AI_NETWORK_IN_NUM; idx++) {
	data_ins[idx] = ai_input[idx].data;
  }
#else
  for (int idx=0; idx < AI_NETWORK_IN_NUM; idx++) {
	  ai_input[idx].data = data_ins[idx];
  }
#endif

#if defined(AI_NETWORK_OUTPUTS_IN_ACTIVATIONS)
  /*  In the case where "--allocate-outputs" option is used, memory buffer can be
   *  used from the activations buffer. This is no mandatory.
   */
  for (int idx=0; idx < AI_NETWORK_OUT_NUM; idx++) {
	data_outs[idx] = ai_output[idx].data;
  }
#else
  for (int idx=0; idx < AI_NETWORK_OUT_NUM; idx++) {
	ai_output[idx].data = data_outs[idx];
  }
#endif

  return 0;
}

static int ai_run(void)
{
  ai_i32 batch;

  batch = ai_network_run(network, ai_input, ai_output);
  if (batch != 1) {
    ai_log_err(ai_network_get_error(network),
        "ai_network_run");
    return -1;
  }

  return 0;
}

/* USER CODE BEGIN 2 */
const float my_test_image[784] = {
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0078f, 0.0078f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0039f, 0.0000f, 0.0000f, 
0.0392f, 0.0471f, 0.0118f, 0.0000f, 0.0000f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.0314f, 0.3255f, 0.4510f, 
0.4000f, 0.4000f, 0.4784f, 0.4706f, 0.1490f, 0.0000f, 0.0078f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.1961f, 0.7765f, 0.6353f, 0.1176f, 
0.0039f, 0.0000f, 0.0627f, 0.4667f, 0.9098f, 0.4353f, 0.0039f, 0.0078f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0039f, 0.1843f, 0.9059f, 0.8431f, 0.0471f, 0.0000f, 
0.0118f, 0.0118f, 0.0000f, 0.0000f, 0.5765f, 1.0000f, 0.4078f, 0.0000f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.6431f, 1.0000f, 0.4706f, 0.0000f, 0.0118f, 
0.0118f, 0.0118f, 0.0078f, 0.0000f, 0.1804f, 0.9333f, 0.8863f, 0.1098f, 0.0000f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.5765f, 0.9098f, 0.2235f, 0.0000f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.0824f, 0.9020f, 1.0000f, 0.2510f, 0.0000f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0392f, 0.1020f, 0.0078f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.1765f, 0.9686f, 0.9725f, 0.1647f, 0.0000f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0039f, 0.0000f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0078f, 0.0000f, 0.5176f, 1.0000f, 0.6078f, 0.0118f, 0.0078f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0039f, 
0.0000f, 0.0000f, 0.0000f, 0.3490f, 0.9490f, 0.6157f, 0.0549f, 0.0039f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0078f, 0.0784f, 
0.1804f, 0.2941f, 0.5647f, 0.5882f, 0.2235f, 0.0000f, 0.0039f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0078f, 0.1373f, 
0.2980f, 0.3333f, 0.4706f, 0.6275f, 0.3922f, 0.0392f, 0.0000f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0000f, 
0.0000f, 0.0000f, 0.0000f, 0.2314f, 0.9333f, 0.7294f, 0.0824f, 0.0039f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.4667f, 1.0000f, 0.6235f, 0.0078f, 0.0078f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0078f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.1961f, 0.9725f, 0.9569f, 0.1451f, 0.0000f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.0157f, 0.0039f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.0980f, 0.9216f, 1.0000f, 0.3255f, 0.0000f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.4706f, 0.7804f, 0.1725f, 0.0039f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.1294f, 0.9412f, 1.0000f, 0.2941f, 0.0000f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.6902f, 1.0000f, 0.4235f, 0.0000f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.2980f, 0.9961f, 0.9137f, 0.0980f, 0.0000f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.2745f, 0.9765f, 0.7686f, 0.0118f, 0.0039f, 
0.0118f, 0.0118f, 0.0078f, 0.0000f, 0.6431f, 1.0000f, 0.5059f, 0.0000f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.3373f, 0.8941f, 0.5255f, 0.0392f, 
0.0000f, 0.0000f, 0.0000f, 0.3725f, 0.9882f, 0.6157f, 0.0353f, 0.0078f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.1137f, 0.4784f, 0.4902f, 
0.2902f, 0.2510f, 0.4314f, 0.6510f, 0.3294f, 0.0118f, 0.0078f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0000f, 0.0000f, 0.0353f, 
0.1059f, 0.1294f, 0.0902f, 0.0000f, 0.0000f, 0.0078f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0078f, 
0.0000f, 0.0000f, 0.0039f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 
0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f, 0.0118f
};

int acquire_and_process_data(ai_i8* data[])
{
  /* fill the inputs of the c-model
  for (int idx=0; idx < AI_NETWORK_IN_NUM; idx++ )
  {
      data[idx] = ....
  }

  */
  return 0;
}

int post_process(ai_i8* data[])
{
  /* process the predictions
  for (int idx=0; idx < AI_NETWORK_OUT_NUM; idx++ )
  {
      data[idx] = ....
  }

  */
  return 0;
}
/* USER CODE END 2 */

/* Entry points --------------------------------------------------------------*/

void MX_X_CUBE_AI_Init(void)
{
    /* USER CODE BEGIN 5 */
  printf("\r\nTEMPLATE - initialization\r\n");

  ai_boostrap(data_activations0);
    /* USER CODE END 5 */
}

void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 6 */
printf("AI 引擎已启动，准备识别...\r\n");

    while(1) {
        // 1. 将你的图片数组喂给 AI 的输入缓冲区
        // 你的代码版本中，输入缓冲区指针是 data_ins[0]
        float *in_ptr = (float *)data_ins[0];
        for (int i = 0; i < 784; i++) {
            in_ptr[i] = my_test_image[i];
        }

        // 2. 运行神经网络推理 (你的版本使用的是 ai_run)
        int res = ai_run();

        // 3. 如果运行成功 (ai_run 成功返回 0)，解析输出结果
        if (res == 0) { 
            // 你的代码版本中，输出缓冲区指针是 data_outs[0]
            float *out_ptr = (float *)data_outs[0];
            float max_prob = out_ptr[0];
            int max_index = 0;

            // 遍历 10 个数字的概率，找出最大的那个
            for (int i = 1; i < 10; i++) {
                if (out_ptr[i] > max_prob) {
                    max_prob = out_ptr[i];
                    max_index = i;
                }
            }

            // 打印最终结果
		printf("----------------------------------\r\n");
		printf("Result: %d \r\n", max_index);
		printf("Probability: %.2f%% \r\n", max_prob * 100.0f);
		printf("----------------------------------\r\n\n");
        } else {
            printf("AI 推理运行失败！错误码: %d\r\n", res);
        }

        // 停顿 2 秒，防止串口打印太快刷屏
        HAL_Delay(2000); 
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
    /* USER CODE END 6 */
}
#ifdef __cplusplus
}
#endif
