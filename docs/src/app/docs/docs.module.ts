import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { DocsComponent } from './pages/docs/docs.component';
import { DocsRoutingModule } from './docs-routing.module';

@NgModule({
  declarations: [DocsComponent],
  imports: [DocsRoutingModule, CommonModule],
})
export class DocsModule {}
