# Project Overview
The TextEditorEngine provides a interface to create and manipulate a text buffer. A text buffer can be used to store the content's of a file in a systematic format, and we can manipulate the buffer's contents

## The structure of the Text Buffer
The text buffer is a self-balancing binary search tree which holds individual Gap Buffers. The Gap Buffer is another data structure we use to represent individual lines in the Text Buffer. So the tree's node contain line numbers as keys, which point to Gap Buffers. The Gap Buffer is data structure has an efficient in-place insertion and deletion, O(1).  


