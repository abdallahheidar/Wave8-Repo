/*
 * tester.h
 *
 * Created: 3/13/2020 9:21:04 AM
 *  Author: mahmo
 */ 


#ifndef TESTER_H_
#define TESTER_H_
#include <stdio.h>
#include "../../common_macros.h"
#include "../../std_types.h"
#include "../../HAL/UltraSonic/ultraSonic.h"
#include "stubFunction.h"
#include "../TMU_test/TMU_test.h"
#include "../SOS_test/SOS_test.h"
#include "../Us_test/UltraSonic_test.h"
void checkTestCase(sint16_t s16_expected_return , sint16_t s16_fun_return,uint8_t * u8_testCaseNumber);
void parameter_test(uint8_t* u8_testParamterValues,uint8_t u8_size ,ERROR_STATUS (*callB_fun)(uint8_t), sint16_t ERROR_VALUE,uint8_t * u8_testCaseNumber);
void test();
#endif /* TESTER_H_ */