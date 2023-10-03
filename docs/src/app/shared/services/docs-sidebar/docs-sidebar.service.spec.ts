import { TestBed } from '@angular/core/testing';

import { DocsSidebarService } from './docs-sidebar.service';

describe('DocsSidebarService', () => {
  let service: DocsSidebarService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(DocsSidebarService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
