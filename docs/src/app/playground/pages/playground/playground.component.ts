import { Component, OnDestroy, OnInit } from '@angular/core';
import { CodeModel } from '@ngstack/code-editor';
import { Subject, scan } from 'rxjs';

// wasm Module

@Component({
  selector: 'app-playground',
  templateUrl: './playground.component.html',
  styleUrls: ['./playground.component.scss']
})
export class PlaygroundComponent implements OnInit, OnDestroy {
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
  codeOutput$ = new Subject<string>();
  codeOutput: string[] = [];

  public onCodeChanged(value: string) {
    this.code = value;
  }

  public runCode() {
    if (this.wasmModule)
      (this.wasmModule as any).run(this.code);
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
        this.codeOutput$.next(textContent);
      }
    })(console.log.bind(console))

    this.codeOutput$
      //.pipe(scan((acc, val)=>acc + val || ''))
      .subscribe(res => this.codeOutput.push(res));
  }

  ngOnDestroy(): void {
    console.log = this.consoleLog;
  }
}
