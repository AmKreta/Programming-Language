import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { PlaygroundComponent } from './pages/playground/playground.component';
import { PlaygroundRoutingModule } from './playground-routing.module';
import { CodeEditorModule } from '@ngstack/code-editor';
import { MatButtonModule } from '@angular/material/button';
import { SharedModule } from '@shared/shared.module';



@NgModule({
  declarations: [
    PlaygroundComponent
  ],
  imports: [
    CommonModule,
    PlaygroundRoutingModule,
    CodeEditorModule.forChild(),
    MatButtonModule,
    SharedModule
  ]
})
export class PlaygroundModule { }
