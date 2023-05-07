import { createApp } from "vue";
import "./style.scss";
import App from "./App.vue";
import { createPinia } from "pinia";

const vueApp = createApp(App);

const pinia = createPinia();

vueApp.use(pinia);

vueApp.mount("#app");
