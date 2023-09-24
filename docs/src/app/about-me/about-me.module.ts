import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { AboutMeComponent } from './pages/about-me/about-me.component';
import { AboutMeRoutingModule } from './about-me-routing.module';



@NgModule({
  declarations: [
    AboutMeComponent
  ],
  imports: [
    AboutMeRoutingModule,
    CommonModule
  ]
})
export class AboutMeModule { }
