auto stringBootstrapString = R"(class String{
    function constructor(str=''){
        this.val = str;   
    }

    function slice(start, end){
       print(start, end);
    }

    function length(){
        return __BRIDGE__FUNCTIONS__(this.val, 'length');
    }

    function reverse(){
        return __BRIDGE__FUNCTIONS__(this.val, 'reverse');
    }

    function split(delimeter=''){
        return __BRIDGE__FUNCTIONS__(this.val, 'split', [delimeter]);
    }

    function includes(){

    }

    function replace(){

    }

    function replaceAll(){

    }

    function findIndex(){
        
    }

    function findIndex(){

    }

};)";