#include "LoanCalculator.h"
#include <gtest/gtest.h>
#include <cmath>    // <-- add this
#include <limits>

// Normal EMI calculation
TEST(LoanCalculatorTest, NormalEMICalculation) {
    LoanCalculator calc;
    calc.setAmount(100000.0L);
    calc.setInterest(6.0L);
    calc.setPeriodTotal(120);
    long double emi = calc.calculatePayment();
    EXPECT_NEAR((double)emi, 1110.21, 0.5);
}

// Invalid input handling
TEST(LoanCalculatorTest, InvalidInputsThrow) {
    LoanCalculator calc;
    EXPECT_THROW(calc.setAmount(-50.0L), std::invalid_argument);
    EXPECT_THROW(calc.setInterest(-1.0L), std::invalid_argument);
    EXPECT_THROW(calc.setPayment(-10.0L), std::invalid_argument);
    EXPECT_THROW(calc.setPeriodTotal(0), std::invalid_argument);
}

// Large tenure calculations without overflow
TEST(LoanCalculatorTest, LargeTenureNoOverflow) {
    LoanCalculator calc;
    calc.setAmount(1e12L);
    calc.setInterest(8.0L);
    calc.setPeriodTotal(100 * 12);
    long double emi = calc.calculatePayment();
    ASSERT_FALSE(std::isnan(emi));
    ASSERT_FALSE(std::isinf(emi));
    EXPECT_GT(emi, 0.0L);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
