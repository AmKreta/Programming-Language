import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DataTypesComponent } from './data-types.component';

describe('DataTypesComponent', () => {
  let component: DataTypesComponent;
  let fixture: ComponentFixture<DataTypesComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [DataTypesComponent]
    });
    fixture = TestBed.createComponent(DataTypesComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
