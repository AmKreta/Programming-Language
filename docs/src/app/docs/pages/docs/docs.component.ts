import { Component, OnInit, TemplateRef, ViewChild } from '@angular/core';
import { NavigationEnd, Router } from '@angular/router';
import withDestory from '@shared/util/withDestory';
import { takeUntil } from 'rxjs';

interface Topic {
  title: string;
  routerLink: string;
};
@Component({
  selector: 'app-docs',
  templateUrl: './docs.component.html',
  styleUrls: ['./docs.component.scss']
})
export class DocsComponent extends withDestory() implements OnInit {
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
      title:'Conditional Statement',
      routerLink:'conditional-statement'
    },
    {
      title:'Loops',
      routerLink:'loops'
    },
    {
      title:'Scope',
      routerLink:'scope'
    },
    {
      title: 'Function',
      routerLink: './functions'
    },
    {
      title: 'Class',
      routerLink: './class'
    },
    // {
    //   title: 'In-built Classes and Functions',
    //   routerLink: './inbuilt-classes-functions'
    // },
    // {
    //   title: 'Behind the scene',
    //   routerLink: './behind-the-scene'
    // }
  ];

  @ViewChild('outletContainer') outletContainer!: TemplateRef<any>;

  constructor(public router: Router) {
    super();
    this.router.events.pipe(takeUntil(this.destroy$)).subscribe(ev => {
      if (ev instanceof NavigationEnd) {
        (this.outletContainer?.elementRef?.nativeElement as HTMLDivElement)?.scrollTo({ top: 0, behavior: 'smooth' });
      }
    });
  }

  ngOnInit() {
    if (this.router.url === "/docs")
      this.router.navigate(["./docs/print"]);
  }
}
