# Secure File Deletion

This program securely deletes a given file by overwriting its binary contents with random data multiple times before deleting it. The process reduces the chances of recovering the original file data using data recovery tools or forensic techniques.

## Usage

To compile the program, use the provided Makefile:  

`make`

To run the program, provide the file name and optionally the number of passes and verbosity using the following options:

`./secure_delete [options] <file>`

Options:
- `-v, --verbose`: Show original and edited binary content.
- `-p NUM, --passes NUM`: Set the number of overwrite passes (default: 3).
- `-h, --help`: Show the help message.

## Example

To securely delete a file named 'example.txt' with the default number of passes:  

`./secure_delete example.txt`


To securely delete the same file using 5 passes and show the original and edited binary content: 

`./secure_delete -p 5 -v example.txt`
