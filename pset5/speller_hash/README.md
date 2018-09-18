# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

The longest word ever in the English dictionary and a synonym for the disease known as silicosis.

## According to its man page, what does `getrusage` do?

It returns resource usage measures.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

By passing them by reference we save memory and time. If we would pass them by value it would make a copy of those structs, which uses time and memory space.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

We iterate over each character in the file until we reach the end of the file (EOF). While we do this, we look at the current character. If it is either alphabetical or an apostrophe that is not at the beginning of a word, we found a legal character to build our word.
We can now append this character if we are already in the building process of a word or we start building a new word. If our word becomes too large (larger than the longest word in the dictionary) or we encounter any numbers we can skip the current word and start building a new one.
Finally if we encounter any other characters listed above, like a space, period etc. we know that our word is finished. We add the null terminator to it's end to finish the word string and we can check it against the dictionary.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

By using fscanf we would have problems when a "real" word is followed by a period, comma or any other non-whitespace character. fscanf would treat those characters as a part of the word and this produces issues if we want to check such a word against our disctionary.
We also don't want to check any words longer than LENGTH (in our case 45) characters. A text could have very long gibberish words in it or maybe someone created a text file without any spaces which would look to fscanf like one huge long word.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

const makes sure they can not accidently be altered.
