# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

According to the *Oxford English Dictionary*, it is "an artificial long word said to mean a lung disease caused by inhaling very fine ash and sand dust". Consisting of 45 letters, it is the longest word in the English language.

## According to its man page, what does `getrusage` do?

The name `getrusage` means "get resource usage". It returns resource usage measures for `who`, which can be one of the following: `RUSAGE_SELF`, `RUSAGE_CHILDREN` or `RUSAGE_THREAD`.  
In `speller.c` it is always `RUSAGE_SELF`, it returns
resource usage statistics for the calling process, which is the sum of resources used by all threads in the process.


## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because it saves memory and time: passing the values includes copying the two 16 member `struct`s. As the purpose of `getrusage()` is to track the required resources (e.g., time and RAM), the results would be inaccurate.


## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The `for` loop reads words from the text by checking their characters one by one, until it reaches the end of the file. If the character is a letter or apostrophe, it is added to `word`. 

It also checks if the created word is longer than the size of the largest word possible (as we have defined it previously as 45), or if the word contains a digit. In both cases the word will be ignored, and the program prepares for a new word by closing the current one and resetting the character `index` to 0.

If the word is assumed to be valid, the `words` counter is updated. 

Then `time_check` logs the amount of time it took the program to complete the check.

Finally, the spelling of the word is checked, and if it is misspelled, it gets printed and the `misspellings` counter is incremented. Then the character position `index` is reset to 0, so that the loop starts checking the next word .


## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

`fgetc` reads characters one by one from a stream, enabling us to keep track of the number of chars we read.

`fscanf` reads up to a whitespace, so it might not stop at the end of a word, as it can interpret commas or periods as part of the word. Consequently, it can overrun the target buffer, leading to buffer overflow.


## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

This way they cannot be (accidentally) modified, if we tried to do so, it would throw an error message. 
