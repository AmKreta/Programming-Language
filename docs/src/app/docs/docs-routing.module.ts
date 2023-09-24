import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { DocsComponent } from './pages/docs/docs.component';

const routes: Routes = [
  {
    path: '',
    component: DocsComponent,
  },
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
})
export class DocsRoutingModule {}
