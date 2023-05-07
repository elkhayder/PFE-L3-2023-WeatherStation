// stores/counter.js
import { defineStore } from "pinia";

type Position = {
   longitude?: number;
   latitude?: number;
};

export const useGeolocationStore = defineStore("geolocation", {
   state: (): Position => {
      return {
         longitude: undefined,
         latitude: undefined,
      };
   },
   actions: {
      getLocation() {
         if (!navigator.geolocation) return;
         navigator.geolocation.getCurrentPosition((pos) => {
            this.latitude = pos.coords.latitude;
            this.longitude = pos.coords.longitude;
         });
      },
   },
});
