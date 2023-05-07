<template>
   <h4 class="title font-bold text-lg text-center">Sunrise & Sunset</h4>
   <div
      class="card w-full flex border-[1px] border-slate-300 items-center rounded-md py-4 px-6 my-4"
      v-if="response"
   >
      <i class="fad fa-sun text-3xl mr-6" />
      <div class="flex-1">
         <h2 class="font-light mb-0.5">Sunrise</h2>
         <time class="font-medium">{{
            TimeFormatter.format(response.sunrise)
         }}</time>
      </div>
      <time class="font-light">{{ relativeTime(response.sunrise) }}</time>
   </div>
   <div
      class="card w-full flex border-[1px] border-slate-300 items-center rounded-md py-4 px-6 my-4"
      v-if="response"
   >
      <i class="fad fa-moon-stars text-3xl mr-6" />
      <div class="flex-1">
         <h2 class="font-light mb-0.5">Sunset</h2>
         <time class="font-medium">{{
            TimeFormatter.format(response.sunset)
         }}</time>
      </div>
      <time class="font-light">{{ relativeTime(response.sunset) }}</time>
   </div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { useGeolocationStore } from "../../stores/geolocation";
import { TimeFormatter } from "../../include/helpers";

const geolocationStore = useGeolocationStore();

const response = ref<{ sunrise: Date; sunset: Date } | null>(null);

geolocationStore.$subscribe((_, state) => {
   if (!state.latitude || !state.longitude) return;

   fetch(
      `https://api.sunrise-sunset.org/json?date=today&lat=${state.latitude}&lng=${state.longitude}`
   )
      .then((x) => x.json())
      .then(
         (x) =>
            (response.value = {
               sunrise: formatTime(x.results.sunrise),
               sunset: formatTime(x.results.sunset),
            })
      );
});

const rtf = new Intl.RelativeTimeFormat("en", {
   localeMatcher: "best fit", // other values: "lookup"
   numeric: "always", // other values: "auto"
   style: "long", // other values: "short" or "narrow"
});

const formatTime = (time: string): Date => {
   return new Date(new Date().toLocaleString().split(", ")[0] + " " + time);
};

const relativeTime = (time: Date): string => {
   let diff = (time.getTime() - new Date().getTime()) / (1000 * 60 * 60);
   let type: Intl.RelativeTimeFormatUnit = "hour";
   if (Math.abs(diff) < 1) {
      diff *= 60;
      type = "minute";
   }
   return rtf.format(Math.round(diff), type);
};
</script>

<style lang="scss"></style>
