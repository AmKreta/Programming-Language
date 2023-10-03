auto mapBootstrapString = R"(class Map{
    function constructor(val = {}){
        this.val = val;
    }

    function insert(key, val){
        __BRIDGE__FUNCTIONS__(this.val, 'insert', [key, val]);
    }

    function delete(key){
        __BRIDGE__FUNCTIONS__(this.val, 'remove', [key]);
    }

    function getKeys(){
        let res = __BRIDGE__FUNCTIONS__(this.val, 'getKeys');
        return res;
    }

    function getValues(){
        let res = __BRIDGE__FUNCTIONS__(this.val, 'getValues');
        return res;
    }
};)";