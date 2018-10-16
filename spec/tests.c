#include <check.h>
#include "tests.h"

int main(void)
{
  SRunner *sr;
  int fails;

  sr = srunner_create(stateMachineSuite());
  srunner_add_suite(sr, trafficLightCircuitSuite());

  srunner_set_tap (sr, "-");

  srunner_run_all(sr, CK_VERBOSE);
  fails = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (fails == 0) ? 0 : 1;
}
