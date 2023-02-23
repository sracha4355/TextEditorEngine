## bool insert(char character );
**inserts a char into the Text Buffer based on the current position within the buffer, to describe current position we would say line number, then the location in the Gap Buffer of the line we are currently on**
## bool insert(string word);
**inserts a string into the Text Buffer based on the current position within the buffer, to describe current position we would say line number, then the location in the Gap Buffer of the line we are currently on**
		
## void setCurrentLine(int line);		
**This method will set the current line, in which our changes will take place**   
**important method: most edits will be made based on the current line**	

## bool remove();
**based on the current location in the textbuffer, remove can 
append two lines into one
or remove a character on the currentLine
if the beginning of the gap is at the beginning of the 
gap buffer array, then logically, the current line will be merged with the line above it**

Ex:  
 Hello world  
 Hello next line
 - if the gap buffer's gap of line 2 is at the beginning, a 
 remove operation will result in   
 Hello worldHello next line  
 -given the current line at the time of the operation was line 2	
			
## void createNewLine();
**creates a new line at the end of the buffer, so if there are four lines, a line 5 will be made**

## void shiftLines(char nlEscSeq = '\n');
**shifts a portion of text onto a line under the currentLine, how much of the text depends on the position in buffer**
			
## methods to move position in the buffer
### int moveRight();
**move the position one to the right**
### int moveLeft();
**move the position one to the left**
### int moveUp();
**move the current line up one, so now edits will be made on that line**
### int moveDown();
**move the current line down one, so now edits will be made on that line**
		
## int getNumOfLines();
**get the numbers of lines in the buffer**
## int getCurrentLine()
**get the current line we are making edits on**	
		
## GapBuffer * getLine(int line);
**get the reference to the gapBuffer that represents a line in our TextBuffer**

## void shiftLinesUp();
**shifts all line up by 1 with respect to the current line**
## void shiftLinesDown();
**shifts all down up by 1 with respect to the current line**
## string getLineContents(int);
**get the contents of a line in string format**
