import { Component } from '@angular/core';
import { ConditionalOperatorExamples, IfElseExamples } from './examples';

@Component({
  selector: 'app-conditional-statement',
  templateUrl: './conditional-statement.component.html',
  styleUrls: ['./conditional-statement.component.scss']
})
export class ConditionalStatementComponent {
  ifElseExamples = IfElseExamples;
  conditionalOpExamples = ConditionalOperatorExamples;
}
