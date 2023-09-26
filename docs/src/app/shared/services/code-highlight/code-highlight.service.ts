import { Injectable, Inject } from '@angular/core'; 
import { PLATFORM_ID } from '@angular/core';
import { isPlatformBrowser } from '@angular/common';

import 'prismjs';
import 'prismjs/plugins/toolbar/prism-toolbar';
import 'prismjs/plugins/copy-to-clipboard/prism-copy-to-clipboard';
import 'prismjs/components/prism-css';
import 'prismjs/components/prism-javascript';
import 'prismjs/components/prism-java';
import 'prismjs/components/prism-markup';
import 'prismjs/components/prism-typescript';
import 'prismjs/components/prism-sass';
import 'prismjs/components/prism-scss';

declare var Prism: any;

@Injectable({
  providedIn: 'root'
})
export class CodeHighlightService {
  constructor(@Inject(PLATFORM_ID) private platformId: Object) { 
    console.log(Prism);
  }

  highlightAll() {
    if (isPlatformBrowser(this.platformId)) {
      console.log(Prism);
      Prism.highlightAll();
    }
  }
}
