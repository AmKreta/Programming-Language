import { Injectable } from '@angular/core';
import { BehaviorSubject, fromEvent, interval, takeUntil, throttle } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class IsSmallScreenService {

  isSmallScreen$ = new BehaviorSubject<boolean>(false);

  checkIfSmallScreen = () => {
    this.isSmallScreen$.next(window.innerWidth < 800);
  }

  constructor() {
    this.checkIfSmallScreen();
    fromEvent(window, 'resize')
      .pipe(throttle(() => interval(500)))
      .subscribe(this.checkIfSmallScreen)
  }

};
