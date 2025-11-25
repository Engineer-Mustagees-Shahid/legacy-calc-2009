
#include "LoanCalculator.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <stdexcept>

LoanCalculator::LoanCalculator() {}

void LoanCalculator::validatePositive(long double value, const std::string &msg)
{
    if(value < 0)
        throw std::invalid_argument(msg);
}

void LoanCalculator::setAmount(long double A)
{
    validatePositive(A, "Amount cannot be negative");
    amount_ = A;
}

long double LoanCalculator::getAmount() const { return amount_; }

void LoanCalculator::setInitialPayment(long double initialA)
{
    validatePositive(initialA, "Initial payment cannot be negative");
    initialPayment_ = initialA;
}

long double LoanCalculator::getInitialPayment() const { return initialPayment_; }

void LoanCalculator::setInterest(long double i)
{
    validatePositive(i, "Interest cannot be negative");
    interest_ = i;
    interestPeriodic_ = (i / 100.0L) / 12.0L;
}

long double LoanCalculator::getInterest() const { return interest_; }

void LoanCalculator::setPayment(long double P)
{
    validatePositive(P, "Payment cannot be negative");
    payment_ = P;
}

long double LoanCalculator::getPayment() const { return payment_; }

void LoanCalculator::setPeriodTotal(int N)
{
    if(N <= 0) throw std::invalid_argument("Period must be positive");
    periodTotal_ = N;
}

int LoanCalculator::getPeriodTotal() const { return periodTotal_; }

void LoanCalculator::setPeriodElapsed(int n)
{
    if(n < 0) throw std::invalid_argument("Elapsed period cannot be negative");
    periodElapsed_ = n;
}

int LoanCalculator::getPeriodElapsed() const { return periodElapsed_; }

void LoanCalculator::setOpeningFee(long double fee)
{
    validatePositive(fee, "Opening fee cannot be negative");
    openingFee_ = fee;
}

long double LoanCalculator::getOpeningFee() const { return openingFee_; }

void LoanCalculator::setOpeningPercent(long double percent)
{
    validatePositive(percent, "Opening percent cannot be negative");
    openingPercent_ = percent;
}

long double LoanCalculator::getOpeningPercent() const { return openingPercent_; }

void LoanCalculator::reset()
{
    amount_ = initialPayment_ = interest_ = interestPeriodic_ = payment_ = openingFee_ = openingPercent_ = 0;
    periodTotal_ = periodElapsed_ = 0;
}

long double LoanCalculator::calculatePayment()
{
    if(amount_ <= 0 || interest_ <= 0 || periodTotal_ <= 0)
        throw std::invalid_argument("Missing required parameters");

    long double principal = amount_ - initialPayment_;
    principal += openingFee_ + (principal * openingPercent_ / 100);

    return (interestPeriodic_ * principal) / (1 - powl(1 + interestPeriodic_, -periodTotal_));
}

long double LoanCalculator::calculateLoanBalance()
{
    return (amount_ * powl(1 + interestPeriodic_, periodElapsed_)) -
           (payment_ / interestPeriodic_) * (powl(1 + interestPeriodic_, periodElapsed_) - 1);
}

long double LoanCalculator::calculateNumberPayments()
{
    return -logl(1 - (interestPeriodic_ * amount_ / payment_)) /
            logl(1 + interestPeriodic_);
}

long double LoanCalculator::calculateLoanAmount()
{
    return (payment_ / interestPeriodic_) * (1 - powl(1 + interestPeriodic_, -periodTotal_));
}

long double LoanCalculator::calculateInterestRate()
{
    return interest_;
}

long double LoanCalculator::calculateEffectiveInterestRate()
{
    long double payment = calculatePayment();
    return ((payment * periodTotal_) - amount_) / amount_ * 100;
}

std::string LoanCalculator::toString() const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);

    ss << "Loan Summary:\n";
    ss << "Amount: " << amount_ << "\n";
    ss << "Interest: " << interest_ << "%\n";
    ss << "Payment: " << payment_ << "\n";
    ss << "Period: " << periodTotal_ << " months\n";

    return ss.str();
}

