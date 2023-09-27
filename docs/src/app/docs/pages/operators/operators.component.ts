import { Component } from '@angular/core';
import { BinaryOperatorExamples, TernaryOperatorExamplex, UnaryOperatorExamples } from './examples';

@Component({
  selector: 'app-operators',
  templateUrl: './operators.component.html',
  styleUrls: ['./operators.component.scss']
})
export class OperatorsComponent {
  unaryOperatorExamples = UnaryOperatorExamples;
  binaryOperatorExamples = BinaryOperatorExamples;
  ternaryOperatorExamples = TernaryOperatorExamplex;
}
