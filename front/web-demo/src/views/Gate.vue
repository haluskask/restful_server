<template>
  <v-card
    class="mx-auto my-5"
    max-width="900"
    min-width="600"
    height="400"
  >
    <v-container
      style="height: 200px;"
    >
      <div class="grey lighten-3 mb-6" style="margin: auto; width: 90%; padding:50px; border-radius: 25px; margin-top:35px; font-size:x-large; text-align: center;">
        Status: <span :class="{ working, stopped: close && open }">{{ status }}</span>
      </div>
      <div style="width: 85%; margin: auto; padding-top: 10px"> 
        <v-progress-linear
          :color="this.status == 'STOPPING' ? 'error' : 'secondary'"
          v-show="progressBar"
          indeterminate
          height="6"
        ></v-progress-linear>
      </div>
    </v-container>
    <v-container
      fluid
      class="mb-6"
      style="height: 200px;"
    >
      <v-layout
          align-space-between justify-center row fill-height
        >
          <v-flex xs11>
            <div class="text-xs-center" style="height: 100%;">
              <v-btn
                @click="openGate()"
				        :disabled="open"
                color="primary"
                height="200"
                elevation="2"
                depressed
                style="height: 100px; width:200px; margin-top:25px; font-size:large;"
              >Open</v-btn>
            </div>
          </v-flex>
          <v-flex xs11>
            <div class="text-xs-center" style="height: 100%;">
              <v-btn
                @click="stopGate()"
                :disabled="!progressBar"
                color="error"
                height="200"
                elevation="2"
                depressed
                style="height: 100px; width:200px; margin-top:25px; font-size:large;"
              >Stop</v-btn>
            </div>
          </v-flex>
          <v-flex xs11>
            <div class="text-xs-center" style="height: 100%;">
              <v-btn
                @click="closeGate()"
				        :disabled="close"
                color="secondary"
                elevation="2"
                depressed
                style="height: 100px; width:200px; margin-top:25px; font-size:large;"
              >Close</v-btn>
            </div>
          </v-flex>
      </v-layout>
    </v-container>
  </v-card>
</template>

<script>
export default {
  name: 'Gate',
  data () {
    return {
      status: null,
      open: false,
      close: false,
      progressBar: false
    }
  },
  props: {},
  computed: {},
  methods: {
    openGate () {
      this.open = true
      this.status = "OPENING"
	    this.progressBar = true
	  
      this.$ajax.get("/api/v1/gate/open")
          .then(data => {
            this.status = data.data
            this.progressBar = false
            this.close = false
          })
          .catch(error => {
            console.log(error);
            this.progressBar = false
            this.close = false
          });
        //this.delay(3000, "OPEN")
    },
    stopGate () {
      this.open = true
      this.close = true
      this.status = "STOPPING"
	    this.progressBar = true
	  
      this.$ajax.get("/api/v1/gate/stop")
          .then(data => {
            this.status = data.data
            this.progressBar = false
            this.close = false
            this.open = false
          })
          .catch(error => {
            console.log(error);
            this.progressBar = false
            this.close = false
            this.open = false
          });
        //this.delay(3000, "OPEN")
    },
    closeGate () {
      this.close = true
      this.status = "CLOSING"
      this.progressBar = true
	  
      this.$ajax.get("/api/v1/gate/close")
          .then(data => {
            this.status = data.data
            this.progressBar = false
            this.open = false
          })
          .catch(error => {
            console.log(error);
            this.progressBar = false
            this.open = false
          });
        //this.delay(3000, "CLOSED")
    },
    delay(val, msg) {
      setTimeout(() => { this.status = msg; this.progressBar = false; }, val)
    }
  },
  mounted() {
	this.$ajax.get("/api/v1/gate/state")
		.then(data => {
		  console.log(data)
		  this.status = data.data
		  if (this.status == "OPEN") {
			  this.open = true
		  }
		  if (this.status == "CLOSED") {
			  this.close = true
		  }
		  
		})
		.catch(error => {
		  console.log(error);
		  
		});
  },
  destroyed: function () {}
}
</script>

<style>
  .working {
    color: 'secondary';
  }
  .stopped {
    color: 'error';
  }
</style>