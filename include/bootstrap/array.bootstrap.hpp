auto arrayBootstrapString = R"(class Array{
    function constructor(arr=[]){
        this.val = arr;   
    }

    function push(val){
       return __BRIDGE__FUNCTIONS__(this.val, 'push', [val]);
    }

    function pop(){
        return __BRIDGE__FUNCTIONS__(this.val, 'pop');
    }

    function split(start, end){
        
    }

    function splice(start,end, val){
    }

    function length(){
        return __BRIDGE__FUNCTIONS__(this.val, 'length');
    }

    function forEach(fn){
       
    }

    function map(){

    }

    function filter(){

    }

    function reduce(){

    }

    function find(){

    }

    function findIndex(){

    }

    function reverse(){

    }

    function sort(){

    }

    function join(){

    }

    function toString(){

    }
};)";