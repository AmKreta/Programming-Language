import { AfterViewInit, Directive, ElementRef, EventEmitter, OnDestroy, Output } from '@angular/core';

@Directive({
  selector: '[appSwipe]'
})
export class SwipeDirective implements AfterViewInit, OnDestroy {


  public x: null | number = null;
  public y: null | number = null;

  @Output() onSwipeLeft = new EventEmitter<TouchEvent>();
  @Output() onSwipeRight = new EventEmitter<TouchEvent>();
  @Output() onSwipeUp = new EventEmitter<TouchEvent>();
  @Output() onSwipeDown = new EventEmitter<TouchEvent>();

  constructor(private elementRef: ElementRef) { }

  ngAfterViewInit(): void {
    let el = this.elementRef.nativeElement as HTMLElement;
    el.addEventListener('touchstart', this.handleTouchStart, false);
    el.addEventListener('touchmove', this.handleTouchMove as any, false);
  }

  static getTouches(evt: TouchEvent) {
    return evt.touches      // browser API

  }

  handleTouchStart = (evt: TouchEvent)=>{
    const firstTouch = SwipeDirective.getTouches(evt)[0];
    this.x = firstTouch.clientX;
    this.y = firstTouch.clientY;
  }

  handleTouchMove = (evt: TouchEvent)=>{
    if (!this.x || !this.y) {
      return;
    }

    var xUp = evt.touches[0].clientX;
    var yUp = evt.touches[0].clientY;

    var xDiff = this.x - xUp;
    var yDiff = this.y - yUp;

    if (Math.abs(xDiff) > Math.abs(yDiff)) {/*most significant*/
      xDiff > 0
        ? this.onSwipeLeft.emit(evt)
        : this.onSwipeRight.emit(evt);
    } else {
      yDiff > 0
        ? this.onSwipeDown.emit(evt)
        : this.onSwipeUp.emit(evt);
    }
    /* reset values */
    this.x = null;
    this.y = null;
  };

  ngOnDestroy(): void {
    let el = this.elementRef.nativeElement as HTMLElement;
    el.removeEventListener('touchstart', this.handleTouchStart);
    el.removeEventListener('touchend', this.handleTouchMove as any);
  }
}
