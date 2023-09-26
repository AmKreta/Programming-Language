import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { TypographyComponent } from './components/typography/typography.component';
import { CodeHighlightService } from './services/code-highlight/code-highlight.service';



@NgModule({
  declarations: [
    TypographyComponent,
  ],
  imports: [
    CommonModule
  ],
  exports: [
    TypographyComponent
  ],
  providers: [
    CodeHighlightService
  ]
})
export class SharedModule { }
