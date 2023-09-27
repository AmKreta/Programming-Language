import { Component } from '@angular/core';

@Component({
  selector: 'app-function',
  templateUrl: './function.component.html',
  styleUrls: ['./function.component.scss']
})
export class FunctionComponent {

  functionDeclerationExample = `
  function greet() {
    print('Hello World');
  }`;

  functionExpressionExample = `
  let greet = function () {
    print('Hello World');
  }`;

  functionCallExample = `
  function greet() {
    print('Hello World');
  }
  greet(); // prints hello world`;

  functionParametersExample = `
  function add(a, b) { // here a and b are parameters
    let res = a+b;
    print(res);
  }`;

  functionArgumentExample = `
  function add(a, b) {
    let res = a+b;
    print(res);
  }
  add(3, 4); // here 3 and 4 are parameters`;

  functionDefaultParamsExample = `
  function add(a = 5, b = 6) { // default value for 'a' is 5 
    let res = a+b;             // default value for 'b' is 6
    print(res);                // value for 'a' is provided so 'a' becomes 3
  }                            // no value provided for 'b' so 'b' takes default value and becomes 6
  add(3); // prints 9`;

  functionAsFirstClassCitizenExample = `
// Function Declaration
function add(a, b) {
  return a + b;
}

// Function Expression (assigned to a variable)
const subtract = function (a, b) {
  return a - b;
};

// Function as an argument to another function
function performOperation(operation, x, y) {
  return operation(x, y);
}

// Using the functions

const result1 = performOperation(add, 7, 2); // Passing add as an argument
console.log("Result of performing addition:", result1);

const result2 = performOperation(subtract, 15, 6); // Passing subtract as an argument
console.log("Result of performing subtraction:", result2);`;

  functionClosureExample = `
function createCounter() {
  let count = 0;
  return function () {
    return ++count;
  };
}

const counter = createCounter();
console.log(counter()); // 1 , count is still accessible
console.log(counter()); // 2 , count is still accessible
`;
}
