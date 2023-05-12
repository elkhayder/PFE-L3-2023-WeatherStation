export const TimeFormatter = Intl.DateTimeFormat("en-US", {
   hour: "2-digit",
   minute: "2-digit",
});

export const DateFormatter = Intl.DateTimeFormat("fr-FR", {
   day: "2-digit",
   month: "2-digit",
   year: "numeric",
});

export const UNIT = (type: string) => {
   const filter = [
      ["Temperature", "°C"],
      ["Pressure", "hPa"],
      ["Humidity", "%"],
   ].find((x) => x[0] == type);
   return filter ? filter[1] : null;
};

export const ICON = (type: string) => {
   const filter = [
      ["Temperature", "fas fa-thermometer-half"],
      ["Pressure", "far fa-weight"],
      ["Humidity", "fal fa-humidity"],
   ].find((x) => x[0] == type);
   return filter ? filter[1] : null;
};
