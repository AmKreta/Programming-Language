export default [
    {
        title:'insert(key, val)',
        codeSnippet:`
let myMap = {};
myMap.insert("name", "John");
myMap.insert("age", 30);
print(myMap);`,
        description:'Adds a new key-value pair to the map. If the key already exists, it updates the associated value.'
    },
    {
        title:'delete(key)',
        codeSnippet:`
let myMap = {"name":"John", "age": 30};
myMap.delete("age");
print(myMap);`,
        description:'Removes the key-value pair associated with the given key.'
    },
    {
        title:'getKeys()',
        codeSnippet:`
let myMap = {"name":"John", "age": 30};
print(myMap.getKeys()); // ["name", "age"]`,
        description:'Returns an array containing all the keys in the map.'
    },
    {
        title:'getValues()',
        codeSnippet:`
let myMap = {"name":"John", "age": 30};
print(myMap.getValues()); // ["John", 30]`,
        description:'Returns an array containing all the values in the map.'
    },
    {
        title:'clone()',
        codeSnippet:`
let myMap = {"name":"John", "age": 30};
let clone = myMap.clone();
clone.insert("designation", "software Engineer");
printLn(myMap);
printLn(clone);`,
        description:''
    },
];