const PrintExamples = [
    {
        title: 'Printing a String',
        codeSnippet: `
// Example 1: Printing a String
print("Hello World"); 
// Output: 'Hello World'`,
        description: ' In this example, we use the print function to display a string.'
    },
    {
        title: 'Printing an Expression',
        codeSnippet: `
// Example 2: Printing an Expression
print(1 + 1); 
// Output: '2'`,
        description: 'Here, the print function outputs the result of an arithmetic expression'
    },
    {
        title: 'Printing an Array',
        codeSnippet: `
// Example 3: Printing an Array
print([1, 2, 3, 4, "Five"]); 
// Output: '[1, 2, 3, 4, 'Five']'`,
        description: 'This example demonstrates how to use print with an array containing mixed data types, including strings and numbers.'
    },
    {
        title: 'Printing an Object',
        codeSnippet: `
// Example 4: Printing an Object
print({'array': [1, 2, 3]}); 
// Output: "{'array': [1, 2, 3]}"`,
        description: 'The print function is capable of displaying the content of JavaScript objects.'
    },
    {
        title: 'Printing a Class Instance',
        codeSnippet: `
// Example 5: Printing a Class Instance
class cls {
    function constructor() {
    this.a = 5;
    this.b = 6;
    }
};
    
let x = new cls();  
print(x); 

// Output: "{'a': 5, 'b': 6}"`,
        description: 'This example showcases the use of print with a class instance.'
    },
];

const PrintLnExamples = [
    {
        title: 'Using printLn Function',
        codeSnippet: `
// Using the "print" function
print("Hello, "); // Output: Hello, World!
print("World!");

// Using the "printLn" function
printLn("Hello, "); // Output: Hello,
printLn("World!");    //        World!`,
        description: 'In the example above, "print" prints both "Hello, " and "World!" on the same line, while "printLn" separates them onto different lines for a cleaner presentation.',
        explaination: 'The "print" function is commonly used to display content without adding line breaks, which means that subsequent output continues on the same line. On the other hand, "printLn" achieves the same output but automatically inserts an end-of-line character, resulting in a new line for each call.'
    }
]

export { PrintExamples, PrintLnExamples };