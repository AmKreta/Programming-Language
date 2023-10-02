auto arrayBootstrapString = R"(class String{
    function constructor(str=''){
        this.val = str;   
    }

    function slice(start, end){
        return __BRIDGE__FUNCTIONS__(this.val, 'slice', [start, end]);
    }

    function splice(start,numElements, vals=[]){
        return __BRIDGE__FUNCTIONS__(this.val, 'length', [start, numElements, vals]);
    }

    function length(){
        return __BRIDGE__FUNCTIONS__(this.val, 'length');
    }

    function reverse(){
        return __BRIDGE__FUNCTIONS__(this.val, 'reverse');
    }

    split(delimeter=''){
        return __BRIDGE__FUNCTIONS__(this.val, 'split', [delimeter]);
    }

};)";