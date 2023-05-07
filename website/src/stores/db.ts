// stores/counter.js
import { defineStore } from "pinia";

export type Measure = {
   node: string;
   measure: string;
   value: number;
   date: Date;
};

export const useDBStore = defineStore("db", {
   state: (): Measure[] => {
      return [];
   },
   actions: {
      async fetch() {
         this.$state = await fetch("/api/db")
            .then((x) => x.text())
            .then((x) => x.split("\n"))
            .then(
               (x) =>
                  x
                     .map((y) => {
                        const splitted = y.split(",");
                        return {
                           node: splitted[0],
                           measure: splitted[1],
                           value: +splitted[2],
                           date: new Date(+splitted[3] * 1000),
                        };
                     })
                     .filter((x) => x.node) as Measure[]
            )
            .catch(() => {
               console.error("DB fetching failed");
               return [];
            });
         console.log(`this.$state`, this.$state);
         return this.$state;
      },
   },
});
