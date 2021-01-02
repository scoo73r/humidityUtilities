#include <humidity.h>
#include <unity.h>
void test_setAirPressure()
{
    Humidity humidity;
    TEST_ASSERT_EQUAL_DOUBLE(1010.0, humidity.getAirPressure());
    humidity.setAirPressure(2000);
    TEST_ASSERT_EQUAL_DOUBLE(2000.0, humidity.getAirPressure());
    humidity.setAirPressure(10000.0);
    TEST_ASSERT_EQUAL_DOUBLE(10000.0, humidity.getAirPressure());
}

void process()
{
    UNITY_BEGIN();
    RUN_TEST(test_setAirPressure);
    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>
void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    process();
}

void loop()
{
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}

#else

int main(int argc, char **argv)
{
    process();
    return 0;
}

#endif