import { Component } from '@angular/core';
import MapExamples from './map.examples';

@Component({
  selector: 'app-map',
  templateUrl: './map.component.html',
  styleUrls: ['./map.component.scss']
})
export class MapComponent {
  mapDeclExample = `
let map = {"key": "val"};
print(map);`;
  mapExamples = MapExamples;
}
