/* Given a principal amount and an interest rate,    */
/* this program computes principal payments and      */
/* total interest paid for the duration of the loan. */
/* For each payment period, the program shows the    */
/* balance remaining at the end of that period,      */
/* as well as how much of each payment goes to       */
/* interest. Useful for figuring out payment         */
/* strategies and the cost of borrowing.             */

/* This version compounds interest semi-annually,    */
/* doing it according to the bank's formula.         */

/* This is a discrete-time (time-stepped) simulation  */
/* model (even though it is deterministic).          */
/* Fixed: taxes was uninitialized; added safety stop; */
/* set INTERACTIVE off for batch runs; taxes=0.      */

#include <stdio.h>
#include <math.h>

/* Set to 0 for hardcoded values (non-interactive) */
#define INTERACTIVE 0

#define MONTH_FUDGE 1 /* Hack month stuff */

float interest;
float taxes = 0.0;  /* FIXED: was uninitialized, set to 0 (no taxes) */
float amount;
float payment;

int main(void)
{
    float intamt;
    float inttotal;
    int paymentnum;
    int paymentsperyear;
    int max_payments = 10000; /* safety to prevent infinite loop */

    /* Daily interest factor, period interest factor.  */
    double dif, pif;
    /* annual interest rate, and compounding frequency */
    float a, f;
    int days;
    double x, y;

#if INTERACTIVE
    printf(" Amount of loan? ");
    scanf("%f", &amount);

    printf("Annual interest rate? ");
    scanf("%f", &interest);

    printf("Payment interval? (in days) ");
    scanf("%d", &days);

    printf("Payment size? ");
    scanf("%f", &payment);
#else
    /* Hardcoded example values for demonstration */
    amount = 100000.0;
    interest = 10.5;
    payment = 1000.00;  /* reasonable monthly-ish payment */
    days = 30;
#endif
    paymentsperyear = (int) (0.3 + 1.0*365.0/days);

    /* Compute daily interest factor */
    f = 2;  /* semi-annual compounding */
    a = 0.01 * interest;
    x = 1 + a/f;
    y = f/365.0;

    dif = pow(x, y) - 1;

    x = 1.0 + dif;
    y = 1.0 * days;
    pif = pow(x, y) - 1;

    printf("\n\n         --- Mortgage Payment Summary ---\n\n");
    printf("Initial amount: $%.2f\n", amount);
    printf("Annual interest rate: %.3f%%\n", interest);
    printf("Payment size: $%.2f\n", payment);
    printf("Payment period: every %d days\n", days);
    printf("Taxes per period: $%.2f\n\n", taxes);

    printf("Payment  Taxes   Interest  PPLReduction  PPLBalance   TotalInterest\n");
    printf("--------------------------------------------------------------------\n");
    inttotal = 0;
    paymentnum = 1;

    while (amount > 0.01 && paymentnum <= max_payments)
    {
        intamt = amount * pif;
        /* principal reduction = payment - interest - taxes */
        float prin_red = payment - intamt - taxes;
        if (prin_red < 0) {
            /* payment too small to cover interest */
            printf("Warning: payment too small to cover interest at payment %d\n", paymentnum);
            break;
        }
        amount = amount + intamt - (payment - taxes);
        if (amount < 0) amount = 0; /* avoid negative due to overpay */
        inttotal += intamt;
        printf("  %4d  %6.2f  %8.2f   %10.2f   %12.2f    %12.2f\n",
               paymentnum, taxes, intamt, prin_red, amount, inttotal);
        if (paymentnum % paymentsperyear == 0)
        {
            printf("   ------------  End of year %d ----------- \n",
                   paymentnum/paymentsperyear);
        }
        paymentnum++;
#ifdef MONTH_FUDGE
        /* Kludge to approximate a year better for monthly payments */
        if (days == 30)
            days = 31;
        else if (days == 31)
            days = 30;
        /* Recompute pif */
        x = 1.0 + dif;
        y = 1.0 * days;
        pif = pow(x, y) - 1;
#endif
    }
    if (paymentnum > max_payments) {
        printf("Stopped after %d payments (safety limit).\n", max_payments);
    }
    printf("Total interest paid: %.2f\n", inttotal);
    printf("Number of payments: %d\n", paymentnum - 1);
    return 0;
}
