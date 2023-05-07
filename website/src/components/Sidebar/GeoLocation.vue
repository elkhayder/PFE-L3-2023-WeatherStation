<template>
   <div class="flex justify-between items-center" v-if="address">
      <div>
         <h2 class="title">{{ address?.city }}</h2>
         <h5 class="text-sm font-light text-gray-200">
            {{ address?.county }}, {{ address?.state }}
         </h5>
      </div>
      <div>
         <time class="font-medium">{{ TimeFormatter.format(date) }}</time>
      </div>
   </div>
</template>

<script setup lang="ts">
import { ref, onMounted } from "vue";
import { useGeolocationStore } from "../../stores/geolocation";
import { TimeFormatter } from "../../include/helpers";

const geolocationStore = useGeolocationStore();

const address = ref<any>(null);

const date = ref(new Date());

onMounted(() => {
   setInterval(() => date.value != new Date(), 60 * 1000);
});

geolocationStore.$subscribe(async (_, state) => {
   if (!state.latitude || !state.longitude) return;
   fetch(
      `https://geocode.maps.co/reverse?lat=${state.latitude}&lon=${state.longitude}`
   )
      .then((x) => x.json())
      .then((x) => (address.value = x.address));
});
</script>

<style lang="scss"></style>
