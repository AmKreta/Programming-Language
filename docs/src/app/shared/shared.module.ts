import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { TypographyComponent } from './components/typography/typography.component';
import { CodeHighlightService } from './services/code-highlight/code-highlight.service';
import { CodeSnippetComponent } from './components/code-snippet/code-snippet.component';



@NgModule({
  declarations: [
    TypographyComponent,
    CodeSnippetComponent,
  ],
  imports: [
    CommonModule
  ],
  exports: [
    TypographyComponent,
    CodeSnippetComponent,
  ],
  providers: [
    CodeHighlightService,
  ]
})
export class SharedModule { }
