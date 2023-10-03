import { Component } from '@angular/core';
import stringExamples from './stringExamples';

@Component({
  selector: 'app-string',
  templateUrl: './string.component.html',
  styleUrls: ['./string.component.scss']
})
export class StringComponent {
  stringDeclExample = `
let singleQuotes = 'Hello, World!';
let doubleQuotes = "Token programming language is fun!";
printLn(singleQuotes);
printLn(doubleQuotes);`;

stringExamples = stringExamples;
}
