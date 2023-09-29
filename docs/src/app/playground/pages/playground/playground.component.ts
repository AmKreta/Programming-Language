import { Component, OnDestroy, OnInit } from '@angular/core';
import { CodeModel } from '@ngstack/code-editor';
import { Subject, scan, takeUntil } from 'rxjs';
import withDestory from '@shared/util/withDestory';

// wasm Module

type Log = { isLog: boolean, text: string };

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

  ngOnInit() {
    const script = document.createElement('script');
    script.src = 'assets/wasm-compiled-program/main.js';
    document.getElementsByTagName('head')[0].appendChild(script);
    script.onload = () => {
      console.log(this.wasmModule);
      this.wasmModule = (window as any).Module;
    }

    // intercepting console.log
    this.consoleLog = console.log;
    console.log = ((originalConsoleLog: Function) => {
      return (...args: any[]) => {
        let textContent = Array.prototype.slice.call(args).join(' ');
        originalConsoleLog(textContent);
        if (textContent.startsWith('Exception:'))
          this.codeOutput$.next({ isLog: false, text: textContent });
        else 
          this.codeOutput$.next({ isLog: true, text: textContent });
      }
    })(console.log.bind(console))

    this.codeOutput$
      .pipe(takeUntil(this.destroy$))
      .subscribe(res => this.codeOutput.push(res));
  }

  override ngOnDestroy(): void {
    super.ngOnDestroy();
    console.log = this.consoleLog;
  }
}
