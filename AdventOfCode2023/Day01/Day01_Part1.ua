# uiua v0.6.1

# Part 1
GetDigits ← ≡(⍜(°□)(▽≤@9.))⊜□¬∊, "\r\n"
GetNumberFromFirstAndLastDigit ← ⋕⊂⊃(⊢|⊢⇌)
SumOfCalibrationValues ← /+ ∵GetNumberFromFirstAndLastDigit GetDigits

# Input ← &sc
InputFile ← &fras "01.txt"
SumOfCalibrationValues InputFile

---
InputTest ← "1abc2\r\npqr3stu8vwx\r\na1b2c3d4e5f\r\ntreb7uchet"
⍤.= 142 SumOfCalibrationValues InputTest
---
