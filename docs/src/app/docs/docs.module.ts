import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { DocsComponent } from './pages/docs/docs.component';
import { DocsRoutingModule } from './docs-routing.module';
import { MatSidenavModule } from '@angular/material/sidenav';
import { MatListModule } from '@angular/material/list';
import { PrintComponent } from './pages/print/print.component';
import { VariablesComponent } from './pages/variables/variables.component';
import { OperatorsComponent } from './pages/operators/operators.component';
import { FunctionComponent } from './pages/function/function.component';
import { ClassComponent } from './pages/class/class.component';
import { InbuiltClassesFunctionsComponent } from './pages/inbuilt-classes-functions/inbuilt-classes-functions.component';
import { BehindTheSceneComponent } from './pages/behind-the-scene/behind-the-scene.component';
import { SharedModule } from '../shared/shared.module';

@NgModule({
  declarations: [DocsComponent, PrintComponent, VariablesComponent, OperatorsComponent, FunctionComponent, ClassComponent, InbuiltClassesFunctionsComponent, BehindTheSceneComponent],
  imports: [DocsRoutingModule, CommonModule, MatSidenavModule, MatListModule, SharedModule],
})
export class DocsModule { }
