This repository contains the source codes for the paper, '**{Improved Differential Cryptanalysis of ARADI} **'.

## Language Used for code
1. C-language

## Setup

1. To install gcc, use the following command:
	* `sudo apt update`
	* `sudo apt install build-essential`


## File Structure

1.  `functions.h': Script for writing necessary functions for encryption and decryption of ARADI.

2.  `toyaradi_function.h': Script for writing necessary functions for encryption and decryption of toy version of ARADI.

3.  `2filterrightpair.c': Script to find the average number of survival keys when the pair is a right pair.

4.  `nWRONGPAIR.c': Script to find the average number of survival keys when the pair is a wrong pair.

5.  `toyrightpair.c': Script to find the average number of survival keys when the pair is a right pair in the toy version of ARADI.

6.  `toywrongpair.c': Script to find the average number of survival keys for any wrong pair in the toy version of ARADI.



## Usage
1. compile the programme: `gcc file_name.c `
2. run the file:           `./a.out`
