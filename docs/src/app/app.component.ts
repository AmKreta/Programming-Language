import { Component, OnInit } from '@angular/core';
import { DocsSidebarService } from '@shared/services/docs-sidebar/docs-sidebar.service';
import { IsSmallScreenService } from '@shared/services/isSmallScreen/is-small-screen.service';
import withDestory from '@shared/util/withDestory';
import { takeUntil} from 'rxjs';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent extends withDestory() implements OnInit {
  title = 'docs';

  navBarList: {
    icon: string,
    title: string,
    routerLink: string
  }[] = [
      { icon: 'insert_drive_file', title: 'Docs', routerLink: '/docs' },
      { icon: 'code', title: 'Playground', routerLink: '/playground' }
    ]

  isSmallScreen = false;

  constructor(
    private isSmallScreenService:IsSmallScreenService,
    public docSidebarService:DocsSidebarService
  ){
    super();
  }

  ngOnInit() {
    this
    .isSmallScreenService
    .isSmallScreen$
    .pipe(takeUntil(this.destroy$))
    .subscribe(res=>{
      this.isSmallScreen = res
    });
  }
}
