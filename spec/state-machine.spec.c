#include <check.h>
#include "tests.h"
#include "../state-machine.h"

void setupSimple(void) {
  setMode(SIMPLE);
}

void teardownSimple(void) {
  setMode(SIMPLE);
}

START_TEST(initialStateMachine)
{
  SafeLightState state = nextState();
  ck_assert_int_eq(state.next, 1);
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
}
END_TEST

START_TEST(setModeSimpleReset)
{
  SafeLightState state = nextState();
  ck_assert_int_eq(state.next, 1);
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
  setMode(SIMPLE);
  SafeLightState newState = nextState();
  ck_assert_int_eq(newState.next, 1);
  ck_assert_int_eq(newState.a, RED);
  ck_assert_int_eq(newState.b, RED);
}
END_TEST

START_TEST(simpleSequence)
{
  SafeLightState state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, GREEN);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, AMBER);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, GREEN);
  state = nextState();
  ck_assert_int_eq(state.next, 0);
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, AMBER);
  state = nextState();
  ck_assert_int_eq(state.next, 1);
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
}
END_TEST

START_TEST(advanceASequence)
{
  setMode(ADVANCE_A);
  SafeLightState state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, ADVANCE);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, GREEN);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, AMBER);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, GREEN);
  state = nextState();
  ck_assert_int_eq(state.next, 0);
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, AMBER);
  state = nextState();
  ck_assert_int_eq(state.next, 1);
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
}
END_TEST

START_TEST(advanceBSequence)
{
  setMode(ADVANCE_B);
  SafeLightState state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, GREEN);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, AMBER);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, ADVANCE);
  state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, GREEN);
  state = nextState();
  ck_assert_int_eq(state.next, 0);
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, AMBER);
  state = nextState();
  ck_assert_int_eq(state.next, 1);
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
}
END_TEST

START_TEST(advanceABSequence)
{
  setMode(ADVANCE_AB);
  SafeLightState state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, ADVANCE);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, GREEN);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, AMBER);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
  state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, ADVANCE);
  state = nextState();
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, GREEN);
  state = nextState();
  ck_assert_int_eq(state.next, 0);
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, AMBER);
  state = nextState();
  ck_assert_int_eq(state.next, 1);
  ck_assert_int_eq(state.a, RED);
  ck_assert_int_eq(state.b, RED);
}
END_TEST

Suite *stateMachineSuite(void)
{
    Suite *s;
    TCase *tc_core;
    TCase *tc_limits;

    s = suite_create("State Machine");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setupSimple, teardownSimple);
    tcase_add_test(tc_core, initialStateMachine);
    tcase_add_test(tc_core, setModeSimpleReset);
    tcase_add_test(tc_core, simpleSequence);
    tcase_add_test(tc_core, advanceASequence);
    tcase_add_test(tc_core, advanceBSequence);
    tcase_add_test(tc_core, advanceABSequence);
    suite_add_tcase(s, tc_core);

    // /* Limits test case */
    // tc_limits = tcase_create("Limits");

    // tcase_add_test(tc_limits, test_money_create_neg);
    // tcase_add_test(tc_limits, test_money_create_zero);
    // suite_add_tcase(s, tc_limits);

    return s;
}
