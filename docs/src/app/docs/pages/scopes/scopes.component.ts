import { Component } from '@angular/core';
import { ScopesTypes } from './definationList';

@Component({
  selector: 'app-scopes',
  templateUrl: './scopes.component.html',
  styleUrls: ['./scopes.component.scss']
})
export class ScopesComponent {
  scopesTypes = ScopesTypes;

  scopeExamples = [
    {
      codeSnippet: `
let globalVar = "I'm global";

function outerFunction() {
    let outerVar = "I'm in outerFunction";
          
    function innerFunction() {
        let innerVar = "I'm in innerFunction";
        let globalVar = "I'm a local var Shadowing global var";
        printLn(innerVar); // Accesses the inner variable
        printLn(outerVar); // Accesses the outer variable
        printLn(globalVar); // Accesses the locally defined globalVar
    }
      
    innerFunction();
          
    //printLn(innerVar); //Error: innerVar is not defined here
    printLn(outerVar); // Accesses the outer variable
    printLn(globalVar); // Accesses the global variable
}
      
outerFunction();`,
      description: "In this example, you can see how variables are scoped within functions and how shadowing works. The innerVar is accessible only within innerFunction, and when it's not found there, the outer scopes are checked. The outerVar is accessible within outerFunction, and the globalVar is accessible globally."
    }
  ];
}
