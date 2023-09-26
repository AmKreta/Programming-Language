import { Component } from '@angular/core';

interface Topic {
  title: string;
  routerLink: string;
};
@Component({
  selector: 'app-docs',
  templateUrl: './docs.component.html',
  styleUrls: ['./docs.component.scss']
})
export class DocsComponent {
  topics: Topic[] = [
    {
      title: 'Print',
      routerLink: './print'
    },
    {
      title: 'Variables',
      routerLink: './variables'
    },
    {
      title: 'Operators',
      routerLink: './operators'
    },
    {
      title: 'Data Types',
      routerLink: './data-types'
    },
    {
      title: 'Function',
      routerLink: './functions'
    },
    {
      title: 'Class',
      routerLink: './class'
    },
    {
      title: 'In-built Classes and Functions',
      routerLink: './inbuilt-classes-functions'
    },
    {
      title:'Behind the scene',
      routerLink:'./behind-the-scene'
    }
  ]
}
