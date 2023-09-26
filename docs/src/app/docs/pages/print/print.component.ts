import { Component } from '@angular/core';
import { CodeHighlightService } from '@shared/services/code-highlight/code-highlight.service';
import {PrintExamples, PrintLnExamples} from './examples';
@Component({
  selector: 'app-print',
  templateUrl: './print.component.html',
  styleUrls: ['./print.component.scss']
})
export class PrintComponent {
  public printExamples = PrintExamples;
  public printLnExamples = PrintLnExamples;
  public highlighted = false;

  constructor(private codeHighlight:CodeHighlightService){}

  ngAfterViewChecked() {
    if (!this.highlighted) {
      this.codeHighlight.highlightAll()
      this.highlighted = true
    }
  }
}