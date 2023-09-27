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
import { DataTypesComponent } from './pages/data-types/data-types.component';
import { ConditionalStatementComponent } from './pages/conditional-statement/conditional-statement.component';
import { LoopsComponent } from './pages/loops/loops.component';
import { ScopesComponent } from './pages/scopes/scopes.component';

@NgModule({
  declarations: [DocsComponent, DataTypesComponent, PrintComponent, VariablesComponent, OperatorsComponent, FunctionComponent, ClassComponent, InbuiltClassesFunctionsComponent, BehindTheSceneComponent, ConditionalStatementComponent, LoopsComponent, ScopesComponent],
  imports: [DocsRoutingModule, CommonModule, MatSidenavModule, MatListModule, SharedModule],
})
export class DocsModule { }
