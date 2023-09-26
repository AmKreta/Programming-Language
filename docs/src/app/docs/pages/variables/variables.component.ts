import { Component } from '@angular/core';
import { ConstExample, DataTypesDeclerationExample, LetExample } from './examples';

@Component({
  selector: 'app-variables',
  templateUrl: './variables.component.html',
  styleUrls: ['./variables.component.scss']
})
export class VariablesComponent {
  letExample = LetExample;
  constExample = ConstExample;
  dataTypesDeclerationExample = DataTypesDeclerationExample;
}
