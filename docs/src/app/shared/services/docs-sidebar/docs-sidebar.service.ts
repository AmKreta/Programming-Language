import { Injectable } from '@angular/core';
import { NavigationEnd, Router } from '@angular/router';
import { BehaviorSubject } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class DocsSidebarService {

  showHambuggerMenu$ = new BehaviorSubject<boolean>(false);
  showDocsMenu = false;

  constructor(public router: Router) {
    this.router.events.subscribe(ev => {
      if (ev instanceof NavigationEnd)
        this.showHambuggerMenu$.next(ev.url.includes("/docs"));
    });
  }

  toggleDocsMenu() {
    this.showDocsMenu = !this.showDocsMenu;
  }
}
