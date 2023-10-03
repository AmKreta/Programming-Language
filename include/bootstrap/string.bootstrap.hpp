auto stringBootstrapString = R"(class String{
    function constructor(str=''){
        this.val = str;   
    }

    function slice(start, end){
        return __BRIDGE__FUNCTIONS__(this.val, 'slice', [start, end]);
    }

    function length(){
        return __BRIDGE__FUNCTIONS__(this.val, 'length');
    }

    function reverse(){
        return __BRIDGE__FUNCTIONS__(this.val, 'reverse');
    }

    function split(delimeter=' '){
        return __BRIDGE__FUNCTIONS__(this.val, 'split', [delimeter]);
    }

    function includes(substr){
        return __BRIDGE__FUNCTIONS__(this.val, 'includes', [substr]);
    }

    function replace(oldStr, newStr){
        return __BRIDGE__FUNCTIONS__(this.val, 'replace', [oldStr, newStr]);
    }

    function replaceAll(oldStr, newStr){
        return __BRIDGE__FUNCTIONS__(this.val, 'replaceAll', [oldStr, newStr]);
    }

    function findIndex(substr){
        return __BRIDGE__FUNCTIONS__(this.val, 'findIndex', [substr]);
    }

    function clone(){
        return __BRIDGE__FUNCTIONS__(this.val, 'clone');
    }

};)";