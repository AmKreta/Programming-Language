import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { DocsComponent } from './pages/docs/docs.component';
import { PrintComponent } from './pages/print/print.component';
import { VariablesComponent } from './pages/variables/variables.component';
import { OperatorsComponent } from './pages/operators/operators.component';
import { FunctionComponent } from './pages/function/function.component';
import { ClassComponent } from './pages/class/class.component';
import { InbuiltClassesFunctionsComponent } from './pages/inbuilt-classes-functions/inbuilt-classes-functions.component';
import { BehindTheSceneComponent } from './pages/behind-the-scene/behind-the-scene.component';
import { LoopsComponent } from './pages/loops/loops.component';
import { DataTypesComponent } from './pages/data-types/data-types.component';
import { ConditionalStatementComponent } from './pages/conditional-statement/conditional-statement.component';
import { ScopesComponent } from './pages/scopes/scopes.component';

const routes: Routes = [
  {
    path: '',
    component: DocsComponent,
    children: [
      {
        title: 'Print',
        path: 'print',
        component: PrintComponent
      },
      {
        title: 'Variables',
        path: 'variables',
        component: VariablesComponent
      },
      {
        title: 'Operators',
        path: 'operators',
        component: OperatorsComponent
      },
      {
        title: 'Data Types',
        path: 'data-types',
        component: DataTypesComponent
      },
      {
        title: 'Loops',
        path: 'loops',
        component: LoopsComponent
      },
      {
        title: 'Function',
        path: 'functions',
        component: FunctionComponent
      },
      {
        title: 'Class',
        path: 'class',
        component: ClassComponent
      },
      {
        title: 'In-built Classes and Functions',
        path: 'inbuilt-classes-functions',
        component: InbuiltClassesFunctionsComponent
      },
      {
        title: 'Behind the scene',
        path: 'behind-the-scene',
        component: BehindTheSceneComponent
      },
      {
        title: 'Conditional Statement',
        path: 'conditional-statement',
        component: ConditionalStatementComponent
      },
      {
        title: 'Loops',
        path: 'loops',
        component: LoopsComponent
      },
      {
        title: 'Scopes',
        path: 'scope',
        component: ScopesComponent
      }
    ]
  },
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class DocsRoutingModule { }
