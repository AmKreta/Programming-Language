import { Component } from '@angular/core';

@Component({
  selector: 'app-class',
  templateUrl: './class.component.html',
  styleUrls: ['./class.component.scss']
})
export class ClassComponent {
  classExample=`
// Define a JavaScript class called 'Person'
class Person {
  // Constructor to initialize properties
  function constructor(firstName, lastName) {
    this.firstName = firstName;
    this.lastName = lastName;
  }
  
  // Method to get the full name
  function getFullName() {
    return this.firstName + ' ' + this.lastName;
  }
};
  
// Create an instance of the 'Person' class using the 'new' keyword
const person1 = new Person('John', 'Doe');
  
// Access properties and call methods of the object
print(person1.firstName); // Output: "John"
print(person1.lastName);  // Output: "Doe"
print(person1.getFullName()); // Output: "John Doe"`
}
