import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ArrayComponent } from './array.component';

describe('ArrayComponent', () => {
  let component: ArrayComponent;
  let fixture: ComponentFixture<ArrayComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [ArrayComponent]
    });
    fixture = TestBed.createComponent(ArrayComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
