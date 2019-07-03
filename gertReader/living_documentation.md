// This is a comment
// I'd recommend leaving the space above your first Chapter blank, unlike what I've done here.
// it likely won't mess up the program but I'd consider it undefined behavior

# Welcome
This is a working document gr can run
The '#' denotes a Chapter's title and everything after it will be a part of that chapter, until another Chapter is declared the same way.

Within two square brackets '[[' you can define a link, this can be done inline [[like so]]

To alter the link text and location separately put a pipe '|' inside the brackets, the left side will be shown text, and the right side will be the link location.
[[shown text | link location]]

The next Chapter will cover [[Functions]]

# like so
You've selected the first link example.
[[back | Welcome]]

# link location
You've selected the second link example.
[[back | Welcome]]
[[first link | like so]]

#Functions
Functions follow this syntax '(word: parameter)' where 'word' is the operation and 'parameter' is it's operand.
The following words are valid functions:

SET
UNSET
IF
ELSE-IF
ELSE
AND

Parameters can be most any word, though some functions take no parameters, such as ELSE.
[[set and unset | Variables]]
(if: viewed_variables) [[if, else-if, else, and and | Conditionals]]
[[back | Welcome]]

# Variables
SET and UNSET create "Variables" which can be used in conditionals to create alternating paths and repercussions in the story.
SET and UNSET are executed when the player reaches the chapter, with exceptions mentioned in [[Conditionals]].
(set: viewed_variables)
Now when you go back to Chapter [[Functions]] you'll see another link for the chapter on conditionals, 'if, else-if, else, and and'.

[[start | Welcome]]
[[back | Functions]]

# Conditionals
IF alters how other functions behave and if text/links are shown

(if: conditional_example) (else:) [[show example]]
(if: conditional_example) [[hide example]]

[[start | Welcome]]
[[Functions]]
[[Variables]]

# show example
Example will be shown
(set: conditional_example)
[[back | Conditionals]]

# hide example
Example will be hidden
(unset: conditional_example)
[[back | Conditionals]]
