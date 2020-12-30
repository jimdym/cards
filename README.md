# cards
Emulate the way I use 3x5 cards.

This works only on linux. I don't have a C compiler for windows, but I may get one someday just to see if I can make it work the same way.

starting requirements:
1. it should work with text files that can be modified with a standard text editor
2. there can be links to non text files
3. i'm shooting for a 3x5 card with unlimited size
4. cards are uniquely identified by a "serial number"
5. cards have 0 or more "names"
6. cards have 0 or more comments
7. a "serial number" consists only of 0,1,2,3,4,5,6,7,8,9
8. a card is a collection of "lines", the serial number line starts a card, the next serial number line terminates the current card.

20201224 - The first iteration just added a card to the end of the file with one name and one comment. This next series of changes will allow for finding the card (by serial number) corresponding to a name, then adding additional names and comments. The new modules will be called listMatches, addName, and addComment.

20201226 - adding a program to display a card (all records associated with a serial). It looks like the first name record added has no date. Not really a bug, but maybe I should add it. The way I use a card file, the first name is really what the card is about although it doesn't have to be that way - I certainly have ambiguous cars in my file box.

20201226 - adding a userManual.html file. This should bring me current with the work I've already done and be a pretty functional, albeit barebones, system.

20201229 - add tech manual and prettified card display almost certainly as a web page. modify addCard.c to create file if it DNE.
