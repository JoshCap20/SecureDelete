# Secure File Deletion

This program securely deletes a given file by overwriting its binary contents with random data multiple times before deleting it. The process reduces the chances of recovering the original file data using data recovery tools or forensic techniques.

## Rewriting Logic

The program uses a pseudorandom number generator to create random data for overwriting the original file content. By default, the file is overwritten three times (this number can be adjusted with the `-p` or `--passes` option), ensuring a more secure deletion process.

Each pass generates a new set of random data, which is then written to the file, effectively masking the original content. After the specified number of passes, the program deletes the file from the filesystem. This multi-pass overwriting approach helps to prevent data recovery by making it difficult to reconstruct the original data from the overwritten file.

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
