export default [
    {
        title:'push(val)',
        codeSnippet:`
const fruits = ["apple", "banana", "cherry"];
fruits.push("date");
// fruits now contains ["apple", "banana", "cherry", "date"]`,
        description:'Adds one or more elements to the end of an array and returns the new length of the array.'
    },
    {
        title:'pop()',
        codeSnippet:`
const fruits = ["apple", "banana", "cherry"];
const removedFruit = fruits.pop();
// removedFruit is "date", and fruits is now ["apple", "banana", "cherry"]`,
        description:'Removes the last element from an array and returns that element.'
    },
    {
        title:'slice(from, to)',
        codeSnippet:`
const fruits = ["apple", "banana", "cherry"];
const slicedFruits = fruits.slice(1, 3);
// slicedFruits is ["banana", "cherry"]`,
        description:'Returns a shallow copy of a portion of an array into a new array object.'
    },
    {
        title:'splice(from, deleteCount, [...elementsToPush])',
        codeSnippet:`
const fruits = ["apple", "banana", "cherry"];
fruits.splice(1, 1, "grape");
// fruits is now ["apple", "grape", "cherry"]`,
        description:'Changes the contents of an array by removing or replacing existing elements and/or adding new elements in place and returns array of removed elements.'
    },
    {
        title:'length()',
        codeSnippet:`
const fruits = ["apple", "banana", "cherry"];
const count = fruits.length();
// count is 3`,
        description:'Returns the number of elements in an array.'
    },
    {
        title:'forEach(callbackFn)',
        codeSnippet:`
const fruits = ["apple", "banana", "cherry"];
fruits.forEach(function(fruit){
    printLn(fruit);
});
// Logs each fruit in the array`,
        description:'Executes a provided function once for each array element.'
    },
    {
        title:'map(callbackFn)',
        codeSnippet:`
const num = [1, 2, 3];
const numSquare = num.map(function(i){
    return i**2;
});
print(numSquare);
// numSquare is [1, 4, 9]`,
        description:'Creates a new array with the results of calling a provided function on every element.'
    },
    {
        title:'filter(callbackFn)',
        codeSnippet:`
const num = [1, 2, 3, 4, 5, 6, 7, 8];
let res = num.filter(function(item){
   return item%2==0;
});
print(res);// array of each even no in num array`,
        description:'Creates a new array with all elements that pass a test provided by a function.'
    },
    {
        title:'reduce(callbackFn, initialval)',
        codeSnippet:`
const fruits = ["apple", "banana", "cherry"];
let totalLength = fruits.recude(function(acc, fruit){
   return acc + fruit.length()
}, 0);
print(totalLength);// Logs total length of items in fruit array`,
        description:'Applies a function against an accumulator and each element in the array (from left to right) to reduce it to a single value.'
    },
    {
        title:'find(callbackFn)',
        codeSnippet:`
const fruits = ["apple", "banana", "cherry"];
const foundFruit = fruits.find(function(fruit){
    return fruit == "banana";
});
print(foundFruit);// foundFruit is "banana"`,
        description:'Returns the first element in the array that satisfies the provided testing function.'
    },
    {
        title:'findIndex(callbackFn)',
        codeSnippet:`
const fruits = ["apple", "banana", "cherry"];
const index = fruits.findIndex(function(fruit){
    return fruit == "cherry";
});
print(index);// index is 2`,
        description:'Returns the index of the first element in the array that satisfies the provided testing function.'
    },
    {
        title:'reverse()',
        codeSnippet:`
const fruits = ["apple", "banana", "cherry"];
fruits.reverse();
print(fruits);// fruits is now ["cherry", "banana", "apple"]`,
        description:'Reverses the order of the elements in an array.'
    },
    {
        title:'clone()',
        codeSnippet:`
const fruits = ["apple", "banana", "cherry"];
let clone = fruits.clone();
clone[1] = "grapes";
printLn(fruits);
printLn(clone); // fruits is now ["cherry", "banana", "apple"]`,
        description:'Used to create shallow copy of an array.'
    }
];