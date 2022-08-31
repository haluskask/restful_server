<template>
  <v-card
    class="mx-auto my-5"
    max-width="800"
  >
    <v-sheet
      class="v-sheet--offset mx-auto"
      :color="chartColor"
      elevation="12"
      max-width="calc(100% - 32px)"
    >
      <v-sparkline
        :labels="get_data.map(x => x.toFixed(2))"
        :value="get_data"
        color="white"
        line-width="2"
        padding="16"
      ></v-sparkline>
    </v-sheet>

    <v-card-text class="pt-0">
      <div class="text-h6 font-weight-light mb-2">
        {{ get_live_data }} {{ sign }}
      </div>
      <div class="subheading font-weight-light grey--text">
        Live {{ get_title(title) }} [{{ sign }}]
      </div>
      <v-divider class="my-2"></v-divider>
      <v-icon
        class="mr-2"
        small
      >
        watch_later
      </v-icon>
      <span class="text-caption grey--text font-weight-light">last updated {{ this.$props.date }}</span>
    </v-card-text>
  </v-card>
</template>

<script>
export default {
  name: 'Sensor',
  props: {
    title: String,
    sign: String,
    chartColor: String,
    date: String
  },
  computed: {
    get_data () {
      return this.$store.state[this.$props.title];
    },
    get_live_data () {
      let data = this.$store.state[this.$props.title];
      return data[data.length - 1].toFixed(2);
    }
  },
  methods: {
    get_title (str) {
      return str.charAt(0).toUpperCase() + str.slice(1);
    }
  }
}
</script>

<style>
  .v-sheet--offset {
    top: -24px;
    position: relative;
  }
</style>
