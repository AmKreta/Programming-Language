import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent {
  title = 'docs';

  navBarList:{
    icon:string, 
    title: string,
    routerLink:string
  }[]=[
    {icon:'insert_drive_file', title:'Docs', routerLink:'/docs'},
    {icon:'code', title:'Playground', routerLink:'/playground'}
  ]
}
