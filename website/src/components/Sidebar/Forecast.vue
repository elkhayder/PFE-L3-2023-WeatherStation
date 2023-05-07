<template>
   <h4 class="title font-bold text-lg text-center">Forecast</h4>
   <!--  -->
   <h5 class="title mt-4">Rain</h5>
   <div
      class="flex justify-center items-center my-3 font-mono font-bold"
      v-if="response"
      v-for="i of [1, 5, 9, 13, 17]"
   >
      <time class="font-medium">{{
         TimeFormatter.format(new Date(response.time[i]))
      }}</time>
      <div class="mx-4 flex-1 h-5 rounded-full bg-slate-600 overflow-clip">
         <div
            class="bg-blue-300 h-full rounded-full"
            :style="{
               width: `${response.rain[i]}%`,
            }"
         />
      </div>
      <h5>{{ response.rain[i] }} %</h5>
   </div>
   <!--  -->
   <h5 class="title mt-8">Temperature</h5>
   <div
      class="flex justify-between items-center my-3"
      v-if="response"
      v-for="i of [1, 5, 9, 13, 17]"
   >
      <time class="font-medium font-mono">{{
         TimeFormatter.format(new Date(response.time[i]))
      }}</time>
      <h5>{{ response.temperature_2m[i] }}&#176; C</h5>
   </div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { useGeolocationStore } from "../../stores/geolocation";
import { TimeFormatter } from "../../include/helpers";

const geolocationStore = useGeolocationStore();

const response = ref<any>(null);

geolocationStore.$subscribe((_, state) => {
   if (!state.latitude || !state.longitude) return;

   fetch(
      `https://api.open-meteo.com/v1/forecast?hourly=temperature_2m,rain&current_weather=true&forecast_days=3&latitude=${state.latitude}&longitude=${state.longitude}`
   )
      .then((x) => x.json())
      .then((x) => (response.value = x.hourly));
});
</script>

<style lang="scss"></style>
