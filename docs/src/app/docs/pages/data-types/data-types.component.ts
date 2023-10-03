import { Component } from '@angular/core';

@Component({
  selector: 'app-data-types',
  templateUrl: './data-types.component.html',
  styleUrls: ['./data-types.component.scss']
})
export class DataTypesComponent {
  numberExample = {
    codeSnippet: `
let age = 25;            // Integer
let pi = 3.14159;        // Floating-point number`
  };

  stringExample = {
    codeSnippet: `
name = "Amresh";
message = 'Hello, ' + name;`
  };

  mapExample = {
    codeSnippet: `
let person = {
  'name': "Amk",
  'age': 25,
};
print(person['name']);  // Accessing value using a key`
  };

  arrayExample = {
    codeSnippet: `
fruits = ["apple", "banana", "cherry", 1, 2, {"foo" : 'bar'}, ["nested aray"]]
print(fruits[0])  # Accessing the first element`
  }

  customDataTypeExample = {
    codeSnippet: `
class Cls{
  function constructor(){
    this.a = 5;
        this.b = 6;
  }
};
let cls = new Cls();
print(cls); // Cls {'a':5, 'b':6}`
  }
}
