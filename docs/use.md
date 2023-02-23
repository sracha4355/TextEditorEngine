# How to use
## Step 1: Integrate into project using cmake
**There is a CMakeLists.txt file already made for you, wherever in your project you need to build and import the library integrate the CMakeLists.txt command through the add_subdirectory() directive in your own CMakeLists.txt file**


## Step 2: import "buffer.h" and "file.h"

## Step 3: Instantiate a TextBuffer object  
**TextBuffer obj;** 
  
**Now we can use the methods of the TextBuffer Class to manipulate the buffer. The docs will cover all the methods that we can use**

## Step 4: Read a file's contents into the TextBuffer
**File is implemented as a struct, so intialize these 2 member variables this way:**   
**file.m_buffer = "a pointer to your TextBuffer"** 
**file.m_fileName = "your path to file"** 
**Now, read data  from the file into your text buffer using file.readData()**
 
## Step 5: Write the buffer along with its new changes back into the file
**To save changes back into a file use**  
**file.writeData()**

