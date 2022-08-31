<template>
  <v-container fluid>
      <Sensor title="temperature" sign="°C" chartColor="red lighten-1" v-bind:date="this.date"/>
      <Sensor title="humidity" sign="%" chartColor="yellow darken-1" v-bind:date="this.date"/>
  </v-container>
</template>

<script>
import Sensor from '../components/Sensor.vue'

export default {
   data () {
    return {
      timer: null,
      date: null
    }
  },
  components: {
    Sensor
  },
  methods: {
    updateData: function () {
      this.$store.dispatch("update_sensors");
      let today = new Date();
      let date = today.getFullYear()+'-'+(today.getMonth()+1)+'-'+today.getDate();
      let time = today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();
      this.date = date+' '+time;
    }
  },
  mounted() {
    if (localStorage.date) {
      this.date = localStorage.date;
    }
    clearInterval(this.timer);
    this.timer = setInterval(this.updateData, 5000);
  },
  destroyed: function () {
    localStorage.date = this.date;
    clearInterval(this.timer);
  }
}
</script>
