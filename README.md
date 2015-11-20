# KMPTool
A string matching tool based on KMP algorithm (Knuth-Morris-Pratt Algorithm).
I wrote it in a pure C styple, it is both okay for GCC and G++.

# Code Example
![Alt text](https://github.com/lhCheung1991/KMPTool/blob/master/code_example.png?raw=true "Optional Title")

You should declare a KMPRes first, then call malKMPRes(KMPRes * res) to initialize it since it need so memory from heap. You can get the matched position in KMPRes.matchPos and the length of KMPRes.matchPos in KMPRes.matchCount. Don't forget to call delKMPRes(KMPRes * res) to recycle the heap memory.

![Alt text](https://github.com/lhCheung1991/KMPTool/blob/master/code_example_output.png?raw=true "Optional Title")
