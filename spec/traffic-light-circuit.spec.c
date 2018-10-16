#include <check.h>
#include "tests.h"
#include "../traffic-light-circuit.h"

typedef struct results {
  int pinMode;
  int digitalWrite;
} Results;

Results g_results;

void mockPinMode(unsigned char pin, unsigned char mode) {
  g_results.pinMode += pin + mode;
}

void mockDigitalWrite(unsigned char pin, unsigned char output) {
  if (output == 0) {
    return;
  }
  g_results.digitalWrite += pin + output;
}

void setup(void) {
  TrafficLightCircuitEnvironment env = {
      1,
      0,
      2,
      &mockDigitalWrite,
      &mockPinMode,
      {
          1, 2, 3,
      },
      {
          4, 5, 6,
      }
    };
   setTrafficLightCircuitEnvironment(env);
   g_results.pinMode = 0;
   g_results.digitalWrite = 0;
}


START_TEST(check_trafficLightCircuitInitializePins)
{
  trafficLightCircuitInitializePins();
  ck_assert_int_eq(g_results.pinMode, 33);
}
END_TEST

START_TEST(check_safeSetLights_red_red)
{
  safeSetLights(1, 1);
  ck_assert_int_eq(g_results.digitalWrite, 7);
}
END_TEST

START_TEST(check_safeSetLights_red_green)
{
  safeSetLights(1, 3);
  ck_assert_int_eq(g_results.digitalWrite, 9);
}
END_TEST

START_TEST(check_safeSetLights_green_green)
{
  /** DANGER CASE, NOTE THIS IS THE SIGNAL FOR RED/RED */
  safeSetLights(3, 3);
  ck_assert_int_eq(g_results.digitalWrite, 7);
}
END_TEST

START_TEST(check_safeSetLights_green_amber)
{
  /** DANGER CASE, NOTE THIS IS THE SIGNAL FOR RED/RED */
  safeSetLights(3, 2);
  ck_assert_int_eq(g_results.digitalWrite, 7);
}
END_TEST

START_TEST(check_safeSetLights_amber_green)
{
  /** DANGER CASE, NOTE THIS IS THE SIGNAL FOR RED/RED */
  safeSetLights(2, 3);
  ck_assert_int_eq(g_results.digitalWrite, 7);
}
END_TEST

START_TEST(check_safeSetLights_amber_amber)
{
  /** DANGER CASE, NOTE THIS IS THE SIGNAL FOR RED/RED */
  safeSetLights(2, 2);
  ck_assert_int_eq(g_results.digitalWrite, 7);
}
END_TEST

Suite *trafficLightCircuitSuite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Traffic Light Circuit");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, setup);

    tcase_add_test(tc_core, check_trafficLightCircuitInitializePins);
    tcase_add_test(tc_core, check_safeSetLights_red_red);
    tcase_add_test(tc_core, check_safeSetLights_red_green);
    tcase_add_test(tc_core, check_safeSetLights_green_green);
    tcase_add_test(tc_core, check_safeSetLights_green_amber);
    tcase_add_test(tc_core, check_safeSetLights_amber_green);
    tcase_add_test(tc_core, check_safeSetLights_amber_amber);
    suite_add_tcase(s, tc_core);

    return s;
}
