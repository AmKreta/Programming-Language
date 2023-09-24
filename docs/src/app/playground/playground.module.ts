import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { PlaygroundComponent } from './pages/playground/playground.component';
import { PlaygroundRoutingModule } from './playGround-routing.module';



@NgModule({
  declarations: [
    PlaygroundComponent
  ],
  imports: [
    CommonModule,
    PlaygroundRoutingModule
  ]
})
export class PlaygroundModule { }
