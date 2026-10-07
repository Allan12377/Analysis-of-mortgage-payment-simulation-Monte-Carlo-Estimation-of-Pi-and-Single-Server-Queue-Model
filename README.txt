CODING ASSIGNMENT ONE - MODELING AND SIMULATION
Kabale University - Department of Computer Science
  (BSCS Year 3 Semester 1)
  
  Student:
1.	AINEBYONA ALLAN	2024/A/KCS/1670/F
2.	ARINDA ELIZABETH	2024/A/KCS/3099/G/F
3.	GUMISIRIZA AMBROSE	2024/A/KCS/3143/F



1. PRESENTATION
   - Coding_Assignment_One_Presentation.pptx
    

2. WRITTEN REPORT
   - Coding_Assignment_One_Report.docx
     

3. FIXED SOURCE CODES (ready to compile)
   - mortgage_fixed.c   Discrete-time mortgage amortisation simulator
   - pi_fixed.c         Monte Carlo estimation of Pi
   - ssq1_fixed.c       Single-server queue (trace-driven)
   - ssq1.dat           Input data file required by ssq1_fixed.c

4. ORIGINAL SOURCE FILES (for reference)
   - mortgage.txt, pi.txt, ssq1.txt, ssq1 dat.txt

5. ILLUSTRATIVE FIGURES
   - pi_convergence.png
   - ssq_metrics.png
   - mortgage_balance.png

HOW TO COMPILE AND RUN (Linux / macOS / WSL / MSYS2)
====================================================

Make sure you have a C compiler (gcc) installed.

1. Mortgage simulator (non-interactive demo values already set)
   gcc mortgage_fixed.c -o mortgage_fixed -lm
   ./mortgage_fixed

2. Pi estimator
   gcc pi_fixed.c -o pi_fixed -lm
   ./pi_fixed
   (then type the number of trials, e.g. 10000, and press Enter)

3. Single-server queue
   # place ssq1.dat in the same directory
   gcc ssq1_fixed.c -o ssq1_fixed -lm
   ./ssq1_fixed

WHAT WAS FIXED
==============

Mortgage:
  - taxes variable was never initialised (undefined behaviour) → set to 0.0
  - unbounded loop risk when payment cannot cover interest → safety limit + warning

Pi:
  - non-portable srandom/random → standard srand/rand
  - DEBUG always on → disabled for clean output
  - input validation added

SSQ:
  - classic while(!feof) off-by-one error → proper fscanf return-value test
  - incomplete structure initialiser → corrected
  - inter-arrival average calculated from last valid arrival

All three programs compile cleanly with gcc -Wall and produce the numerical
results reported in the presentation and the written report.

