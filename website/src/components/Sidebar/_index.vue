<template>
   <aside class="flex-1 max-w-sm text-white p-8 h-screen overflow-y-auto">
      <!-- ******************* -->
      <!-- * Location & Time * -->
      <!-- ******************* -->
      <GeoLocation />
      <!-- *************** -->
      <!-- * Temperature * -->
      <!-- *************** -->
      <Temperature />
      <hr class="my-9 w-full h-[1px] mx-auto bg-gray-400 border-0 rounded" />
      <!-- ******************** -->
      <!-- * Sunrise & Sunset * -->
      <!-- ******************** -->
      <SunriseSunset />
      <hr class="my-9 w-full h-[1px] mx-auto bg-gray-400 border-0 rounded" />
      <!-- ***************** -->
      <!-- * Rain Forecast * -->
      <!-- ***************** -->
      <Forecast />
   </aside>
</template>

<script setup lang="ts">
import { useGeolocationStore } from "../../stores/geolocation";

import { onMounted } from "vue";
import GeoLocation from "./GeoLocation.vue";
import Temperature from "./Temperature.vue";
import Forecast from "./Forecast.vue";
import SunriseSunset from "./SunriseSunset.vue";

const geolocationStore = useGeolocationStore();

onMounted(() => {
   geolocationStore.getLocation();
});
</script>

<style lang="scss" scoped>
aside {
   background: radial-gradient(#1a3251, #12294b);
}
.title {
   @apply text-lg font-medium;
}

.card {
   background: radial-gradient(#284166, #223b6b);
}
</style>
