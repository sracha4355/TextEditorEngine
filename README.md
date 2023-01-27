# TextEditorEngine
A Text editor engine that utilizes a gap Buffers stored in a binary search tree for efficient text manipulation, allowing for fast insertion and deletion of large text files, and with the ability to read and write files from and to your system. This engine can be used as a backend for a text editor.

IN-DEPTH DOCUMENTATION *need to insert hyperlink here*

How to build using cmake and use library: 
- clone repo
- point your CMakeLists.txt to the CMakeLists.txt file contained in root directory via add_subdirectory(path/to/cloned/repo)
- add these include statements: #include <buffer.h> and #include <file.h> to a .h/.cpp and enjoy!

How to manipulate a buffer:
- instantiate a TextBuffer object: TextBuffer tb;
- then you can use tb's methods to manipulate the buffer, 
- remember the TextBuffer is an std :: map which operates as Red-Black Tree(self-balancing bst) under the hood. The class maps line numbers to GapBuffers
How to read in an existing file into a TextBuffer:
- instantiate a File Object: File file;
- File is implemented as a struct, so intialize these 2 member variables this way: file.m_buffer = *a ptr to your TextBuffer* 
file.m_fileName = *your path to file*
- to read data from a file to a TextBuffer call file.readData(), once to write the buffer's contents into a file do file.writeData()
- to clear a file file.clearData() *note this will erase data in a file*
- you really only need to use readData() and writeData()


Gap Buffer is a simple data structure used for efficent insertion and deletion, both O(1) into an array: great use case for text buffers.
In this library the Text Buffer is self-balancing Binary Search Tree (BST), which holds individual Gap Buffers to represent lines of a file.
If a file become very large, let's say 10000 lines, if we want to edit line 9000, we can access line 9000 in O(log n) time.

What this engine provides is a simple interface that can be built on top of:
- reading data from a file into a Text Buffer
- functions to easily modify the buffer
- write changes made to a file into the system
- efficent insertion, deletion, and access to data

I apologize for any bugs I missed, hack and test this library to your liking!!!

