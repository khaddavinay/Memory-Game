# Memory Game on Pt-51 Using 8051 Microprocessor
In the game, the LCD will display a sequence of 10 word-digit pairs, where each
pair is displayed for 1 second. A random digit from 0 to 9 is shown next to each
word.
{ For example, a sequence could be the following:
king 5
idea 7
left 0
good 1
exit 5
taxi 5
chef 3
lava 1
cafe 2
logo 9
{ Each word is 4 letters long.
{ Words should not repeat in the list, i.e. all the 10 words should be dierent.
{ The digits next to the word can repeat.
 After the 10 word-digit pairs have been displayed, there is a delay of 3 seconds
with the LCD displaying the string Get Ready on the rst line. The second line
is blank.
 Then the same sequence of 10 words from the list appears one at time on the
rst line, with each word displayed for 3 seconds. In the 3 second duration,
the player is expected to type the digit which appeared next to the word in the
beginning of the game. The digit typed by the player should appear on the
second line.
 After all 10 words have been shown, the number of correct guesses is displayed
on the rst LCD line and the highest score so far is displayed on the second
LCD line, for 3 seconds. For example, if the player get four digits correct in
the current game and has a high score of 8, then the display will look like the
following.


Score: 4
High Score: 8
 After showing the score, the game restarts by showing a new sequence of 10
word-digit pairs.
 To make the game interesting, the word-digit pairs need to change from game to
game. We will use a linear feedback shift register (LFSR) of length 5 to generate
pseudorandomness.
