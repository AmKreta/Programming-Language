import { ComponentFixture, TestBed } from '@angular/core/testing';

import { LoopsComponent } from './loops.component';

describe('LoopsComponent', () => {
  let component: LoopsComponent;
  let fixture: ComponentFixture<LoopsComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [LoopsComponent]
    });
    fixture = TestBed.createComponent(LoopsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
