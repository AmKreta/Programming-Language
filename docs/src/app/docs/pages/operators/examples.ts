export const UnaryOperatorExamples = [
    {
        title: 'Mathematical Operators + and -',
        codeSnippet: `
let x = +"5";  // Converts '5' to a number (unary plus)
let y = -10;   // Negates the value 10 (unary minus)
print(x,', ', y);`,
        description: 'The + operator is used to convert an operand into a number, the - operator is used for negation or to convert an operand into a negative number.'
    },
    {
        title: 'Bitwise Operator ~',
        codeSnippet: `
let num = 5;    // Binary representation: 00000101
let result = ~num; // Binary representation: 11111010 (inverts bits)
print(result);`,
        description: 'The ~ operator performs a bitwise NOT operation, inverting the bits of an integer.'
    },
    {
        title: 'Logical Operator !',
        codeSnippet: `
let isTrue = true;
let isFalse = !isTrue; // isFalse is now false
print(isFalse);`,
        description: 'The ! operator is used for logical NOT. It negates a Boolean value, turning true into false and vice versa.'
    }
];

export const BinaryOperatorExamples = [
    {
        title: 'Mathematical Operators +, -, /, *, **, %',
        codeSnippet: `
let a = 5 + 3;     // Addition
let b = 10 - 4;    // Subtraction
let c = 6 * 2;     // Multiplication
let d = 8 / 4;     // Division
let e = 2 ** 3;    // Exponentiation (2 to the power of 3)
let f = 15 % 4;    // Modulus (remainder of 15 divided by 4)
print({"a":a, "b":b, "c":c, "d":d, "e":e, "f":f});`,
        description: 'These operators perform basic arithmetic operations on numbers.'
    },
    {
        title: 'Bitwise Operators &, |, <<, >>, ^',
        codeSnippet: `
let num1 = 5;        // Binary: 00000101
let num2 = 3;        // Binary: 00000011   

let result1 = num1 & num2; // Bitwise AND: 00000001
let result2 = num1 | num2; // Bitwise OR: 00000111
let result3 = num1 << 2;   // Left shift by 2 bits: 00010100
let result4 = num1 >> 1;   // Right shift by 1 bit: 00000010
let result5 = num1 ^ num2; // Bitwise XOR: 00000110
printLn({"num1":num1, "num2":num2});
printLn({
    "result1":result1, 
    "result2":result2, 
    "result3":result3, 
    "result4":result4, 
    "result5":result5
});`,
        description: 'These operators perform bitwise operations on integers.'
    },
    {
        title: 'Logical Operators && and ||',
        codeSnippet: `
let isTrue = true;
let isFalse = false;

let result1 = isTrue && isFalse; // Logical AND: false
let result2 = isTrue || isFalse; // Logical OR: true
print(result1,', ', result2);`,
        description: 'These operators are used for logical AND and logical OR operations on Boolean values.'
    },
    {
        title: 'Relational Operators <, >, <=, >=, !=, ==',
        codeSnippet: `
let a = 5;
let b = 3;
        
let isLess = a < b;   // Is a less than b? (false)
let isGreater = a > b; // Is a greater than b? (true)
let isEqual = a == b; // Is a equal to b? (false)
print({
    "isLess":isLess,
    "isGreater":isGreater,
    "isEqual":isEqual
});`,
        description: 'These operators compare values and return Boolean results.'
    },
    {
        title: 'Assignment Operator =',
        codeSnippet: `let x = 10; // Assigns the value 10 to the variable x`,
        description: 'The = operator is used to assign a value to a variable.'
    },
];

export const TernaryOperatorExamplex = [
    {
        title: 'Conditional Operator',
        codeSnippet: `
let age = 20;
let isAdult = age >= 18 ? "Yes" : "No"; // If age is 18 or older, isAdult is "Yes", otherwise "No"
print(isAdult);`,
        description: 'The conditional operator (? :) is a conditional operator that evaluates a condition and returns one of two values depending on whether the condition is true or false.'
    },
];