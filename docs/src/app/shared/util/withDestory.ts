import { OnDestroy } from "@angular/core";
import { Subject } from "rxjs";

type Constructor<T = {}> = new (...args: any[]) => T;

function withDestory<T extends Constructor>(base: T = class { } as T) {
    return class extends base implements OnDestroy {

        destroy$ = new Subject<void>();

        ngOnDestroy(): void {
            this.destroy$.next();
            this.destroy$.complete();
        }
    };
}

export default withDestory;