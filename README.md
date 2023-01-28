# Memory Game on Pt-51 Using 8051 Microprocessor
In the game, the LCD will display a sequence of 10 word-digit pairs, where each
pair is displayed for 1 second. A random digit from 0 to 9 is shown next to each
Each word is 4 letters long.  

After the 10 word-digit pairs have been displayed, there is a delay of 3 seconds
with the LCD displaying the string.

Then the same sequence of 10 words from the list appears one at time with each word displayed for 3 seconds. In the 3 second duration,
the player is expected to type the digit which appeared next to the word in the
beginning of the game. The digit typed by the player should appear on the
second line.

After all 10 words have been shown, the number of correct guesses is displayed
on the  LCD line and the highest score so far is displayed on the second
LCD line


The word-digit pairs are generated using  linear feedback shift register (LFSR) of length 5 to generate
pseudorandomness.
