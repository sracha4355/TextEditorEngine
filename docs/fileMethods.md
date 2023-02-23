## How to use File module
**instantiate a FILE object, File file**  
TextBuffer * m_buffer;  
**string m_fileName;**  
**set m_buffer to a pointer that point to a TextBuffer object**  
**set m_fileName to a file path that points to your desired file**

## bool readData();
**once m_buffer and m_fileName are set, use readData() to read contents from a file and into the TextBuffer**
## bool writeData();
**once m_buffer and m_fileName are set, use writeData() to write the buffer's contents into the file we read from intitally**
