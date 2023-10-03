import { Injectable } from '@angular/core';
import { NavigationEnd, Router } from '@angular/router';
import { BehaviorSubject } from 'rxjs';
import { IsSmallScreenService } from '../isSmallScreen/is-small-screen.service';

@Injectable({
  providedIn: 'root'
})
export class DocsSidebarService {

  showHambuggerMenu$ = new BehaviorSubject<boolean>(false);
  showDocsMenu = false;

  constructor(
    private router: Router,
    private isSmallScreenService:IsSmallScreenService
  ) {
    this.router.events.subscribe(ev => {
      if (ev instanceof NavigationEnd)
        this.showHambuggerMenu$.next(ev.url.includes("/docs"));
    });
    this.isSmallScreenService.isSmallScreen$.subscribe(res=>{
      if(!res)
        this.showDocsMenu = true;
    })
  }

  toggleDocsMenu() {
      this.showDocsMenu = !this.showDocsMenu;
  }
}
