import { NgModule } from '@angular/core';
import {RouterModule, Routes} from '@angular/router';
import { AboutMeComponent } from './pages/about-me/about-me.component';

const routes:Routes = [
    {
        path:'',
        component:AboutMeComponent
    }
];

@NgModule({
    imports:[RouterModule.forChild(routes)]
})
export class AboutMeRoutingModule{}