# cards
Emulate the way I use 3x5 cards
I want to start a project that emulates how I use 3x5 cards using github. it should eventually morph into my people project (in fact, I'll use the code from that project).

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
