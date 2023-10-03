import { Component, OnDestroy, OnInit } from '@angular/core';
import withDestory from '@shared/util/withDestory';
import { fromEvent, interval, takeUntil, throttle } from 'rxjs';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent extends withDestory() implements OnInit {
  title = 'docs';

  navBarList: {
    icon: string,
    title: string,
    routerLink: string
  }[] = [
      { icon: 'insert_drive_file', title: 'Docs', routerLink: '/docs' },
      { icon: 'code', title: 'Playground', routerLink: '/playground' }
    ]

  showFooter = false;

  setShowFooter = () => {
    this.showFooter = window.innerWidth < 800;
  }

  checkIfSmallScreen(){
    this.showFooter = window.innerWidth < 800;
  }

  ngOnInit() {
    this.checkIfSmallScreen();
    
    fromEvent(window, 'resize')
      .pipe(
        takeUntil(this.destroy$),
        throttle(() => interval(500))
      )
      .subscribe(this.checkIfSmallScreen)
  }
}
