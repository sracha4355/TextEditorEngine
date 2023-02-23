# Quick overview of the Project Structure  
**~ indicates root directory**
## ~/src 		
**Contains the modules pertaining to manipulating a TextBuffer and reading andwriting to that TextBuffer**

## ~/src/File
**Contains the File module, which is used to read a file's contents into
a TextBuffer object, and it is used to write a buffer's contents into storage.**

## ~/src/TextBuffer
**Contains the TextBuffer class. The class will allow us to instantiate a TextBuffer Object, and the class will provide methods to manipulate the contents of the buffer**

## ~/src/gapBuffer	
**Contains the gapBuffer class. This class provides a Gap Buffer data structure that can be manipulated. Our TextBuffer class is a self-balancing binary search tree that contains indiviual Gap Buffers to represent lines**
