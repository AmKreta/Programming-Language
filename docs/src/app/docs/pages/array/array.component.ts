import { Component } from '@angular/core';
import ArrayExample from './array.example';

@Component({
  selector: 'app-array',
  templateUrl: './array.component.html',
  styleUrls: ['./array.component.scss']
})
export class ArrayComponent {
  arrayDeclExample=`
  let fruits = ["apple", "banana", "cherry"];`;
  arrayExamples = ArrayExample;
}
