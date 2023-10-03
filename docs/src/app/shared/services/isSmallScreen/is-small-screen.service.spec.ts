import { TestBed } from '@angular/core/testing';

import { IsSmallScreenService } from './is-small-screen.service';

describe('IsSmallScreenService', () => {
  let service: IsSmallScreenService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(IsSmallScreenService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
