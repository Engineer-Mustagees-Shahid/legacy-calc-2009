#ifndef LOANCALCULATOR_H_INCLUDED
#define LOANCALCULATOR_H_INCLUDED

#include <string>

/**
 * @brief Simple loan calculator for common loan calculations (EMI, balance, etc).
 *
 * Uses yearly interest in percent (e.g. 6.5) which is converted internally to a
 * monthly periodic interest value.
 */
class LoanCalculator
{
public:
    /**
     * @brief Construct a new LoanCalculator object.
     */
    LoanCalculator();

    /**
     * @brief Set the initial loan amount (principal).
     * @param A Principal amount (must be >= 0)
     * @throws std::invalid_argument if A < 0
     */
    void setAmount(long double A);

    long double getAmount() const;

    /**
     * @brief Set an initial upfront payment applied to the loan.
     * @param initialA Upfront payment (must be >= 0)
     * @throws std::invalid_argument if initialA < 0
     */
    void setInitialPayment(long double initialA);
    long double getInitialPayment() const;

    /**
     * @brief Set the yearly interest rate (percent).
     * @param i Yearly interest in percent (e.g. 6.5). Must be >= 0.
     * @throws std::invalid_argument if i < 0
     */
    void setInterest(long double i);
    long double getInterest() const;

    /**
     * @brief Set the monthly payment. (Used when computing number of payments, etc.)
     * @param P Monthly payment amount (must be >= 0)
     * @throws std::invalid_argument if P < 0
     */
    void setPayment(long double P);
    long double getPayment() const;

    /**
     * @brief Set total loan period (months).
     * @param N Total months (must be > 0)
     * @throws std::invalid_argument if N <= 0
     */
    void setPeriodTotal(int N);
    int getPeriodTotal() const;

    /**
     * @brief Set elapsed payments (months).
     */
    void setPeriodElapsed(int n);
    int getPeriodElapsed() const;

    void setOpeningFee(long double fee);
    long double getOpeningFee() const;

    void setOpeningPercent(long double percent);
    long double getOpeningPercent() const;

    /**
     * @brief Reset all values to zero/default.
     */
    void reset();

    // Calculation methods (brief docs)
    /**
     * @brief Calculate loan balance after periodElapsed_ payments.
     * @return Remaining balance
     */
    long double calculateLoanBalance();

    /**
     * @brief Calculate monthly payment (EMI) using current values:
     *        amount_, initialPayment_, interest_, periodTotal_, openingFee_, openingPercent_.
     * @return monthly payment
     */
    long double calculatePayment();

    /**
     * @brief Calculate number of payments required given amount_, payment_, interest_.
     * @return number of payments (months)
     */
    long double calculateNumberPayments();

    long double calculateLoanAmount();
    long double calculateInterestRate();
    long double calculateEffectiveInterestRate();

    /**
     * @brief Return a compact summary string of current values.
     * @return formatted string
     */
    std::string toString();

private:
    long double amount_;
    long double initialPayment_;
    long double interest_;
    long double interestPeriodic_;
    long double payment_;
    int periodTotal_;
    int periodElapsed_;
    long double openingFee_;
    long double openingPercent_;

    // Add this line:
    void validatePositive(long double value, const std::string &msg);
};

#endif // LOANCALCULATOR_H_INCLUDED
