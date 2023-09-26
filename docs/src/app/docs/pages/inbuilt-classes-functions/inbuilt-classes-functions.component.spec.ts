import { ComponentFixture, TestBed } from '@angular/core/testing';

import { InbuiltClassesFunctionsComponent } from './inbuilt-classes-functions.component';

describe('InbuiltClassesFunctionsComponent', () => {
  let component: InbuiltClassesFunctionsComponent;
  let fixture: ComponentFixture<InbuiltClassesFunctionsComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [InbuiltClassesFunctionsComponent]
    });
    fixture = TestBed.createComponent(InbuiltClassesFunctionsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
