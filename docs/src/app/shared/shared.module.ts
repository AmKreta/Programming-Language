import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { TypographyComponent } from './components/typography/typography.component';
import { CodeHighlightService } from './services/code-highlight/code-highlight.service';
import { CodeSnippetComponent } from './components/code-snippet/code-snippet.component';
import { SwipeDirective } from './directives/swipe/swipe.directive';



@NgModule({
  declarations: [
    TypographyComponent,
    CodeSnippetComponent,
    SwipeDirective,
  ],
  imports: [
    CommonModule
  ],
  exports: [
    TypographyComponent,
    CodeSnippetComponent,
    SwipeDirective
  ],
  providers: [
    CodeHighlightService,
  ]
})
export class SharedModule { }
