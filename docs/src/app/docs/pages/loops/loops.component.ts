import { Component } from '@angular/core';

@Component({
  selector: 'app-loops',
  templateUrl: './loops.component.html',
  styleUrls: ['./loops.component.scss']
})
export class LoopsComponent {
  forLoopExample=`
  for (let i = 0; i < 3; i++)
    printLn("hello", i); // braces not needed for single statement
  
    // prints hello 0
  //        hello 1
  //        hello 2
  
  let Items = ["Item 1", "Item 2", "Item 3"];
  for(let i=0;i<3;i++){
    let item = Items[i];
    print(item);
  }
  
  // prints   Item 1
  //          Item 2
  //          Item 3`;

  whileLoopExample=`
let count = 0;
while (count < 5) {
  // Code to repeat
  count++;
}
print(count); //5`;
}
