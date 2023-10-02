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

    function slice(start, end){
        return __BRIDGE__FUNCTIONS__(this.val, 'slice', [start, end]);
    }

    function splice(start,numElements, vals=[]){
        return __BRIDGE__FUNCTIONS__(this.val, 'splice', [start, numElements, vals]);
    }

    function length(){
        return __BRIDGE__FUNCTIONS__(this.val, 'length');
    }

    function forEach(fn){
       let len = __BRIDGE__FUNCTIONS__(this.val, 'length');
       let x = this.val;
       for(let i=0;i<len;i = i+1)
        fn(x[i],i);
    }

    function map(fn){
        let res = [];
        let len =  __BRIDGE__FUNCTIONS__(this.val, 'length');
        let x = this.val;
        for(let i=0;i<len;i = i+1){
            let val = x[i];
            __BRIDGE__FUNCTIONS__(res, 'push', [fn(val, i)]);
        }
        return res;
    }

    function filter(fn){
        let res = [];
        let len =  __BRIDGE__FUNCTIONS__(this.val, 'length');
        let x = this.val;
        for(let i=0;i<len;i = i+1){
            let val = x[i];
            let result = fn(val, i);
            if(result)
            __BRIDGE__FUNCTIONS__(res, 'push', [val]);
        }
        return res;
    }

    function reduce(fn, acc = 0){
        let len =  __BRIDGE__FUNCTIONS__(this.val, 'length');
        let x = this.val;
        for(let i=0;i<len;i = i+1){
            let val = x[i];
            acc = fn(acc, val);
        }
        return acc;
    }

    function find(fn){
        let len =  __BRIDGE__FUNCTIONS__(this.val, 'length');
        let x = this.val;
        for(let i=0;i<len;i = i+1){
            let val = x[i];
            let match = fn(val, i);
            if(match)
                return val;
        }
    }

    function findIndex(fn){
        let len =  __BRIDGE__FUNCTIONS__(this.val, 'length');
        let x = this.val;
        for(let i=0;i<len;i = i+1){
            let val = x[i];
            if(fn(val, i))
                return i;
        }
    }

    function reverse(){
        __BRIDGE__FUNCTIONS__(this.val, 'reverse');
    }

};)";