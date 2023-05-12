<template>
   <section class="flex-[2_2_0%] h-screen overflow-y-auto">
      <div class="w-full p-8 flex justify-between">
         <div>
            <h3 class="font-bold text-xl text-blue-950">
               {{
                  Intl.DateTimeFormat("en-US", {
                     month: "long",
                     year: "numeric",
                  }).format(new Date())
               }}
            </h3>
            <h5 class="font-medium text-gray-500">
               {{
                  Intl.DateTimeFormat("en-US", {
                     weekday: "long",
                     month: "short",
                     day: "2-digit",
                     // year: "numeric",
                  }).format(new Date())
               }}
            </h5>
         </div>

         <ul class="flex" role="tablist" v-if="data.length">
            <li v-for="node of [...new Set(data.map((x) => x.node))]">
               <a
                  :class="[
                     'ml-2 block min-w-[120px] rounded  px-6 pb-3.5 pt-4 text-center text-xs font-medium uppercase leading-tight border-[1px] border-neutral-300 cursor-pointer select-none transition-all duration-150',
                     {
                        'bg-neutral-700 text-white': selectedNode == node,
                     },
                  ]"
                  role="tab"
                  @click="() => changeSelectedNode(node)"
               >
                  {{ node }}
               </a>
            </li>
         </ul>
      </div>

      <div class="p-8 grid grid-cols-2 gap-8">
         <!-- card -->
         <div
            v-for="measure of [
               ...new Set(selectedNodeMeasures.map((x) => x.measure)),
            ]"
            :class="[
               'cursor-pointer border-2 border-zinc-100 p-8 flex items-center rounded-lg',
               { 'bg-zinc-100': measure == selectedMeasureType },
            ]"
            @click="selectedMeasureType = measure"
         >
            <i
               class="text-4xl text-blue-600 w-9 text-center mr-8"
               :class="ICON(measure)"
            />
            <div class="flex-1">
               <h5 class="font-medium text-gray-500 mb-1">{{ measure }}</h5>
               <h4 class="font-medium text-3xl text-blue-950">
                  {{
                     selectedNodeMeasures
                        .filter((x) => x.measure == measure)[0]
                        .value.toFixed(2)
                  }}
                  {{ UNIT(measure) }}
               </h4>
            </div>
            <div class="text-right text-sm font-medium text-gray-400">
               <h5>
                  {{
                     TimeFormatter.format(
                        selectedNodeMeasures.filter(
                           (x) => x.measure == measure
                        )[0].date
                     )
                  }}
               </h5>
               <h6>
                  {{
                     DateFormatter.format(
                        selectedNodeMeasures.filter(
                           (x) => x.measure == measure
                        )[0].date
                     )
                  }}
               </h6>
            </div>
         </div>
         <!-- <div class="bg-gray-500">Hello</div> -->
      </div>

      <div class="p-8">
         <div class="flex justify-center mb-8">
            <DatePicker
               v-model="dateRange"
               :range="true"
               lang="en"
               :circle="true"
            />
         </div>
         <Line
            :data="chartData"
            :options="{
               responsive: true,

               scales: {
                  x: {
                     ticks: {
                        maxRotation: 90,
                        minRotation: 90,
                     },
                  },
                  y: {
                     beginAtZero: true,
                  },
               },
               plugins: {
                  legend: {
                     display: false,
                  },
               },
            }"
         />
      </div>
      <div class="text-center font-medium text-sm m-4 mb-8">
         <h2>
            Created with <i class="far fa-heart text-red-500" /> by
            <a
               class="hover:underline"
               href="https://zelkhayder.me"
               target="_blank"
            >
               EL KHAYDER Zakaria
            </a>
            ,
            <a
               class="hover:underline"
               href="https://www.linkedin.com/in/nouhailaoufaski"
               target="_blank"
            >
               OUFASKI Nouhaila
            </a>
            &
            <a
               class="hover:underline"
               href="https://www.linkedin.com/in/l%C3%A9o-fries-556a70275/"
               target="_blank"
            >
               FRIES Léo
            </a>
         </h2>
         <h4 class="mt-2">Final year's project - L3 - 2022/2023</h4>
      </div>
   </section>
</template>

<script setup lang="ts">
import { onMounted, ref, computed } from "vue";
import { useDBStore, Measure } from "../../stores/db.ts";
import { Line } from "vue-chartjs";
import {
   Chart as ChartJS,
   Title,
   Tooltip,
   Legend,
   CategoryScale,
   LinearScale,
   ChartData,
   PointElement,
   LineElement,
} from "chart.js";
import {
   TimeFormatter,
   DateFormatter,
   UNIT,
   ICON,
} from "../../include/helpers";
ChartJS.register(
   Title,
   Tooltip,
   Legend,
   PointElement,
   LineElement,
   CategoryScale,
   LinearScale
);

import "vue-datepicker-ui/lib/vuedatepickerui.css";
import DatePicker from "vue-datepicker-ui";

const dateRange = ref<[Date, Date]>([
   new Date(new Date().getTime() - 7 * 24 * 60 * 60 * 1000),
   new Date(),
]);

const dbStore = useDBStore();

const data = ref<Measure[]>([]);

const selectedNode = ref<string | null>(null);
const selectedNodeMeasures = computed(() =>
   data.value
      .filter((x) => x.node == selectedNode.value)
      .sort((a, b) => b.date.getTime() - a.date.getTime())
);
const selectedMeasureType = ref<string | null>(null);

const changeSelectedNode = (node: string) => {
   selectedNode.value = node;
   selectedMeasureType.value = selectedNodeMeasures.value[0]?.measure;
};

const chartData = computed((): ChartData<"line"> => {
   const withoutTime = (d: Date) => {
      const newd = new Date(d);
      newd.setHours(0, 0, 0, 0);
      return newd;
   };
   const data = selectedNodeMeasures.value
      .filter((x) => x.measure == selectedMeasureType.value)
      .filter(
         (x) =>
            withoutTime(x.date) >= withoutTime(dateRange.value[0]) &&
            withoutTime(x.date) <= withoutTime(dateRange.value[1])
      );

   return {
      labels: data.map(
         (x) =>
            DateFormatter.format(x.date) + " " + TimeFormatter.format(x.date)
      ),
      datasets: [
         {
            label: selectedMeasureType.value ?? "",
            data: data.map((x) => +x.value),
            cubicInterpolationMode: "monotone",
            borderColor: "#284479",
            fill: true,
            pointBackgroundColor: "#dfe2e8",
            backgroundColor: "#dfe2e8",
         },
      ],
   };
});

onMounted(() => {
   dbStore.fetch().then((x) => {
      data.value = x;
      x.length && changeSelectedNode(x[0].node);
   });
});
</script>

<style lang="scss"></style>
