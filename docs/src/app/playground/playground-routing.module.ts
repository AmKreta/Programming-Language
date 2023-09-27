import { NgModule } from "@angular/core";
import { RouterModule, Routes } from "@angular/router";
import { PlaygroundComponent } from "./pages/playground/playground.component";

const routes:Routes = [
    {
        path:'',
        component:PlaygroundComponent
    }
];

@NgModule({
    imports:[RouterModule.forChild(routes)]
})
export class PlaygroundRoutingModule{};