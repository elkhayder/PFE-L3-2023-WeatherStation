/** @type {import('tailwindcss').Config} */
export default {
   content: ["./index.html", "./src/**/*.{vue,js,ts,jsx,tsx}"],
   theme: {
      extend: {
         fontFamily: {
            sans: ["Montserrat", "sans-serif"],
            mono: ["'Anonymous Pro'"],
         },
      },
   },
   plugins: [],
};
