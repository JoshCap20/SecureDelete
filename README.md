# Secure File Deletion

This program securely deletes a given file by overwriting its binary contents with random data multiple times before deleting it. The process reduces the chances of recovering the original file data using data recovery tools or forensic techniques.

## Usage

To compile the program, use the provided Makefile:  
`make`

To run the program, provide the file name and optionally the number of passes (the default is 3 passes):  

`./secure_delete <file> [<passes>]`

## Example

To securely delete a file named 'example.txt' with the default number of passes:  

`./secure_delete example.txt`


Or, to securely delete the same file using 5 passes:  

`./secure_delete example.txt 5`
