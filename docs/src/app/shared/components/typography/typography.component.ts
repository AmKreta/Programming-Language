import { Component, Input } from '@angular/core';


const Colors = {
  primary: 'primary',
  accent: 'accent',
  warn: 'warn'
};

const Variants = {
  headline1: 'mat-headline-1',
  headline2: 'mat-headline-2',
  headline3: 'mat-headline-3',
  headline4: 'mat-headline-4',
  headline5: 'mat-headline-5',
  headline6: 'mat-headline-6',
  subtitle1: 'mat-subtitle-1',
  subtitle2: 'mat-subtitle-2',
  body1: 'mat-body-1',
  body2: 'mat-body-2',
  caption: 'mat-caption',
  h5: 'mat-h5',
  h6: 'mat-h6'
};


@Component({
  selector: 'app-typography',
  templateUrl: './typography.component.html',
  styleUrls: ['./typography.component.scss']
})
export class TypographyComponent {
  @Input() variant: keyof typeof Variants = 'body1';
  @Input() color: keyof typeof Colors | undefined;
  @Input() colorShade: `${number}00` | number = 500;
  @Input() style: { [key: string]: string } = {};

  public get className() {
    let res = `${Variants[this.variant]}`;
    if (this.color)
      res += ` text-${this.color}-${this.colorShade}`;
    return res;
  }
}
