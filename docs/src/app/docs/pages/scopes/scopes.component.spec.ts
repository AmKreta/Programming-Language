import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ScopesComponent } from './scopes.component';

describe('ScopesComponent', () => {
  let component: ScopesComponent;
  let fixture: ComponentFixture<ScopesComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [ScopesComponent]
    });
    fixture = TestBed.createComponent(ScopesComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
