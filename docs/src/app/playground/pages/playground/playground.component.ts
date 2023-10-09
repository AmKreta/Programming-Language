import { Component, OnDestroy, OnInit } from '@angular/core';
import { CodeModel } from '@ngstack/code-editor';
import { Subject, takeUntil} from 'rxjs';
import withDestory from '@shared/util/withDestory';
import { IsSmallScreenService } from '@shared/services/isSmallScreen/is-small-screen.service';

// wasm Module

type Log = { isLog: boolean, text: string };
let logger$: Subject<Log> | null = null;

console.log = ((originalConsoleLog: Function) => {
  return (...args: any[]) => {
    let textContent = Array.prototype.slice.call(args).join(' ');
    originalConsoleLog(textContent);
    if (textContent.startsWith('Exception:'))
      logger$?.next({ isLog: false, text: textContent });
    else
      logger$?.next({ isLog: true, text: textContent });
  }
})(console.log.bind(console));

@Component({
  selector: 'app-playground',
  templateUrl: './playground.component.html',
  styleUrls: ['./playground.component.scss']
})
export class PlaygroundComponent extends withDestory() implements OnInit, OnDestroy {
  theme = 'vs-dark';

  codeModel: CodeModel = {
    language: 'Token',
    uri: 'main.token',
    value: '',
  };

  options = {
    contextmenu: true,
    lineNo: true,
    bracketPairColorization: true,
    formatOnPaste: true,
    "editor.codeActionsOnChange": {
      "source.fixAll": false,
      "source.fixAll.eslint": false, // If you're using ESLint
    },
    minimap: {
      enabled: true
    }
  };

  wasmModule: any;
  code = '';
  consoleLog: any; // original console log function
  codeOutput$ = new Subject<Log>();
  codeOutput: Log[] = [];
  isSmallScreen=false;
  showError = true;

  constructor(private isSmallScreenService:IsSmallScreenService){
    super();
  }

  public onCodeChanged(value: string) {
    this.code = value;
  }

  public runCode() {
    try {
      if (this.wasmModule)
        (this.wasmModule as any).run(this.code);
    }
    catch (err: any) {
      console.log(err)
    }
  }

  public clear() {
    this.codeOutput = [];
  }

  checkIfSmallScreen() {
    this.isSmallScreen = window.innerWidth < 800;
  }

  ngOnInit() {
    logger$ = this.codeOutput$;

    if (!(window as any).Module) {
      const script = document.createElement('script');
      script.src = 'assets/wasm-compiled-program/main.js';
      document.getElementsByTagName('head')[0].appendChild(script);
      script.onload = () => {
        console.log(this.wasmModule);
        this.wasmModule = (window as any).Module;
      }
    }
    else this.wasmModule = (window as any).Module;

    this.checkIfSmallScreen();

    this.codeOutput$
      .pipe(takeUntil(this.destroy$))
      .subscribe(res => this.codeOutput.push(res));

      this
      .isSmallScreenService
      .isSmallScreen$
      .pipe(takeUntil(this.destroy$))
      .subscribe(res=>this.isSmallScreen = res);
  }

  override ngOnDestroy(): void {
    super.ngOnDestroy();
    logger$ = null;
  }

  togleShowError = ()=> this.showError=!this.showError;
}
