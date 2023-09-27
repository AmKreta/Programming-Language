import { Component } from '@angular/core';
import { CodeModel } from '@ngstack/code-editor';

@Component({
  selector: 'app-playground',
  templateUrl: './playground.component.html',
  styleUrls: ['./playground.component.scss']
})
export class PlaygroundComponent {
  theme = 'vs-dark';

  codeModel: CodeModel = {
    language: 'Token',
    uri: 'main.token',
    value: '',
  };

  options = {
    contextmenu: true,
    lineNo:true,
    bracketPairColorization:true,
    formatOnPaste:true,
    "editor.codeActionsOnChange": {
      "source.fixAll": false,
      "source.fixAll.eslint": false, // If you're using ESLint
    },
    minimap: {
      enabled: true
    }
  };
  

  onCodeChanged(value:string) {
    console.log('CODE', value);
  }
}
