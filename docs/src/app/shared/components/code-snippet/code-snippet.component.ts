import { AfterViewChecked, Component, Input } from '@angular/core';
import { CodeHighlightService } from '@shared/services/code-highlight/code-highlight.service';

@Component({
  selector: 'app-code-snippet',
  templateUrl: './code-snippet.component.html',
  styleUrls: ['./code-snippet.component.scss']
})
export class CodeSnippetComponent implements AfterViewChecked {
  @Input() title = '';
  @Input({ required: true }) codeSnippet = '';
  @Input() description = '';
  @Input() explaination = '';

  public highlighted = false;

  constructor(private codeHighlight: CodeHighlightService) { }

  ngAfterViewChecked() {
    if (!this.highlighted) {
      this.codeHighlight.highlightAll()
      this.highlighted = true
    }
  }
}
