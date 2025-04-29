#include "leitor_temperatura_testado.h"
#include "unity.h"


// Unity requires these two functions
void setUp(void) {}
void tearDown(void) {}


void test_funcao_temperatura(void){
    float temperature = adc_to_temperature(876);
    TEST_ASSERT_FLOAT_WITHIN(0.2f, 27, temperature);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(test_funcao_temperatura);
    return UNITY_END();
}