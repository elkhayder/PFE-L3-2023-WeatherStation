<template>
   <div class="mt-12" v-if="temperature">
      <div class="flex justify-between items-center mt-2">
         <h3 class="text-5xl font-medium">{{ temperature }}&#176; C</h3>
         <!-- <p class="text-right leading-6">Dramatic<br />Cloudy</p> -->
         <i class="fad fa-meteor text-4xl" />
      </div>
   </div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { useGeolocationStore } from "../../stores/geolocation";

const geolocationStore = useGeolocationStore();

const temperature = ref<number | null>(null);

geolocationStore.$subscribe((_, state) => {
   if (!state.latitude || !state.longitude) return;

   fetch(
      `https://api.open-meteo.com/v1/forecast?hourly=temperature_2m&current_weather=true&forecast_days=1&latitude=${state.latitude}&longitude=${state.longitude}`
   )
      .then((x) => x.json())
      .then((x) => (temperature.value = x.current_weather.temperature));
});
</script>

<style lang="scss"></style>
