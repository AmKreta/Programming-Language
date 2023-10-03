export default [
    {
        title: 'length()',
        codeSnippet: `
let text = "Hello, World!";
let length = text.length(); 
print(length);// 13`,
        description: 'Returns the length (number of characters) of a string.'
    },
    {
        title: 'slice(start, end)',
        codeSnippet: `
let text = "Hello, World!";
let slicedText = text.slice(0, 5); 
print(slicedText); // "Hello"`,
        description: 'Extracts a portion of the string and returns it as a new string. The start index is inclusive, and the end index is exclusive.'
    },
    {
        title: 'reverse()',
        codeSnippet: `
let text = "Hello, World!";
let reversedText = text.reverse();
print(reversedText); //"!dlroW ,olleH"`,
        description: 'Reverses the order of characters in a string and returns a new string.'
    },
    {
        title: 'split(separator)',
        codeSnippet: `
let text = "apple,banana,cherry";
let fruits = text.split(",");
print(fruits); // ["apple", "banana", "cherry"]`,
        description: 'Splits a string into an array of substrings based on a specified separator.'
    },
    {
        title: 'includes(substring)',
        codeSnippet: `
let text = "Hello, World!";
let containsWorld = text.includes("World");
print(containsWorld); // true`,
        description: 'Checks if a string contains the specified substring and returns a boolean.'
    },
    {
        title: 'replace(oldSubstring, newSubstring)',
        codeSnippet: `
let text = "Hello, World!";
let newText = text.replace("World", "Universe"); 
print(newText);// "Hello, Universe!"`,
        description: 'Replaces occurrences of oldSubstring with newSubstring in a string and returns a new string.'
    },
    {
        title: 'replaceAll(oldSubstring, newSubstring)',
        codeSnippet: `
let text = "Hello, World! Hello, Universe!";
let newText = text.replaceAll("Hello", "Hi"); 
print(newText);// "Hi, World! Hi, Universe!"`,
        description: 'Replaces all occurrences of oldSubstring with newSubstring in a string and returns a new string. (Available in modern JavaScript environments)'
    },
    {
        title: 'findIndex(callbackFn)',
        codeSnippet: `
let text = "Hello, World! Hello, Universe!";
const index = text.findIndex("World");
print(index);// index is 7`,
        description: 'Returns the index of the first element in the array that satisfies the provided testing function.'
    },
];